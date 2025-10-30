# Projekt
Biblioteka w C/C++ zajmująca się operacjami na tekstach. 
## Program demonstracyjny:
Aby skompilować program demonstracyjny wpisz:
```bash
g++ -std=c++17 Szyfr_RSA.c rozpoznawanie_jezyka.c regex.c podzial.c plot.c nawiasowanie.c najdluzszy_palindrom.c biblioteka.c base64.cpp arithmetic.cpp demo.cpp  -o demonstracja
```
Program prezentuje różne funkcjonalności biblioteki


## Pythonowa wersja projektu:
Żeby przetestować wersję pythonową wpisz w terminalu:
`python3 demo.py` lub `py demo.py`
Aby skorzystać z biblioteki pythonowej, powinieneś mieć zainstalowanego 64-bitowego Pythona oraz 64-bitowy gcc oraz g++.
Musisz mieć też zainstalowane pythonowe biblioteki: `ctypes, subprocess, os`
Żeby skorzystać z funkcji bibliotecznych we własnym projekcie w Pythonie zaimportuj najpierw bibliotekę `pyton`:
```python
from pyton import *
lib = get_all_libs() #to polecenie spróbuje skompilować wszystkie biblioteki dynamiczne potrzebne do uruchomienia programu
#Żeby wypisać nazwy poszczególnych modułów wpisz:
print(list(lib))
#wynik: ['biblioteka', 'palindrom', 'szyfr_rsa', 'plot', 'podzial', 'regex', 'rozpoznawanie_jezyka', 'nawiasowanie', 'arithmetic', 'base64']
lib['plot'].szyfruj() #wywołuje funkcję szyfruj() z plot.c
lib['arithmetic'].c_encode1421(b'a.txt',b'b.txt') #w przypadku funkcji z arithmetic.cpp oraz base64.cpp
#należy dodać przedrostek c_ do nazwy funkcji
#poza tym wszystkie pythonowe stringi przesyłane do funkcji należy poprzedzić literą b
#aby zadeklarować obiekt typu np. c_string należy wpisać
tekst = c_string() #tworzymy obiekt klasy c_string
lib['szyfr_rsa'].init(ctypes.byref(tekst)) #jesli funkcja wymaga wskaznika do obiektu, a nie obiektu to należy użyć ctypes.byref()
#dużo więcej przykładów można znaleźć w demo.py 
```

--------------------------------------
## base64

Testowy program może zostać skompilowany i uruchomiony przy pomocy:

```bash
g++ -std=c++17 main.cpp base64.cpp arithmetic.cpp -o main
./main base64
```

## arithmetic

Testowy program może zostać skompilowany i uruchomiony przy pomocy:

```bash
g++ -std=c++17 main.cpp base64.cpp arithmetic.cpp -o main
./main arithmetic "${FILE_PATH}"
```
## Specyfikacja klas

### `bitio::bit_istream`

#### Opis:
Bazowa klasa pomocnicza reprezentująca strumień wejściowy z operacjami na bitach.

#### Funkcje:
- `bool get_bit()`: zwraca pojedynczy bit ze strumienia.
- `bool eof()`: zwraca informację czy wszystkie bit zostały przeczytane ze strumienia.

#### Implementacje:
- `bitio::bit_ifstream` wykorzystuje `std::ifstream`.
- `bitio::bit_string_istream` wykorzystuje `std::string`.

### `bitio::bit_ostream`

#### Opis:
Bazowa klasa pomocnicza reprezentująca strumień wyjściowy z operacjami na bitach.

#### Funkcje:
- `void put_bit(bool bit)`: dodaje pojedynczy bit do strumienia.
- `void flush()`: dopełnia niedokończony bajt zerami i zapisuje strumienia.

#### Implementacje:
- `bitio::bit_ofstream` wykorzystuje `std::ofstream`.
    Posiada dodatkową funkcję `void close()` zamykającą strumień.
- `bitio::bit_string_ostream` wykorzystuje `std::string`.
    Posiada dodatkową funkcję `std::string result()` zwracającą wewnętrzny napis.

## Specyfikacja funkcji
### `key RSA()`

