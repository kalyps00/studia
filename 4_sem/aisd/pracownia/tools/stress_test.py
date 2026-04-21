#!/usr/bin/env python3
"""
Universal stress tester for competitive programming tasks.
Supports multiple reference checkers, configurable generators, and detailed reporting.
"""
import argparse
import random
import sys
import time
from pathlib import Path

from checker import ProgramRunError, ProgramRunner
from generator import TASK_GENERATORS

# Fallback timeout if a task does not provide one.
TIMEOUT_PER_TEST = 10
SPINNER_FRAMES = ["|", "/", "-", "\\"]


def parse_massif_peak_bytes(massif_path: Path) -> int:
    peak_bytes = 0
    current = {"heap": 0, "extra": 0, "stack": 0}

    with massif_path.open() as handle:
        for line in handle:
            stripped = line.strip()
            if stripped.startswith("mem_heap_B="):
                current["heap"] = int(stripped.split("=", 1)[1])
            elif stripped.startswith("mem_heap_extra_B="):
                current["extra"] = int(stripped.split("=", 1)[1])
            elif stripped.startswith("mem_stacks_B="):
                current["stack"] = int(stripped.split("=", 1)[1])
                peak_bytes = max(
                    peak_bytes,
                    current["heap"] + current["extra"] + current["stack"],
                )

    return peak_bytes


def clear_console() -> None:
    if sys.stdout.isatty():
        sys.stdout.write("\033[2J\033[H")
        sys.stdout.flush()


def clear_line() -> None:
    if sys.stdout.isatty():
        sys.stdout.write("\r\033[2K")
        sys.stdout.flush()


def render_status(text: str) -> None:
    if sys.stdout.isatty():
        sys.stdout.write("\r\033[2K" + text)
        sys.stdout.flush()
    else:
        print(text, flush=True)


