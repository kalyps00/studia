# Lista 3 - Wyrażenia Arytmetyczne

## Opis projektu

Projekt implementuje hierarchię klas reprezentujących wyrażenia arytmetyczne, które mogą być reprezentowane jako drzewo:

- **Liście**: operandy (liczby, zmienne, stałe)
- **Węzły wewnętrzne**: operatory arytmetyczne i funkcje matematyczne

## Struktura projektu

### Interfejs `Obliczalny`

Interfejs definiujący metody obliczania wartości wyrażeń:

- `double oblicz()` - oblicza wartość wyrażenia

### Klasa abstrakcyjna `Wyrazenie`

Klasa bazowa dla wszystkich wyrażeń implementująca interfejs `Obliczalny`:

- `static Wyrazenie suma(Wyrazenie... wyr)` - sumuje wyrażenia
- `static Wyrazenie iloczyn(Wyrazenie... wyr)` - mnoży wyrażenia

### Operandy

#### `Liczba`

Reprezentuje stałą liczbę rzeczywistą

- Pola statyczne: `ZERO` (0.0), `JEDEN` (1.0)

#### `Stała`

Reprezentuje stałą matematyczną

- Pola statyczne: `Pi` (π ≈ 3.14), `E` (e ≈ 2.72)

#### `Zmienna`

Reprezentuje zmienną o nazwie

- Umożliwia ustawienie wartości: `Zmienna.ustawWartość(nazwa, wartość)`

### Operatory dwuargumentowe

#### `Dodaj`

Operacja dodawania (priorytet 1)

#### `Odejmij`

Operacja odejmowania (priorytet 1)

#### `Mnoz`

Operacja mnożenia (priorytet 2)

#### `Dziel`

Operacja dzielenia (priorytet 2)

### Operatory jednoargumentowe (prefiksowe)

#### `Negacja` (~)

Zmiana znaku: x ↦ -x

#### `Odwrotność` (!)

Odwrotność: x ↦ 1/x

### Funkcje matematyczne

#### `Sin`

Funkcja sinus

#### `Cos`

Funkcja cosinus

#### `Exp`

Funkcja wykładnicza: e^x

#### `Log`

Logarytm o dowolnej podstawie

#### `Potega`

Potęgowanie: podstawa ^ wykładnik

## System priorytetów

Operatory mają następujące priorytety:

- Priorytet 1: Dodawanie, Odejmowanie
- Priorytet 2: Mnożenie, Dzielenie

System priorytetów minimalizuje liczbę potrzebnych nawiasów podczas wypisywania wyrażenia.

## Program testowy

Program testowy `Main.java` demonstruje wszystkie funkcjonalności:

```
7 + 5 * x - 1                    (dla x = 1.618)
~ (2 - x) * e                    (negacja wyrażenia)
(3 * π - 1) / (! x + 5)         (odwrotność wyrażenia)
sin((x + 13) * π / (1 - x))
exp(5) + x * log(e, x)
```

## Kompilacja

```bash
cd lista3
javac -d bin src/wyrażenia/*.java src/Main.java
```

## Uruchomienie

```bash
java -cp bin Main
```

## Dodatkowe testy

Plik `TestEquals.java` testuje metody `equals()` i `toString()` wszystkich klas:

```bash
javac -d bin src/wyrażenia/*.java src/TestEquals.java
java -cp bin TestEquals
```

## Implementowane interfejsy i metody

Wszystkie klasy w hierarchii:

- ✅ Implementują interfejs `Obliczalny` (przez `Wyrazenie`)
- ✅ Implementują metodę `oblicz()`
- ✅ Nadpisują metodę `toString()` z odpowiednim formatowaniem
- ✅ Nadpisują metodę `equals(Object)`
- ✅ Implementują `hashCode()` dla pełnej kompatybilności z kolekcjami