#### Opis:
Funkcja `RSA` zwraca struct typu `key`. Zawiera on parę kluczy - klucz publiczny oraz prywatny.
Klucz prywatny to `key.privatekey`, a publiczny `key.publickey`. Posłużą one do szyfrowania i deszyfrowania.
#### Parametry:
- brak

#### Zwracana wartość:
- `key` - para kluczy
---
### `void init_c_string(c_string* a); void push_c_string(c_string* a, char z); void free_c_string(c_string* a); char get_c_string(c_string* a, int i);`

#### Opis:
Są to funkcje obsługujące struct c_string. Struct ten symuluje nieco zachowanie stringa w C++.
* Żeby utworzyć zmienną typu c_string wystarczy napisać `c_string tekst;`
* Funkcja `init_c_string(&tekst)` powinna zostać wywołana od razu po zadeklarowaniu zmiennej typu c_string oraz zawsze po poleceniu `free_c_string(&tekst)`, jeśli zamierzamy dalej używać tej zmiennej.
* Funkcja `push_c_string(&tekst,char litera)` konkatenuje zawartość zmiennej `litera` na koniec structa `tekst`.
* Funkcja `free_c_string(&tekst)` czyści c_string `tekst`. 
* Funkcja `get_c_string(c_string* a, int i)` zwraca i-tą literę c-stringa (licząc od 0).

---

### `void print_c_string(c_string* a); void read_c_string(c_string* res);`

#### Opis:
Są to funkcje obsługujące struct c_string. Struct ten symuluje nieco zachowanie stringa w C++.
* funkcja `print_c_string(&tekst)` służy wypisaniu zawartości `tekst` na ekran.
* funkcja `read_c_string(&tekst)` służy wczytaniu ze standardowego wejścia tekstu i zapisania go do zmiennej `tekst`. 
  
---

### `void print_hex(int1024 a, c_string* res); int1024 read_hex(c_string* a);`

#### Opis:
Te funkcje służą do zapisania i odczytania klucza z pewnego ustalonego formatu. (np. jeśli jest potrzeba wymienienia się kluczami między różnymi osobami używającymi biblioteki)
* funkcja `print_hex(int1024 a, c_string* res);` zapisuje do `res` zapis w pewnym formacie liczbę 1024-bitową `a`.
* funkcja `read_c_string(&tekst)` zwraca liczbę 1024-bitową po odczytaniu jej ze zmiennej `tekst`. 

#### Przykład zastosowania:
```C
key klucz = RSA();
c_string klucz_prywatny; init_c_string(&klucz_prywatny);
print_hex(klucz.privatekey.d,klucz_prywatny); 
print_c_string(klucz_prywatny); //wypisuje na ekran
free_c_string(&klucz_prywatny);
```
---
### `void RSA_encode(c_string* s, public_key klucz, c_string* res); void RSA_decode(c_string* s, private_key klucz, c_string* res);`

#### Opis:
Szyfruje i deszyfruje tekst za pomocą algorytmu RSA.
#### Parametry:
- wskaźnik do szyfrowanego/deszyfrowanego tekstu (zapisanego z pomocą structa `c_string`) 
- klucz publiczny/prywatny (np. klucz prywatny można dostać ze structa typu `key` o nazwie `klucz` za pomocą `klucz.privatekey`)
- wskaźnik do structa c_string w którym zostanie zapisana odpowiedź


#### Zwracana wartość:
- brak
---
### `void init_c_string(c_string* a); void push_c_string(c_string* a, char z); void free_c_string(c_string* a); char get_c_string(c_string* a, int i);`

#### Opis:
Są to funkcje obsługujące struct c_string. Struct ten symuluje nieco zachowanie stringa w C++.
* Żeby utworzyć zmienną typu c_string wystarczy napisać `c_string tekst;`
* Funkcja `init_c_string(&tekst)` powinna zostać wywołana od razu po zadeklarowaniu zmiennej typu c_string oraz zawsze po poleceniu `free_c_string(&tekst)`, jeśli zamierzamy dalej używać tej zmiennej.
* Funkcja `push_c_string(&tekst,char litera)` konkatenuje zawartość zmiennej `litera` na koniec structa `tekst`.
* Funkcja `free_c_string(&tekst)` czyści c_string `tekst`. 
* Funkcja `get_c_string(c_string* a, int i)` zwraca i-tą literę c-stringa (licząc od 0).