def infer_checker_max_n(task: str, checker_path: str):
    stem = Path(checker_path).stem.lower()
    if task == "klocki" and ("brutal" in stem or "brute" in stem):
        return 18
    return None


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Universal stress tester for algorithmic tasks"
    )
    parser.add_argument(
        "--task",
        type=str,
        required=True,
        choices=list(TASK_GENERATORS.keys()),
        help="Task identifier (e.g., 'klocki', 'miasta')",
    )
    parser.add_argument(
        "--program",
        type=str,
        required=True,
        help="Path to program to test (binary or .cpp file)",
    )
    parser.add_argument(
        "--checkers",
        type=str,
        nargs="+",
        required=False,
        help="Paths to reference checkers/solutions (space-separated)",
    )
    parser.add_argument(
        "--checker-names",
        type=str,
        nargs="+",
        help="Names for checkers (defaults to filenames)",
    )
    parser.add_argument(
        "--checker-max-n",
        type=int,
        nargs="+",
        help="Optional max n per checker (same order as --checkers)",
    )
    parser.add_argument(
        "--tests",
        type=int,
        default=100,
        help="Number of tests per run (default: 100)",
    )
    parser.add_argument(
        "--infinite",
        action="store_true",
        help="Run indefinitely until error found",
    )
    parser.add_argument(
        "--seed",
        type=int,
        default=None,
        help="Random seed",
    )
    parser.add_argument(
        "--output-dir",
        type=str,
        default=".",
        help="Output directory for error logs (default: current dir)",
    )
    parser.add_argument(
        "--build-dir",
        type=str,
        default=".build",
        help="Directory for compiled binaries (default: .build)",
    )
    parser.add_argument(
        "--memory-limit-mb",
        type=int,
        default=None,
        help="Override memory limit in MB (default: from task constraints)",
    )
    parser.add_argument(
        "--limit-checkers-memory",
        action="store_true",
        help="Also apply the memory limit to reference checkers",
    )
    parser.add_argument(
        "--timeout",
        type=int,
        default=None,
        help="Override timeout per test in seconds (default: tool default)",
    )
    parser.add_argument(
        "--no-timeout",
        action="store_true",
        help="Disable timeout completely (useful for overnight infinite runs)",
    )
    parser.add_argument(
        "--full-task-limits",
        action="store_true",
        help="Use the full task constraints as generator limits",
    )
    parser.add_argument(
        "--overnight",
        action="store_true",
        help="Shortcut for --infinite --no-timeout --full-task-limits",
    )
    parser.add_argument(
        "--valgrind-massif",
        action="store_true",
        help="Run the tested program under Valgrind massif and save a memory profile",
    )
    parser.add_argument(
        "--massif-out-file",
        type=str,
        default=None,
        help="Path to massif output file (default: <output-dir>/massif.out)",
    )
    parser.add_argument(
        "--save-input-file",
        type=str,
        default=None,
        help="Save each generated test input to this file (useful with --tests 1)",
    )
    parser.add_argument(
        "--check-ram",
        action="store_true",
        help="Run one maximal test under Valgrind massif and print whether RAM limit is exceeded",
    )

    # Task-specific parameters
    parser.add_argument(
        "--max-n",
        type=int,
        default=None,
        help="Max n parameter (task-specific; defaults to task default)",
    )
    parser.add_argument(
        "--max-h",
        type=int,
        default=None,
        help="Max height/value parameter (task-specific)",
    )
    parser.add_argument(
        "--sum-limit",
        type=int,
        default=None,
        help="Sum limit constraint (task-specific)",
    )

    args = parser.parse_args()

    if args.overnight:
        args.infinite = True
        args.no_timeout = True
        args.full_task_limits = True

    if args.check_ram:
        args.tests = 1
        args.infinite = False
        args.no_timeout = True
        args.full_task_limits = True
        args.valgrind_massif = True

    # Setup generator
    if args.task not in TASK_GENERATORS:
        print(f"Unknown task: {args.task}")
        return 1

    generator = TASK_GENERATORS[args.task]
    defaults = generator.defaults
    constraints = generator.constraints

    # Use CLI args or defaults
    max_n = args.max_n or defaults.get("max_n", constraints.n_max)
    max_h = args.max_h or defaults.get("max_h", 1000)
    sum_limit = args.sum_limit or defaults.get("sum_limit", constraints.sum_limit)
    if args.full_task_limits:
        max_n = constraints.n_max
        max_h = constraints.sum_limit
        sum_limit = constraints.sum_limit
    max_n = min(max_n, constraints.n_max)
    sum_limit = min(sum_limit, constraints.sum_limit)

    memory_limit_mb = args.memory_limit_mb or constraints.memory_limit_mb
    if args.no_timeout or args.infinite and args.timeout is None:
        timeout_per_test = None
    else:
        timeout_per_test = args.timeout or constraints.time_limit_s or TIMEOUT_PER_TEST

    build_dir = Path(args.build_dir)
    if not build_dir.is_absolute():
        build_dir = Path(__file__).resolve().parent / build_dir
    build_dir.mkdir(parents=True, exist_ok=True)

    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    program_run_prefix = []
    if args.valgrind_massif:
        if args.infinite:
            print("--valgrind-massif cannot be used with --infinite")
            return 1
        if args.tests != 1:
            print(
                "--valgrind-massif requires --tests 1 to avoid overwriting massif snapshots"
            )
            return 1

        massif_out = (
            Path(args.massif_out_file)
            if args.massif_out_file
            else output_dir / "massif.out"
        )
        if not massif_out.is_absolute():
            massif_out = Path.cwd() / massif_out
        massif_out.parent.mkdir(parents=True, exist_ok=True)

        program_run_prefix = [
            "valgrind",
            "--tool=massif",
            "--stacks=yes",
            f"--massif-out-file={massif_out}",
            "--quiet",
        ]
    else:
        massif_out = None

    # Setup program and checkers
    try:
        program_memory_limit = (
            None if (args.valgrind_massif or args.check_ram) else memory_limit_mb
        )

        if not args.check_ram and not args.checkers:
            print("--checkers is required unless --check-ram is used")
            return 1

        program = ProgramRunner(
            args.program,
            timeout=timeout_per_test,
            memory_limit_mb=program_memory_limit,
            build_dir=str(build_dir),
            run_prefix=program_run_prefix,
            static_link=not (args.valgrind_massif or args.check_ram),
        )
        program._ensure_compiled()
    except Exception as e:
        print(f"Failed to setup program: {e}")
        return 1

    checkers = []
    checker_names = []
    checker_max_n = []
    if not args.check_ram:
        try:
            checkers = [
                ProgramRunner(
                    path,
                    timeout=timeout_per_test,
                    memory_limit_mb=(
                        memory_limit_mb if args.limit_checkers_memory else None
                    ),
                    build_dir=str(build_dir),
                )
                for path in args.checkers
            ]
            for checker in checkers:
                checker._ensure_compiled()
        except Exception as e:
            print(f"Failed to compile checkers: {e}")
            return 1

    # Assign checker names
    if not args.check_ram:
        if args.checker_names:
            checker_names = args.checker_names
        else:
            checker_names = [Path(path).stem for path in args.checkers]

        if len(checker_names) != len(checkers):
            checker_names = [f"Checker{i}" for i in range(len(checkers))]

        if args.checker_max_n:
            if len(args.checker_max_n) != len(checkers):
                print("--checker-max-n must have same length as --checkers")
                return 1
            checker_max_n = args.checker_max_n
        else:
            checker_max_n = [infer_checker_max_n(args.task, p) for p in args.checkers]

    # Setup output
    errors_file = output_dir / "test_errors.txt"

    # Setup RNG
    if args.seed is not None:
        random.seed(args.seed)

    if not args.check_ram:
        finite_limits = [x for x in checker_max_n if x is not None]
        if finite_limits and len(finite_limits) == len(checkers):
            supported_max_n = max(finite_limits)
            if max_n > supported_max_n:
                max_n = supported_max_n
                print(
                    f"Info: max-n reduced to {max_n} based on checker limits ({checker_max_n})."
                )

    # Print info
    print(f"Task: {args.task}")
    print(f"Program: {args.program}")
    if args.check_ram:
        print("Checkers: none (RAM check mode)")
    else:
        print(f"Checkers: {', '.join(checker_names)}")
    print(f"Parameters: n<={max_n}, h<={max_h}, sum_limit<={sum_limit}")
    print(
        f"Task limits: RAM={constraints.memory_limit_mb} MB | Time={constraints.time_limit_s}s"
    )
    timeout_label = "none" if timeout_per_test is None else f"{timeout_per_test}s"
    print(f"Active limits: RAM={memory_limit_mb} MB | Timeout={timeout_label}")
    print(f"Checker max-n: {checker_max_n}")
    print(f"Build dir: {build_dir}")
    print(f"Output directory: {output_dir}")
    if args.valgrind_massif:
        print("Valgrind massif: enabled")
        print(f"Massif output: {massif_out}")
    if args.check_ram:
        print("RAM check: enabled")
    print()

    if args.check_ram:
        try:
            test_data = generator.generate_case(max_n, max_h, sum_limit)
            formatted_input = generator.format_case(test_data)
            if args.save_input_file:
                save_path = Path(args.save_input_file)
                if not save_path.is_absolute():
                    save_path = Path.cwd() / save_path
                save_path.parent.mkdir(parents=True, exist_ok=True)
                save_path.write_text(formatted_input)
        except Exception as e:
            print(f"Generator error: {e}")
            return 1

        try:
            program.run(formatted_input)
        except ProgramRunError as e:
            errors_file.parent.mkdir(parents=True, exist_ok=True)
            (errors_file.parent / "failed_case.in").write_text(formatted_input)
            print(f"✗ {e.kind}: {e}")
            print(f"Test saved to: {errors_file.parent / 'failed_case.in'}")
            return 1

        if massif_out is None or not massif_out.exists():
            print("✗ Massif output was not created")
            return 1

        peak_bytes = parse_massif_peak_bytes(massif_out)
        limit_bytes = (
            memory_limit_mb * 1024 * 1024 if memory_limit_mb is not None else None
        )
        peak_mib = peak_bytes / 1024 / 1024
        limit_mib = limit_bytes / 1024 / 1024 if limit_bytes is not None else None
        if limit_bytes is not None and peak_bytes > limit_bytes:
            print(f"RAM peak: {peak_mib:.2f} MiB")
            print(f"RAM limit: {limit_mib:.2f} MiB")
            print("Result: EXCEEDED")
            return 1

        print(f"RAM peak: {peak_mib:.2f} MiB")
        if limit_mib is not None:
            print(f"RAM limit: {limit_mib:.2f} MiB")
        print("Result: OK")
        return 0

    errors_log = []
    errors_count = 0
    total_tests = 0
    run_idx = 1
    started_at = time.time()

    try:
        while True:
            test_count = args.tests
            run_started_at = time.time()

            if run_idx > 1:
                clear_console()

            iterator = range(1, test_count + 1)
            render_status(
                f"{SPINNER_FRAMES[0]} Run #{run_idx} | 0/{test_count} (0%) | total={total_tests} | errors={errors_count}"
            )

            for tc in iterator:
                total_tests += 1

                # Generate test
                try:
                    test_data = generator.generate_case(max_n, max_h, sum_limit)
                    formatted_input = generator.format_case(test_data)
                    if args.save_input_file:
                        save_path = Path(args.save_input_file)
                        if not save_path.is_absolute():
                            save_path = Path.cwd() / save_path
                        save_path.parent.mkdir(parents=True, exist_ok=True)
                        save_path.write_text(formatted_input)
                except Exception as e:
                    print(f"Generator error: {e}")
                    return 1

                # Run program
                try:
                    program_output = program.run(formatted_input)
                except ProgramRunError as e:
                    errors_file.parent.mkdir(parents=True, exist_ok=True)
                    (errors_file.parent / "failed_case.in").write_text(formatted_input)
                    clear_line()
                    print(f"✗ {e.kind} at test #{total_tests}: {e}")
                    print(f"Test saved to: {errors_file.parent / 'failed_case.in'}")
                    return 1

                # Run checkers
                checker_outputs = []
                for checker, checker_name, checker_limit in zip(
                    checkers, checker_names, checker_max_n
                ):
                    if checker_limit is not None and test_data[0] > checker_limit:
                        continue
                    try:
                        output = checker.run(formatted_input)
                        checker_outputs.append((checker_name, output))
                    except ProgramRunError as e:
                        errors_file.parent.mkdir(parents=True, exist_ok=True)
                        (errors_file.parent / "failed_case.in").write_text(
                            formatted_input
                        )
                        clear_line()
                        print(f"✗ {checker_name} {e.kind} at test #{total_tests}: {e}")
                        print(f"Test saved to: {errors_file.parent / 'failed_case.in'}")
                        return 1

                # Compare outputs
                if not checker_outputs:
                    continue

                for checker_name, checker_out in checker_outputs:
                    if program_output != checker_out:
                        errors_count += 1
                        failed_case_path = errors_file.parent / "failed_case.in"
                        errors_file.parent.mkdir(parents=True, exist_ok=True)
                        failed_case_path.write_text(formatted_input)
                        errors_log.append(
                            {
                                "test_id": total_tests,
                                "kind": "WA",
                                "input": formatted_input,
                                "program_out": program_output,
                                "checker_name": checker_name,
                                "checker_out": checker_out,
                            }
                        )
                        clear_line()
                        print(
                            f"✗ WA at test #{total_tests} vs {checker_name} (mismatch #{errors_count})",
                            flush=True,
                        )
                        print(f"Input saved to: {failed_case_path}")

                # Progress
                elapsed = max(0.001, time.time() - started_at)
                speed = total_tests / elapsed
                run_elapsed = max(0.001, time.time() - run_started_at)
                run_speed = tc / run_elapsed
                pct = int(100 * tc / test_count)
                spinner = SPINNER_FRAMES[(tc - 1) % len(SPINNER_FRAMES)]
                render_status(
                    f"{spinner} Run #{run_idx} | {tc}/{test_count} ({pct}%) | total={total_tests} | errors={errors_count} | run {run_speed:.2f} t/s | avg {speed:.2f} t/s"
                )

            clear_line()

            if not args.infinite:
                break

            run_idx += 1
            if errors_count > 0:
                print(f"Found {errors_count} error(s). Stopping.")
                break

            clear_console()

    except KeyboardInterrupt:
        print("\nInterrupted by user.")

    # Write errors
    if errors_log:
        errors_file.parent.mkdir(parents=True, exist_ok=True)
        with open(errors_file, "w") as f:
            f.write(f"Total errors: {errors_count}\n")
            f.write(f"Total tests: {total_tests}\n")
            f.write("=" * 80 + "\n\n")

            for entry in errors_log:
                f.write(f"Error #{entry['test_id']} [{entry['kind']}]\n")
                f.write(f"Checker: {entry['checker_name']}\n")
                f.write("-" * 80 + "\n")
                f.write("INPUT:\n")
                f.write(entry["input"])
                f.write("\n")
                f.write("PROGRAM OUTPUT:\n")
                f.write(entry["program_out"])
                f.write("\n\n")
                f.write(f"{entry['checker_name'].upper()} OUTPUT:\n")
                f.write(entry["checker_out"])
                f.write("\n")
                f.write("=" * 80 + "\n\n")

        print(f"✗ {errors_count} error(s) in {total_tests} tests")
        print(f"Errors saved to: {errors_file}")
        return 1

    print(f"✓ All {total_tests} tests passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
