# Zadanie: Kalkulator (10p)

Twoim zadaniem na tej liście będzie stworzenie prostego kalkulatora w TypeScriptcie, z użyciem biblioteki [mathjs](https://www.npmjs.com/package/mathjs). W tym celu wykorzystasz bundler [https://vite.dev/](vite).

Przykładowe rozwiązanie znajdziesz [tutaj](./example.gif).

## Wymagania

Poniższe wymagania nie są przedstawione jako lista kroków. W szczególności, warto najpierw skonfigurować środowisko (dodać bundler i obsługę eslinta), a potem zacząć implementować funkcjonalność.

1. Twój kalkulator powinien być napisany z użyciem TypeScripta, z użyciem najnowszych konwencji.
   1. Kod TypeScriptowy powinien być rozdzielony na przynajmniej dwa pliki.
1. Twój kalkulator powinien zawierać style, korzystające ze znanych konwencji (np. BEM), ułatwiających utrzymanie i zwiększające czytelność.
   1. Twój kalkulator **nie musi** być responsywny.
1. Twój kalkulator powinien być funkcjonalny:
   1. Powinna istnieć możliwość wpisywania dowolnych formuł z użyciem liczb, znaków mnożenia, dzielenia, dodawania, odejmowania i przecinka (liczb ułamkowych).
   1. Powinna istnieć możliwość usunięcia ostatniego znaku i wyczyszczenia całego napisu
   1. Powinna istnieć możliwość wykonania "obliczenia" działania, przy pomocy przycisku `=`.
   1. W przypadku błędu, na ekranie powinien pokazać się napis `Error`.
1. Aplikacja powinna korzystać z bundlera [https://vite.dev/](vite).
   1. **To wymaganie jest kluczowe**. Aplikacja która nie korzysta z bundlera, albo w której bundler nie spełnia funkcji budowania kodu gotowego na produkcję **nie będzie** oceniane.
1. Zmień domyślny port w którym aplikacja działa w trybie developerskim, zmieniając config.
   1. Nie nalezy tego robić przez argumenty wywołania: należy stworzyć plik konfiguracyjny `vite`.
