# Lista 0

## Zad 2

Wyjątek to jakiś event, który powoduje przerwanie normalnego wykonania programu i wywołanie handlera, który to obsłuży następnie robimy jakąś inną akcję, wznawiamy lub kończymy program

#### hardware interrupt

- wywołany przez jakieś urządzenie spoza procesora, niezależnie od tego, co obecnie robił procesor np. jakiś adapter sieciowy, kontroler dysku lub układ zegara

#### traps

- celowo wywołane przez program w celu powiadomienia kernela o syscallu, czyli wywołaniu systemowym, np. czytaniu pliku (`read`), tworzeniu nowego procesu (`fork`) lub wyjściu z obecnego (`exit`) lub też breakpoint podczas debugowania

#### fault

- wyjąki, które system może jakoś naprawić. Przykładem jest page fault (potrzebna strona nie znajduje się w pamięci fizycznej), dzielenie przez 0 lub naruszenie dostępu do pamięci nie zawsze kończą jako błędy przez możliwośc naprawienia przyczyny i wznowienia programu

## Zad 3

Wektor przerwań to tablica z adresami handlerow do poszczegolnych urzadzen wtedy numer urzadzenia sluzy jako indeks w tej tablicy, Gdy urzadzenie zglosi przerwanie bierzmy ten adres procedury i ja odpalamy

- Przedpobraniem pierwszej isntrukcji procedury obsługi program odklada na stos bieżacy stan i przełącza się do kernel modea po natrafieniu na instruckje powrotu przywracamy stan ze stosu, user mode i wznawamiy dzialanie przerwanego procesu

- Musimy używać kernel modea bo wykonujemy np I/O operacje na sprzecie co w trybie usera jest nie mozliwe co dostosu to użytkownik może mieć zepsuty lub przepelniony stos stąd kernel używa własnego dodatkwo inne procesy niechcianie mogłyby grzebać w tych danych

## Zad 5

#### Składowe pliku wykonywalnego

- ELF haeder
  `readelf -h main`

  > - jest na początku i zawiera informacje na temat architektury sprzętu,
  >   rodzaju pliku oraz adresu pierwszej instrukcji programu (`Entry point address`)

- sekcje
  `readelf -S main`

  > - zawierają różne części programu, np. kod programu (`.text`), dane tylko
  >   do odczytu (`.rodata`), zmienne zainicjalizowane (`.data`) i symbole

- segmenty
  `readelf -l main`

  > - są częściami pliku, które system operacyjny ładuje do pamięci podczas
  >   uruchamiania programu

- nagłówki programu
  > - opisują segmenty, między innymi ich położenie w pliku, rozmiar,
  >   adres w pamięci oraz uprawnienia, np. odczyt, zapis i wykonywanie

#### Sekcja a segment

- sekcja służy głównie linkerowi i zawiera określony rodzaj danych programu
- segment służy systemowi operacyjnemu i mówi co należy załadować do pamięci
- jeden segment może zawierać kilka sekcji

#### Skąd system wie, gdzie załadować program?

- System odczytuje z nagłówków programu adresy segmentów i na ich podstawie
  umieszcza je w odpowiednich miejscach pamięci
- Adres pierwszej instrukcji znajduje w nagłówku ELF jako `Entry point address`.

## Zad 7

`volatile` informuje kompilator, że wartość zmiennej może zmienić się
niezależnie od aktualnego kodu programu. Dlatego przy każdym użyciu trzeba
odczytać ją z pamięci i nie wolno zastępować odczytów zapamiętaną wartością.

Przykłady użycia:

- rejestry urządzeń sprzętowych np zewnetrzy naped zmienia falge bo wlozylismy plyte
- zmienne globalne zmieniane przez np asynchroniczne procedury programu