---






### `const char *detect_language(char *text)`

#### Opis:
Funkcja `detect_language` analizuje tekst i określa, w jakim języku został napisany na podstawie porównania częstotliwości występowania liter z predefiniowanymi profilami językowymi.

#### Jak działa:
1. **Analiza tekstu**: Funkcja zlicza wystąpienia liter od `a` do `z` oraz zamienia je na częstotliwości procentowe.
2. **Porównanie z profilami językowymi**: Częstotliwości liter w tekście są porównywane z profilami języków zdefiniowanymi w strukturze `LanguageBase`.
3. **Określenie dopasowania**: Algorytm oblicza odległość euklidesową pomiędzy rozkładem liter w tekście a każdym profilem językowym, wybierając język o najmniejszej odległości.

#### Parametry:
- `char *text`: Tekst wejściowy, którego język ma zostać rozpoznany.

#### Zwracana wartość:
- `const char *`: Kod języka w formacie trzyliterowym (np. `"ENG"`, `"POL", "GER", "FRA", "FIN", "ESP", "ITA", "TUR", "SWE", "DAN", "ICE", "CZE", "HUN" `). Dla kolejno angielskiego, polskiego, niemieckiego, francuskiego, fińskiego, hiszpańskiego, włoskiego, tureckiego, szwedzkiego, duńskiego, islandzkiego, czeskiego i węgierskiego.

### **Uwaga:** 
**Algorytm działa skutecznie przy tekście który ma wiecej niż 100 znaków, a w tekstach powyżej 1000 znaków dokładność jest bardzo wysoka**

---

### `char *find_longest_palindrome(const char *text)`

#### Opis:
Funkcja `find_longest_palindrome` znajduje najdłuższy palindrom w danym tekście za pomocą algorytmu Manachera, który pozwala na wydajne wyznaczanie palindromów w ciągach znaków.

#### Jak działa:
1. **Przetwarzanie tekstu**: Funkcja najpierw przetwarza tekst, dodając separatory (`#`) pomiędzy każdą literą, a także dodaje znaki krańcowe (`^` na początku i `$` na końcu). To umożliwia łatwiejsze rozszerzanie palindromów.
2. **Algorytm Manachera**: Funkcja stosuje algorytm Manachera do wykrywania palindromów w przetworzonym ciągu. Wartość `P[i]` reprezentuje promień palindromu, którego środek znajduje się w indeksie `i`.
3. **Wyszukiwanie najdłuższego palindromu**: Podczas przetwarzania tekstu funkcja śledzi środek i promień najdłuższego palindromu, a na koniec zwraca najdłuższy palindrom w oryginalnej formie (bez separatorów i znaków krańcowych).

#### Parametry:
- `const char *text`: Tekst wejściowy, w którym należy znaleźć najdłuższy palindrom.

#### Zwracana wartość:
- `char *`: Najdłuższy palindrom znaleziony w tekście. Zwracany łańcuch znaków jest zakończony znakiem `'\0'` i zawiera tylko litery z oryginalnego tekstu, bez dodatkowych separatorów czy znaków krańcowych.

---

### `void szyfruj()`

#### Opis:

Funkcja  `szyfruj` pobiera ze standardowego wejścia dwa argumenty od użytkownika  
	- tekst do zaszyfrowania – niepusty ciąg znaków ASCII  
	- głębokość szyfru – dodatnia liczba naturalna   
   
Funkcja sprawdza poprawność wejścia, w przypadku podania nieprawidłowego wyświetla komunikat i ponownie oczekuje na wejście.
Gdy otrzyma oba parametry, umieszcza litery w odpowiednich dla nich rzędach i na koniec wypisuje na standardowe wyjście zaszyfrowany tekst.

#### Parametry i zwracana wartość
Funkcja nie przyjmuje żadnych parametrów, ani nic nie zwraca

