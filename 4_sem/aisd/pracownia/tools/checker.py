"""Program runner with timeout and resource limit enforcement."""

import hashlib
import resource
import subprocess
from pathlib import Path
from typing import Optional


class ProgramRunError(RuntimeError):
    def __init__(self, kind: str, message: str):
        super().__init__(message)
        self.kind = kind


class ProgramRunner:
    def __init__(
        self,
        exe_path: str,
        timeout: Optional[int] = 10,
        memory_limit_mb: Optional[int] = None,
        build_dir: Optional[str] = None,
    ):
        self.exe_path = Path(exe_path)
        self.timeout = timeout
        self.memory_limit_mb = memory_limit_mb
        self.build_dir = Path(build_dir) if build_dir else None
        self._compiled = False
        self._actual_exe = None

    def _limit_resources(self):
        if self.memory_limit_mb is None:
            return
        mem_bytes = int(self.memory_limit_mb) * 1024 * 1024
        resource.setrlimit(resource.RLIMIT_AS, (mem_bytes, mem_bytes))

    def _ensure_compiled(self):
        if self._compiled:
            return

        if self.exe_path.suffix == ".cpp":
            if self.build_dir is None:
                self.build_dir = self.exe_path.parent / ".build"
            self.build_dir.mkdir(parents=True, exist_ok=True)

            key = str(self.exe_path.resolve())
            short_hash = hashlib.sha1(key.encode()).hexdigest()[:10]
            exe_name = f"{self.exe_path.stem}_{short_hash}"
            self._actual_exe = self.build_dir / exe_name

            compile_cmd = [
                "g++",
                "-std=gnu++20",
                "-Wall",
                "-Wextra",
                "-Wshadow",
                "-O2",
                "-static",
                "-s",
                "-DJUDGE",
                "-o",
                str(self._actual_exe),
                str(self.exe_path),
            ]
            proc = subprocess.run(
                compile_cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                check=False,
            )
            if proc.returncode != 0:
                raise ProgramRunError(
                    "COMPILATION_ERROR",
                    f"Compilation failed for {self.exe_path}:\n"
                    f"{proc.stderr.decode(errors='ignore')}",
                )
        else:
            self._actual_exe = self.exe_path

        self._compiled = True

    def run(self, input_data: str) -> str:
        self._ensure_compiled()

        try:
            proc = subprocess.run(
                [str(self._actual_exe)],
                input=input_data.encode(),
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                timeout=self.timeout if self.timeout is not None else None,
                preexec_fn=self._limit_resources,
                check=False,
            )
        except subprocess.TimeoutExpired:
            raise ProgramRunError("TLE", f"Timeout ({self.timeout}s)")

        stderr = proc.stderr.decode(errors="ignore")

        if proc.returncode != 0:
            looks_like_memory = False
            if any(token in stderr.lower() for token in ["bad_alloc", "memoryerror"]):
                looks_like_memory = True
            if (
                proc.returncode in (-6, -9, -11, -24)
                and self.memory_limit_mb is not None
            ):
                looks_like_memory = True

            if looks_like_memory:
                raise ProgramRunError(
                    "RAM_EXCEEDED",
                    f"RAM exceeded (limit={self.memory_limit_mb} MB, exit code {proc.returncode})\nstderr: {stderr}",
                )

            raise ProgramRunError(
                "RUNTIME_ERROR",
                f"Exit code {proc.returncode}\nstderr: {stderr}",
            )

        return proc.stdout.decode().strip()
