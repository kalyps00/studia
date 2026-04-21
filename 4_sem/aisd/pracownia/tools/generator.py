"""Task generators and task constraints registry."""

import io
import random
from dataclasses import dataclass
from typing import Dict, List, Tuple


@dataclass(frozen=True)
class TaskConstraints:
    n_min: int
    n_max: int
    sum_limit: int
    memory_limit_mb: int
    time_limit_s: int


class BaseGenerator:
    task_name: str = "base"
    constraints: TaskConstraints
    defaults: Dict[str, int]

    def generate_case(self, max_n: int, max_h: int, sum_limit: int):
        raise NotImplementedError

    def format_case(self, case) -> str:
        raise NotImplementedError


class KlockiGenerator(BaseGenerator):
    task_name = "klocki"
    constraints = TaskConstraints(
        n_min=2,
        n_max=2000,
        sum_limit=1_000_000,
        memory_limit_mb=16,
        time_limit_s=1,
    )
    defaults = {
        "max_n": constraints.n_max,
        "max_h": 1000,
        "sum_limit": 10000,
    }

    def generate_case(
        self, max_n: int, max_h: int, sum_limit: int
    ) -> Tuple[int, List[int]]:
        n = random.randint(self.constraints.n_min, max_n)
        arr: List[int] = []
        total = 0

        for i in range(n):
            remaining_positions = n - i - 1
            max_allowed = min(max_h, sum_limit - total - remaining_positions)
            if max_allowed < 1:
                max_allowed = 1
            h = random.randint(1, max_allowed)
            arr.append(h)
            total += h

        return n, arr

    def format_case(self, case: Tuple[int, List[int]]) -> str:
        n, heights = case
        return f"{n}\n{' '.join(map(str, heights))}\n"


class KomiwojazerGenerator(BaseGenerator):
    task_name = "komiwojazer"
    constraints = TaskConstraints(
        n_min=2,
        n_max=100_000,
        sum_limit=1_000_000,
        memory_limit_mb=48,
        time_limit_s=10,
    )
    defaults = {
        "max_n": constraints.n_max,
        "max_h": constraints.sum_limit,
        "sum_limit": constraints.n_max - 1,
    }

    def generate_case(
        self, max_n: int, max_h: int, sum_limit: int
    ) -> Tuple[int, int, int, int]:
        max_n = min(max_n, self.constraints.n_max)
        max_m = min(max_h, self.constraints.sum_limit)
        max_k = min(sum_limit, max_n - 1)

        if max_n >= self.constraints.n_max and max_m >= self.constraints.sum_limit:
            n = self.constraints.n_max
            m = self.constraints.sum_limit
            k = n - 1
        else:
            n = random.randint(self.constraints.n_min, max_n)
            if max_m >= n - 1:
                m = random.randint(n - 1, max_m)
            else:
                m = random.randint(1, max_m)
            random_k_max = min(max_k, n - 1)
            k = random.randint(1, max(1, random_k_max))

        seed = random.getrandbits(64)
        return n, m, k, seed

    def format_case(self, case: Tuple[int, int, int, int]) -> str:
        n, m, k, seed = case
        rng = random.Random(seed)
        buffer = io.StringIO()

        buffer.write(f"{n} {m} {k}\n")

        if m >= n - 1:
            for node in range(1, n):
                weight = rng.randint(1, 10_000)
                buffer.write(f"{node} {node + 1} {weight}\n")

            extra_edges = m - (n - 1)
            for _ in range(extra_edges):
                while True:
                    a = rng.randint(1, n)
                    b = rng.randint(1, n)
                    if a != b:
                        break
                weight = rng.randint(1, 10_000)
                buffer.write(f"{a} {b} {weight}\n")
        else:
            for _ in range(m):
                while True:
                    a = rng.randint(1, n)
                    b = rng.randint(1, n)
                    if a != b:
                        break
                weight = rng.randint(1, 10_000)
                buffer.write(f"{a} {b} {weight}\n")

        if k == n - 1:
            for dest in range(2, n + 1):
                buffer.write(f"{dest}\n")
        else:
            targets = rng.sample(range(2, n + 1), k)
            for dest in targets:
                buffer.write(f"{dest}\n")

        return buffer.getvalue()


TASK_GENERATORS: Dict[str, BaseGenerator] = {
    "klocki": KlockiGenerator(),
    "komiwojazer": KomiwojazerGenerator(),
    "zad_c": KomiwojazerGenerator(),
}