---

### `char* readString()`

#### Opis:

Jest to funkcja pomocnicza, która zapisuje podane przez użytkownika argumenty jako ciągi znaków.
Funkcja alokuje dynamicznie tablicę i dopóki użytkownik nie zakończy wpisywania klawiszem ENTER, zapisuje w niej podane znaki.


#### Parametry i zwracana wartość
Funkcja nie przyjmuje żadnych argumentów
  
Zwraca `char *` - ciąg znaków w której zapisane są dane podane ze standardowego wejścia przez użytkownika.

---

### `void statystyki(const char *text, TextStats *stats)`

#### Opis:
Funkcja `statystyki` analizuje podany tekst i oblicza szczegółowe statystyki związane z jego zawartością.

#### Jak działa:
1. **Inicjalizacja struktury**: Wszystkie pola struktury `TextStats` są zerowane na początku.
2. **Iteracja przez tekst**: Funkcja przechodzi przez każdy znak w tekście i analizuje go:
   - Zlicza znaki alfabetyczne, cyfry, znaki specjalne, wyrazy, zdania oraz akapity.
   - Oblicza minimalną, maksymalną i średnią długość słów oraz zdań.
   - Wyznacza złożoność leksykalną na podstawie unikalnych słów.
3. **Aktualizacja tablicy**: Tablica `tablica_liter` w strukturze jest aktualizowana, aby przechowywać liczbę wystąpień każdej litery alfabetu (zarówno małych, jak i wielkich).

#### Parametry:
- `const char *text`: Tekst wejściowy, który ma zostać przeanalizowany.
- `TextStats *stats`: Wskaźnik do struktury, w której zostaną zapisane wyniki analizy.

#### Struktura `TextStats`:
```c
typedef struct {
    int liczba_znakow;                // Liczba wszystkich znaków w tekście
    int liczba_liter;                 // Liczba liter (od a do z oraz od A do Z)
    int liczba_wyrazow;               // Liczba wyrazów w tekście
    int liczba_zdan;                  // Liczba zdań w tekście
    int liczba_akapitow;              // Liczba akapitów w tekście
    int liczba_znakow_specjalnych;    // Liczba znaków specjalnych (!, @, #, itp.)
    int liczba_cyfr;                  // Liczba cyfr w tekście
    int min_dlugosc_slowa;            // Minimalna długość słowa
    int max_dlugosc_slowa;            // Maksymalna długość słowa
    float srednia_dlugosc_slowa;      // Średnia długość słowa
    float srednia_dlugosc_zdania;     // Średnia długość zdania
    float zlozonosc_leksykalna;       // Złożoność leksykalna tekstu (np. unikalne słowa / wszystkie słowa)
    int tablica_liter[52];            // Tablica wystąpień liter (0-25: a-z, 26-51: A-Z)
} TextStats;
```

#### Zwracana wartość:
- Funkcja nie zwraca wartości. Wyniki są zapisane w strukturze `TextStats`, na którą wskazuje parametr `stats`.

---

### `void wyszukiwanie_wzorca(const char *text, const char *pattern)`

#### Opis:
Funkcja wyszukuje wszystkie wystąpienia wzorca (pattern) w podanym tekście (text) i wypisuje ich pozycje.

#### Jak działa:
1. **Iteracja przez tekst**: Funkcja przeszukuje tekst znak po znaku, próbując dopasować wzorzec od bieżącej pozycji.
2. **Porównanie znaków**: Porównuje ciągi znaków w tekście z wzorcem.
3. **Wynik**: Jeśli wzorzec zostanie znaleziony, wypisuje indeks początkowej pozycji wzorca.

#### Parametry:
- const char *text: Tekst, w którym szukamy wzorca.
- const char *pattern: Wzorzec, który ma zostać znaleziony.

#### Zwracana wartość:
Funkcja nie zwraca wartości. Wyniki są wypisywane na standardowe wyjście.

---

### `void wyszukiwanie_znaku_specjalnego(const char* text, const char *znak)`

#### Opis:
Funkcja wyszukuje podany znak specjalny (znak) w tekście (text) i wypisuje jego pozycje.

