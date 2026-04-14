# Uzycie

Uruchamiaj z folderu `pracownia/tools`:

```bash
python3 stress_test.py \
  --task klocki \
  --program ../zad\ B/klocki.cpp \
  --checkers ../zad\ B/klocki_brutal.cpp \
  --tests 100 \
  --seed 123
```

Program testowany i checkery moga byc binarka albo `.cpp`.

Jesli chcesz odpalic to "na noc" bez podawania limitow recznie, wystarczy:

```bash
python3 stress_test.py \
  --task klocki \
  --program ../zad\ B/klocki.cpp \
  --checkers ../zad\ B/klocki_ref.cpp \
  --overnight
```

`--overnight` to skrot do:

```bash
--infinite --no-timeout --full-task-limits
```

W trybie `--overnight` generator bierze pelne limity zadania i nie ma timeoutu,
wiec run moze leciec cala noc.

Domyslnie generator uzywa praktycznych limitow do długiego testowania. Jesli chcesz
pelne limity zadania, dodaj:

```bash
python3 stress_test.py \
  --task klocki \
  --program ../zad\ B/klocki.cpp \
  --checkers ../zad\ B/klocki_ref.cpp \
  --infinite \
  --no-timeout \
  --full-task-limits
```

To odpala maksymalne `n` i maksymalna sume zadan, ale moze byc wyraznie wolniejsze.

Domyslnie generator bierze pelne limity zadania, czyli dla `klocki`:

- `n` do 2000
- suma wysokosci do 1_000_000
- limit RAM 16 MB
- limit czasu bierze z zadania

Nowe opcje:

- `--build-dir .build` - kompiluje wszystkie `.cpp` do osobnego folderu
- `--memory-limit-mb 16` - ustawia limit RAM dla odpalanych programow
- `--timeout 1` - ustawia limit czasu na test
- `--checker-max-n` - limity rozmiaru dla konkretnych checkerow
- `--limit-checkers-memory` - naklada limit RAM tez na checkery
- `--infinite` - odpala testy w petli bez konca

Domyslnie limit RAM dotyczy tylko programu testowanego. Checkery lecą bez limitu
pamieci, zeby referencja nie wywalala sie sama z siebie na duzych testach.

Jesli chcesz szybsze, mniejsze testy do debugowania, ustaw recznie np. `--max-n 100 --max-h 1000`.

Typy bledow w logach:

- `COMPILATION_ERROR` - blad kompilacji
- `TLE` - przekroczenie czasu
- `RAM_EXCEEDED` - przekroczenie pamieci
- `RUNTIME_ERROR` - crash lub inny blad wykonania
- `WA` - zly wynik wzgledem checkera

Przyklad z wieloma checkerami:

```bash
python3 stress_test.py \
  --task klocki \
  --program ../zad\ B/klocki.cpp \
  --checkers ../zad\ B/klocki_brutal.cpp ../zad\ B/klocki_ref.cpp \
  --checker-names brute ref \
  --tests 50
```

Tryb nieskonczony:

```bash
python3 stress_test.py \
  --task klocki \
  --program ../zad\ B/klocki.cpp \
  --checkers ../zad\ B/klocki_ref.cpp \
  --infinite
```

Pelna lista opcji:

```bash
python3 stress_test.py --help
```

Jak dodac nowy generator:

1. Dodaj nowa klase dziedziczaca po `BaseGenerator` w `generator.py`.
2. Ustaw w niej `constraints` i `defaults` dla zadania.
3. Zaimplementuj `generate_case()` oraz `format_case()`.
4. Dopisz obiekt do `TASK_GENERATORS`.

Przykladowy schemat:

```python
class NoweZadanieGenerator(BaseGenerator):
    task_name = "nowe_zadanie"
    constraints = TaskConstraints(...)
    defaults = {...}

    def generate_case(self, max_n, max_h, sum_limit):
        ...

    def format_case(self, case):
        ...

TASK_GENERATORS["nowe_zadanie"] = NoweZadanieGenerator()
```
