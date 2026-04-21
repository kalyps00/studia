import random
import os
import subprocess
import time
import sys
from pathlib import Path


def generate_test(filename, n, m):
    """Generuje jeden test o wymiarach n x m"""
    tiles = ["A", "B", "C", "D", "E", "F"]

    with open(filename, "w") as f:
        f.write(f"{n} {m}\n")
        for _ in range(n):
            row = "".join(random.choices(tiles, k=m))
            f.write(row + "\n")


def generate_all_tests(test_dir="tests", num_tests=100):
    """Generuje 100 testów - małe, średnie i duże"""
    os.makedirs(test_dir, exist_ok=True)

    print(f"Generowanie {num_tests} testów...")

    for i in range(num_tests):
        # Różne rozmiary testów
        if i < 30:  # 30% małych testów
            n = random.randint(10, 100)
            m = random.randint(10, 100)
        elif i < 60:  # 30% średnich testów
            n = random.randint(100, 500)
            m = random.randint(100, 500)
        else:  # 40% dużych testów
            n = random.randint(500, 2000)
            m = random.randint(500, 2000)

        filename = f"{test_dir}/test_{i:03d}_{n}x{m}.in"
        generate_test(filename, n, m)

        if (i + 1) % 10 == 0:
            print(f"  Wygenerowano {i + 1}/{num_tests} testów")

    print(f"✓ Wszystkie testy zapisane w katalogu '{test_dir}'")


def run_program(program_path, test_file, timeout=10):
    """Uruchamia program na teście i mierzy czas"""
    try:
        with open(test_file, "r") as infile:
            start = time.perf_counter()
            result = subprocess.run(
                [program_path],
                stdin=infile,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                timeout=timeout,
                text=True,
            )
            elapsed = time.perf_counter() - start

            if result.returncode != 0:
                return None, None, f"Error: {result.stderr}"

            output = result.stdout.strip()
            return elapsed, output, None
    except subprocess.TimeoutExpired:
        return None, None, "TIMEOUT"
    except Exception as e:
        return None, None, str(e)


def test_programs(programs, test_dir="tests"):
    """Testuje wszystkie programy na wszystkich testach"""
    test_files = sorted(Path(test_dir).glob("test_*.in"))

    if not test_files:
        print(f"Brak testów w katalogu '{test_dir}'!")
        return

    print(f"\nTestowanie {len(programs)} programów na {len(test_files)} testach...\n")

    # Sprawdź czy programy istnieją
    for prog in programs:
        if not os.path.exists(prog):
            print(f"❌ Program '{prog}' nie istnieje!")
            return

    results = {prog: [] for prog in programs}
    wrong_results_count = 0
    wrong_results_tests = []

    for i, test_file in enumerate(test_files):
        test_name = test_file.name
        times = {}
        outputs = {}

        # Uruchom każdy program
        for prog in programs:
            elapsed, output, error = run_program(prog, test_file)

            if error:
                print(f"  {test_name} - {prog}: {error}")
                times[prog] = None
                outputs[prog] = None
            else:
                times[prog] = elapsed
                outputs[prog] = output
                results[prog].append(elapsed)

        # Sprawdź czy wyniki się zgadzają
        valid_outputs = [out for out in outputs.values() if out is not None]
        if len(set(valid_outputs)) > 1:
            wrong_results_count += 1
            wrong_results_tests.append(test_name)
            print(f"⚠️  {test_name}: Różne wyniki!")
            for prog in programs:
                print(f"    {prog}: {outputs[prog]}")

        # Usunięto sekcję o największej różnicy czasów

        # Pokaż progress co 10 testów
        if (i + 1) % 10 == 0:
            print(f"  Przetestowano {i + 1}/{len(test_files)} testów")

    # Podsumowanie
    print("\n" + "=" * 70)
    print("PODSUMOWANIE")
    print("=" * 70)

    # Podsumowanie poprawności wyników
    print(f"\n📊 Testy: {len(test_files)}")
    if wrong_results_count == 0:
        print(f"✅ Wszystkie wyniki się zgadzają!")
    else:
        print(f"❌ Różne wyniki w {wrong_results_count} testach:")
        for test in wrong_results_tests[:5]:  # Pokaż max 5 pierwszych
            print(f"   - {test}")
        if len(wrong_results_tests) > 5:
            print(f"   ... i {len(wrong_results_tests) - 5} więcej")

    # Ranking wg średniego czasu
    ranking = []
    for prog in programs:
        valid_times = [t for t in results[prog] if t is not None]
        if valid_times:
            avg_time = sum(valid_times) / len(valid_times)
            total_time = sum(valid_times)
            ranking.append(
                (avg_time, prog, total_time, min(valid_times), max(valid_times))
            )

    ranking.sort()
    print("\n" + "=" * 70)
    print("RANKING PROGRAMÓW WG ŚREDNIEGO CZASU")
    print("=" * 70)
    for i, (avg_time, prog, total_time, min_time, max_time) in enumerate(ranking, 1):
        print(f"{i}. {prog}")
        print(f"   Średni czas: {avg_time:.4f}s")
        print(f"   Łączny czas: {total_time:.4f}s")
        print(f"   Min/Max: {min_time:.4f}s / {max_time:.4f}s")


if __name__ == "__main__":
    TEST_DIR = "tests"
    PROGRAMS = ["./zadA_v2", "./miasta_prac_1"]

    # Sprawdź flagę --new
    if "--new" in sys.argv:
        print("Generowanie nowych testów...")
        generate_all_tests(TEST_DIR)
    elif not (os.path.exists(TEST_DIR) and list(Path(TEST_DIR).glob("test_*.in"))):
        print("❌ Brak testów! Wygeneruj je używając: python3 testy.py --new")
        sys.exit(1)
    else:
        print(f"Używanie istniejących testów z '{TEST_DIR}'")

    # Testuj programy
    test_programs(PROGRAMS, TEST_DIR)