#### Jak działa:
1. **Iteracja przez tekst**: Funkcja przeszukuje tekst znak po znaku.
2. **Porównanie**: Sprawdza, czy aktualny znak w tekście odpowiada podanemu znakowi specjalnemu.
3. **Wynik**: Wypisuje indeksy wystąpień znaku specjalnego.

#### Parametry:
- const char *text: Tekst wejściowy, w którym szukamy znaku.
- const char *znak: Znak specjalny, który ma zostać znaleziony.

#### Zwracana wartość:
Funkcja nie zwraca wartości. Wyniki są wypisywane na standardowe wyjście.

---

### `void ignorowanie_wielkosci_liter(const char* text, const char *pattern)`

#### Opis:
Funkcja wyszukuje wzorzec (pattern) w tekście (text) z ignorowaniem wielkości liter.

#### Jak działa:
1. **Konwersja znaków**: Tekst i wzorzec są konwertowane do wspólnego formatu (np. małych liter).
2. **Porównanie**: Funkcja przeszukuje tekst podobnie jak w przypadku funkcji wyszukiwania wzorca.
3. **Wynik**: Wypisuje pozycje dopasowań wzorca, ignorując wielkość liter.

#### Parametry:
- const char *text: Tekst, w którym szukamy wzorca.
- const char *pattern: Wzorzec, który ma zostać znaleziony.

#### Zwracana wartość:
Funkcja nie zwraca wartości. Wyniki są wypisywane na standardowe wyjście.

---

### `void wypisz_tekst_wersja1(const char* text, int x, int pattern_len)`

#### Opis:
Funkcja wypisuje fragment tekstu (text), rozpoczynając od pozycji x i obejmując pattern_len znaków.

#### Jak działa:
1. **Pobranie fragmentu**: Wyodrębnia podciąg tekstu o długości pattern_len, zaczynając od pozycji x.
2. **Wypisanie**: Wypisuje wybrany fragment tekstu na standardowe wyjście.

#### Parametry:
- const char *text: Tekst wejściowy.
- int x: Indeks początkowy fragmentu tekstu.
- int pattern_len: Długość fragmentu tekstu do wypisania.

#### Zwracana wartość:
Funkcja nie zwraca wartości. Fragment tekstu jest wypisywany na standardowe wyjście.

---

### `void wypisz_tekst_wersja2(const char* text, int x, int pattern_len)`

#### Opis:
Funkcja wypisuje fragment tekstu (text) w formacie, który podkreśla dopasowany wzorzec.

#### Jak działa:
1. **Pobranie fragmentu**: Wyodrębnia podciąg tekstu o długości pattern_len, zaczynając od pozycji x.
2. **Formatowanie**: Oznacza dopasowany wzorzec w specjalny sposób (np. za pomocą nawiasów).
3. **Wypisanie**: Wypisuje sformatowany fragment tekstu na standardowe wyjście.

#### Parametry:
- const char *text: Tekst wejściowy.
- int x: Indeks początkowy fragmentu tekstu.
- int pattern_len: Długość fragmentu tekstu do wypisania.

#### Zwracana wartość:
Funkcja nie zwraca wartości. Wyniki są wypisywane na standardowe wyjście.

---

### `void wypisanie_statystyk_liter(TextStats stats)`

#### Opis:
Funkcja wypisuje statystyki liter zapisane w strukturze TextStats.

#### Jak działa:
1. **Iteracja przez statystyki**: Przechodzi przez strukturę TextStats.
2. **Wypisanie**: Wypisuje liczbę wystąpień każdej litery w tekście w przejrzystym formacie.

#### Parametry:
- TextStats stats: Struktura zawierająca liczności wystąpień liter od a do z.

#### Zwracana wartość:
Funkcja nie zwraca wartości. Wyniki są wypisywane na standardowe wyjście.

---

### `int zliczanie_wzorca(const char *text, const char *pattern)`

#### Opis:
Funkcja zlicza liczbę wystąpień wzorca (pattern) w tekście (text).

