# Zadanie: Pokedex (10p)

W tym zadaniu należy stworzyć interaktywny [Pokédex](https://pokemon.fandom.com/wiki/Pok%C3%A9dex). W tym celu należy dodać do pliku [pokedex.html](./pokedex.html) odpowiednie skrypty.

Plik zawiera częściowe dane, które należy usunąć. Można go także dowolnie edytować, jeśli zajdzie taka potrzeba. Częścią zadania nie jest jednak przygotowanie wyglądu strony i nie będzie to oceniane.

W celu wykonania zadania należy wykorzystać [pokeapi](https://pokeapi.co/), w szczególności może się przydać [dokumentacja](https://pokeapi.co/docs/v2).

## Materiały

Przydatne mogą być:

- [getElementById](https://developer.mozilla.org/en-US/docs/Web/API/Document/getElementById)
- [Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
- [Asynchronous JavaScript](https://developer.mozilla.org/en-US/docs/Learn_web_development/Extensions/Async_JS/Introducing)
- [addEventListener](https://developer.mozilla.org/en-US/docs/Web/API/EventTarget/addEventListener)

## Wymagania

- Po lewej stronie należy wyświetlić listę Pokémonów, wpisując ich imiona jako kolejne elementy listy (`li`). Należy wyświetlić pierwsze 151 Pokémonów.

  - Zgodnie ze stroną [odnośnie listy i paginacji](https://pokeapi.co/docs/v2#resource-listspagination-section), do wylistowania Pokémonów należy użyć endpointu `pokemon-species`.
  - Żeby pobrać odpowiednio długą listę, należy dodać parametr `limit`, zgodny z dokumentacją.

- Po kliknięciu w Pokémona na liście należy wypełnić odpowiednie dane:

  - Dane powinny znaleźć się w `div`ie o klasie `pokemon-content`, wyświetlonym jako `flex`.
  - Część danych będzie dostępna w endpointcie [`pokemon-species`](https://pokeapi.co/docs/v2#pokemon-species), a część w [`pokemon`](https://pokeapi.co/docs/v2#pokemon).

    - Endpoint `pokemon-species` można wywołać z ID bądź nazwą Pokémona z listy.
    - Aby znaleźć odpowiadający adres w endpointcie `pokemon`, należy w danych zwróconych z `pokemon-species` odnaleźć tablicę [`PokemonSpeciesVariety`](https://pokeapi.co/docs/v2#pokemonspeciesvariety). Jednym z jej elementów będzie obiekt z ustawionym `is_default` na `true`. W tym obiekcie znajduje się URL do endpointu `pokemon` pokemona którego dane należy wyświetlić.

  - Nazwa Pokémona to nazwa gatunku, taka sama jak ta wyświetlona na liście; można ją również znaleźć w danych `pokemon-species`.

    - Nazwa powinna znaleźć się w elemencie `h2`.

  - Adres obrazka znajduje się w danych z endpointu `pokemon`, w obiekcie [`PokemonSprites`](https://pokeapi.co/docs/v2#pokemonsprites).

    - Można założyć, że każdy Pokémon ma zdefiniowany `front_default`, który jest adresem do obrazka.
    - Obrazek powinien być elementem `img` z klasą `pokemon-image`.

  - Typy Pokémona znajdują się w endpointcie `pokemon`, w tablicy [`PokemonType`](https://pokeapi.co/docs/v2#pokemontype).

    - Typy należy umieścić w `div`ie z klasą `types`, jako osobne `span`y z klasą `type`.

  - Statystyki Pokémona znajdują się w endpointcie `pokemon`, w tablicy [`PokemonStat`](https://pokeapi.co/docs/v2#pokemonstat).

    - Należy wyświetlić nazwę statystyki wraz z jej wartością (`base_stat`).
    - Statystyki powinny znaleźć się w `div`ie o klasie `stats`. Każda statystyka to `div` z klasą `stat`, zawierający dwa `span`y — jeden z nazwą, drugi z wartością.

  - Opis Pokémona znajduje się w endpointcie `pokemon-species`, w tablicy [`FlavorText`](https://pokeapi.co/docs/v2#flavortext).
    - W tablicy znajduje się wiele opisów. Należy wyświetlić dowolny, którego język to angielski (`en`).
    - Tekst opisu znajduje się pod kluczem `flavor_text`, jednak może zawierać znaki specjalne z oryginalnych gier. Należy je usunąć.
      - W dokumentacji API opisano ten problem, wraz z przykładowym rozwiązaniem (do dostosowania do JavaScriptu).
    - Opis należy umieścić w `div`ie z klasą `flavor-text`.

- W przypadku wystąpienia błędu (zarówno przy pobieraniu listy, jak i danych Pokémona), należy zamiast danych wyświetlić `div` z klasą `error-text` i napisem `Failed to load Pokémon data.`

- Podczas ładowania (zarówno listy, jak i danych konkretnego Pokémona) należy wyświetlić `div` z klasą `loading`.

  - Pełną liczbę punktów można uzyskać tylko, jeśli komunikat o ładowaniu znika dopiero po załadowaniu **wszystkich** danych (z `pokemon-species`, z `pokemon`, oraz po pełnym załadowaniu obrazka Pokémona).
    <details>
    <summary>Podpowiedź</summary>

    > Problemem jest oczekiwanie na załadowanie obrazka. Jest na to kilka sposobów. Można podpiąć się do eventu `load` albo `onload` obrazka, poprzez napisanie własnego `Promise` albo za pomocą Event Listenera.
    > Bardziej nowoczesnym sposobem wydaje się być jednak preload obrazka. Używając funkcji `decode`, można to zrobić na przykład w ten sposób:

    ```js
    async function preloadImage(src) {
      const img = new Image();
      img.src = src;
      await img.decode();
      return img;
    }
    ```

    > Wywołanie tej funkcji z odpowiednim adresem załaduje obrazek. Można zaczekać, aż ładowanie się skończy, a następnie przepiąć źródło obrazka w DOM na źródło tego obrazka (albo zwyczajnie wpiąć zwrócony obrazek do DOMu).

    </details>
