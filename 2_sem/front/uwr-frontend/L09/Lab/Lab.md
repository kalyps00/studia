# Zadanie: Harry Potter Guessing Game (10p)

W tym zadaniu trzeba będzie dodać typy do gotowej [gry](./game/) opartej na uniwersum Harry’ego Pottera, korzystającej z [API](https://wizard-world-api.herokuapp.com/swagger/index.html), którego dokumentacja może się okazać przydatna. W tym celu należy zmodyfikować znajdujący się tam plik JS.

## Materiały

Wszystkie potrzebne informacje można znaleźć w [dokumentacji TypeScriptu](https://www.typescriptlang.org/).

## Wymagania

- Dodaj plik `tsconfig.json`. Możesz to zrobić za pomocą komendy `tsc --init` (dostępnej po zainstalowaniu TypeScriptu komendą `npm i -g typescript`, lub z użyciem `npx -p typescript tsc`).

  - Przejrzyj opcje domyślnie zakomentowane w pliku. Zwróć szczególną uwagę na sekcję `/* Type Checking */`. Zdecyduj, które z tych opcji warto włączyć — uzasadnij swój wybór.

- Zacznij od dodania typów do tablic `elixirs` i `spells`.

  - Stwórz typy dla obu obiektów, korzystając z dokumentacji API.
  - Dodaj typy do zmiennych `elixirs` i `spells`.

- Dodaj typ do `validOption`, która będzie zawierała napis stanowiący rozwiązanie zagadki.

- W funkcji `fetchData` należy dodać typ do zmiennej `endpoint`.

  - Typ nie powinien być po prostu napisem — powinien adekwatnie reprezentować dostępne endpointy, z pomocą zmiennej `Endpoints`. Można to zrobić na dwa sposoby:
    - (Łatwiejszy): zmień obiekt `Endpoints` na `enum`.
    - (Bardziej zaawansowany): we współczesnym TypeScriptcie enumy są mniej popularne niż kiedyś. Możesz zamiast tego stworzyć typ `EndpointType`, który będzie reprezentował dane w obiekcie `Endpoints`. Typ powinien być dynamiczny — powinien automatycznie się zmieniać, jeśli obiekt `Endpoints` zostanie rozszerzony. [Tutaj](https://www.typescriptlang.org/docs/handbook/enums.html#objects-vs-enums) znajdziesz podpowiedź, jak to zrobić.
  - Sprawdź, czy twoje rozwiązanie działa, próbując wywołać `fetchData` z czymś znajdującym się w obiekcie `Endpoints` (np. `spells`) oraz czymś, co się tam nie znajduje.

- W funkcji `fetchAllData`, w metodach `filter`, zarówno `elixir`, jak i `spell` mają typ `any`. Spraw, by miały odpowiedni typ. Możesz to osiągnąć, nadając ten typ bezpośrednio w funkcjach, robiąc z funkcji `fetchData` funkcję generyczną albo w inny sposób — wybór należy do ciebie, pamiętaj jednak, że musisz umieć go uzasadnić.

- `getRandomElements`

  - Funkcja ma dwa argumenty: tablicę i liczbę elementów, które chcielibyśmy wybrać. Otypuj je.
    - Typ tablicy powinien być przedstawiony bez użycia `any`, za pomocą [funkcji generycznej](https://www.typescriptlang.org/docs/handbook/2/generics.html), tak by funkcja mogła przyjąć dowolną tablicę i zwrócić coś, co również ma typ elementów tej tablicy.
  - Zmienna `indexes` jest zbiorem, który jednak nie wie, że będzie zbiorem liczb. Nadaj jej odpowiedni typ.

- W podobny sposób jak dla funkcji `getRandomElements`, nadaj typ argumentowi funkcji `generateOptions`.

- Nadaj również typy argumentom funkcji `renderOptions`.

- Popraw błędy w `EventListener`ze na dole pliku:

  - `gameContainer` może być puste, jeśli nie znaleziono takiego elementu na stronie. My jednak wiemy, że taki element się tam znajduje. Napraw ten błąd, używając [operatora Non-null Assertion](https://www.typescriptlang.org/docs/handbook/2/everyday-types.html#non-null-assertion-operator-postfix-).
  - Wewnątrz `EventListener`a znajduje się błąd, który TypeScript pomógł nam wykryć. Wyjaśnij, na czym polega ten błąd i go napraw.

- Używając komendy `tsc` (bez dodatkowych parametrów), pokaż, że kod się kompiluje. Porównaj otrzymany plik z plikiem początkowym.

- W celu debugowania aplikacji przydatna może się okazać możliwość podglądu oryginalnego kodu w przeglądarce. Niestety, podczas podglądu strony w `devtools`, mimo że element o id `"game"` wskazuje na `eventListener`, wskazuje on na jego definicję w kodzie wygenerowanym przez `tsc` (jak to sprawdzić?). Spraw, by przeglądarka mogła wskazać oryginalny kod TypeScriptu.
  - Przydatne mogą się okazać opcje w `tsconfig.json`, w szczególności [ta](https://www.typescriptlang.org/tsconfig/sourceMap.html) oraz [ta](https://www.typescriptlang.org/tsconfig/#inlineSourceMap).