#### Jak działa:
1. **Iteracja przez tekst**: Przeszukuje tekst znak po znaku.
2. **Porównanie**: Sprawdza, czy fragment tekstu od bieżącej pozycji odpowiada wzorcowi.
3. **Zliczanie**: Każde dopasowanie zwiększa licznik o 1.

#### Parametry:
- const char *text: Tekst, w którym szukamy wzorca.
- const char *pattern: Wzorzec, który ma zostać zliczony.

#### Zwracana wartość:
- int: Liczba wystąpień wzorca w tekście.

---

### `void podmiana_wzorca(const char *text, const char *pattern, const char *replacement, char *result)`

#### Opis:
Funkcja `podmiana_wzorca` pozwala na znalezienie wszystkich wystąpień wzorca w tekście i zastąpienie ich innym ciągiem znaków.

#### Jak działa:
1. **Wyszukiwanie wzorca**: Funkcja przeszukuje tekst w celu znalezienia wszystkich wystąpień zadanego wzorca znaków.
2. **Zastąpienie wzorca**: Dla każdego wystąpienia wzorca, jest on zastępowany ciągiem znaków wskazanym w parametrze `replacement`.
3. **Kopiowanie tekstu**: Nowy tekst z podmienionymi wzorcami jest kopiowany do bufora wynikowego `result`.

#### Parametry:
- `const char *text`: Tekst wejściowy, w którym ma być przeprowadzona operacja podmiany.
- `const char *pattern`: Wzorzec znaków, który ma zostać zastąpiony.
- `const char *replacement`: Ciąg znaków, który zastąpi znaleziony wzorzec.
- `char *result`: Bufor wynikowy, do którego zostanie zapisany nowy tekst z podmienionymi wzorcami. Musi być wystarczająco duży, aby pomieścić wynik.

#### Zwracana wartość:
- Funkcja nie zwraca wartości. Wynik operacji jest zapisywany w buforze `result`.

---

### `void zwolnij(char **tablica, int liczba)`

#### Opis:
Funkcja zwalnia pamięć zarezerwowaną dla tablicy wskaźników oraz pamięć, na którą wskazują poszczególne elementy tablicy.

#### Jak działa:
1. Iteruje przez elementy tablicy wskaźników.
2. Zwalnia pamięć każdego elementu.
3. Zwalnia pamięć samej tablicy wskaźników.

#### Parametry wejściowe:
- `char **tablica`: Wskaźnik na dynamicznie alokowaną tablicę wskaźników.
- `int liczba`: Liczba elementów w tablicy.

#### Zwracana wartość:
Funkcja nie zwraca wartości.

---

### `int porownaj_slowo(const void *a, const void *b)`

#### Opis:
Funkcja porównuje dwa słowa na podstawie ich długości i ustawia je w kolejności rosnącej.

#### Jak działa:
1. Odczytuje długości dwóch ciągów znaków wskazywanych przez wskaźniki `a` i `b`.
2. Zwraca wartość porównania (ujemną, zero lub dodatnią) w zależności od różnicy długości.

#### Parametry wejściowe:
- `const void *a`: Wskaźnik na pierwszy element do porównania (wskaźnik na wskaźnik).
- `const void *b`: Wskaźnik na drugi element do porównania (wskaźnik na wskaźnik).

#### Zwracana wartość:
- Liczba całkowita:
  - Ujemna, jeśli długość pierwszego słowa jest mniejsza.
  - Zero, jeśli długości są równe.
  - Dodatnia, jeśli długość pierwszego słowa jest większa.

---

### `char **wczytaj_slownik(const char *nazwa_pliku, int *rozmiar_slownika)`

#### Opis:
Funkcja wczytuje dane z pliku tekstowego, zapisuje je w dynamicznie alokowanej tablicy wskaźników na ciągi znaków oraz sortuje je używając funkcji `porownaj_slowo`.

#### Jak działa:
1. Otwiera plik o podanej nazwie.
2. Odczytuje słowa z pliku i zapisuje je w dynamicznie alokowanej tablicy.
3. Sortuje tablicę przy użyciu funkcji `qsort` i funkcji pomocniczej `porownaj_slowo`.
4. Zapisuje rozmiar wczytanego słownika do zmiennej wskazywanej przez `rozmiar_slownika`.

#### Parametry wejściowe:
- `const char *nazwa_pliku`: Wskaźnik na ciąg znaków reprezentujący nazwę pliku, z którego ma wczytać dane.
- `int *rozmiar_slownika`: Wskaźnik na zmienną, gdzie zostanie zapisany rozmiar wczytanego słownika.

#### Zwracana wartość:
- `char **`: Dynamicznie alokowana tablica wskaźników zawierająca wczytane słowa.
- `NULL`, jeśli wystąpił błąd otwarcia pliku lub alokacji pamięci.

---

### `int najlepszy_podzial(const char *tekst, char **slownik, int rozmiar_slownika, char ***wynik, int *licznik, char ***najlepszy, int *najlepsza_liczba)`

#### Opis:
Funkcja służy do rekursywnego znajdowania najlepszego podziału tekstu na słowa w oparciu o dostarczoną listę słów (tylko dla języka polskiego).

#### Jak działa:
1. Wykorzystuje podejście rekurencyjne do przeszukiwania wszystkich możliwych podziałów tekstu.
2. Sprawdza dopasowanie podziałów z dostarczonym słownikiem słów.
3. Wybiera podział tekstu na najmniejszą liczbę słów.
4. Zapisuje najkrótszy podział w dynamicznie alokowanej tablicy wskaźników.

#### Parametry wejściowe:
- `const char *tekst`: Ciąg znaków reprezentujący tekst do podziału.
- `char **slownik`: Tablica wskaźników zawierająca słowa wczytane z wcześniej zdefiniowanego słownika.
- `int rozmiar_slownika`: Liczba słów w słowniku.
- `char ***wynik`: Dynamicznie alokowana tablica wskaźników przechowująca aktualny podział tekstu na słowa.
- `int *licznik`: Licznik określający liczbę słów w bieżącym podziale.
- `char ***najlepszy`: Dynamicznie alokowana tablica wskaźników przechowująca najkrótszy podział tekstu na słowa.
- `int *najlepsza_liczba`: Liczba słów w najkrótszym podziale.

#### Zwracana wartość:
- Liczba całkowita:
  - 0, jeśli funkcja zakończyła działanie poprawnie.
  - -1, jeśli wystąpił błąd alokacji pamięci.

---

### `char **podziel_na_zdania(const char *tekst, int *liczba_zdan)`

#### Opis:
Funkcja dzieli tekst na pojedyncze zdania, wykorzystując określone znaki końca zdania (., !, ?).

#### Jak działa:
1. Iteruje przez podany tekst i identyfikuje znaki końca zdania.
2. Tworzy dynamicznie alokowaną tablicę wskaźników na ciągi znaków, gdzie każde zdanie jest osobnym elementem.
3. Zapisuje liczbę znalezionych zdań do zmiennej wskazywanej przez `liczba_zdan`.

#### Parametry wejściowe:
- `const char *tekst`: Ciąg znaków reprezentujący tekst, który ma zostać podzielony na zdania. Jeśli wartość jest NULL, funkcja natychmiast zwraca NULL.
- `int *liczba_zdan`: Wskaźnik na zmienną, do której funkcja zapisze liczbę znalezionych zdań. Jeśli wskaźnik jest NULL, funkcja zwraca NULL.

#### Zwracana wartość:
- `char **`: Dynamicznie alokowana tablica wskaźników, gdzie każdy element wskazuje na jedno zdanie.
- `NULL`, jeśli wystąpił błąd alokacji pamięci.

---

### `void polacz_wyniki_do_ciagu(char **zdania, int liczba_zdan, char **wynik, char **slownik, int rozmiar_slownika)`

#### Opis:
Funkcja łączy zdania podzielone na słowa w jeden ciąg znaków, wykorzystując zbiór słów oraz funkcję `najlepszy_podzial` do podziału każdego zdania.

#### Jak działa:
1. Iteruje przez podaną tablicę zdań.
2. Dla każdego zdania stosuje funkcję `najlepszy_podzial` w celu podziału na słowa.
3. Łączy podzielone zdania w jeden ciąg znaków, który jest przechowywany w dynamicznie alokowanej pamięci.

#### Parametry wejściowe:
- `char **zdania`: Tablica wskaźników na zdania (char *), które mają zostać przetworzone i połączone w jeden ciąg znaków.
- `int liczba_zdan`: Liczba elementów w tablicy `zdania` (czyli liczba zdań).
- `char **wynik`: Wskaźnik na dynamicznie alokowany ciąg znaków, który będzie przechowywał połączony wynik.
- `char **slownik`: Tablica wskaźników zawierająca słowa wczytane ze słownika.
- `int rozmiar_slownika`: Liczba słów w słowniku.

#### Zwracana wartość:
Funkcja nie zwraca wartości bezpośrednio, ale wynik działania zapisuje w dynamicznie alokowanej zmiennej `*wynik`. Jeśli wystąpi błąd alokacji pamięci, funkcja nie modyfikuje `*wynik`.

---

### `void sprawdz_gramatyke(const char *tekst)`

#### Opis:
Funkcja sprawdza podstawowe zasady gramatyki w podanym ciągu tekstowym.

#### Jak działa:
1. Weryfikuje, czy zdania zaczynają się od wielkiej litery.
2. Sprawdza, czy po znakach interpunkcyjnych występują odpowiednie spacje.
3. Weryfikuje, czy nie ma zbyt wielu spacji między słowami.
4. Wypisuje komunikaty:
   - "Tekst jest gramatycznie poprawny" w przypadku braku błędów.
   - Informacje o znalezionych błędach i ich lokalizacji w przeciwnym przypadku.

#### Parametry wejściowe:
- `const char *tekst`: Ciąg znaków, który ma zostać sprawdzony pod względem gramatycznym.

#### Zwracana wartość:
Funkcja nie zwraca wartości, lecz wypisuje odpowiednie komunikaty na standardowe wyjście.

---

### `std::string base64::encode1421(const std::string_view input)`

#### Opis:
Funkcja `encode1421` koduje podany tekst (`input`) przy pomocy *base64*, wykorzystując specyfikację z RFC 1421.
Istnieją analogiczne funkcje dla następujących RFC: 2045, 2152, 3501, 4648.4 (4648_4), 4648.5 (4648_5), 4880.

#### Parametry:
- `const std::string_view input`: Tekst wejściowy, który zostanie zakodowany.

#### Zwracana wartość:
- `std::string`: Nowy napis zawierający zakodowany tekst.

---

### `std::optional<std::string> base64::decode1421(const std::string_view input)`

#### Opis:
Funkcja `encode1421` dekoduje podany tekst (`input`) przy pomocy *base64*, wykorzystując specyfikację z RFC 1421.
Istnieją analogiczne funkcje dla następujących RFC: 2045, 2152, 3501, 4648.4 (4648_4), 4648.5 (4648_5), 4880.

#### Parametry:
- `const std::string_view input`: Tekst wejściowy, który zostanie zdekodowany.

#### Zwracana wartość:
- `std::string`: Nowy napis zawierający zdekodowany tekst lub brak wartości w przypadku błędu dekodowania.

---

### `void arithmetic::compress(std::istream &input, bitio::bit_ostream &output)`

#### Opis:
Funkcja kompresuje strumień `input` przy pomocy adaptacyjnego kodowania arytmetycznego do strumienia `output`.

#### Parametry:
- `std::istream &input`: Strumień wejściowy, zawierający tekst do skompresowania.
- `bitio::bit_ostream &output`: Bitowy strumień wyjściowy, do którego zostaną zapisane skompresowane dane.

---

### `void arithmetic::compress(bitio::bit_istream &input, std::ostream &output)`

#### Opis:
Funkcja dekompresuje strumień `input` przy pomocy adaptacyjnego kodowania arytmetycznego do strumienia `output`.

#### Parametry:
- `bitio::bit_istream &input`: Bitowy strumień wejściowy, zawierający skompresowany tekst.
- `std::ostream &output`: Strumień wyjściowy, do którego zostaną zapisane zdekompresowane dane.

