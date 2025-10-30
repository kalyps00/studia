# Task: Pokedex (10 points)

In this task, an interactive [Pokédex](https://pokemon.fandom.com/wiki/Pok%C3%A9dex) must be created. To do this, appropriate scripts should be added to the [pokedex.html](./pokedex.html) file.

The file contains partial data that should be removed. It can also be freely edited if needed. Styling the page is not part of the task and will not be evaluated.

To complete the task, [pokeapi](https://pokeapi.co/) must be used; the [documentation](https://pokeapi.co/docs/v2) may be particularly helpful.

## Resources

Useful references:

- [getElementById](https://developer.mozilla.org/en-US/docs/Web/API/Document/getElementById)
- [Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
- [Asynchronous JavaScript](https://developer.mozilla.org/en-US/docs/Learn_web_development/Extensions/Async_JS/Introducing)
- [addEventListener](https://developer.mozilla.org/en-US/docs/Web/API/EventTarget/addEventListener)

## Requirements

- On the left side, a list of Pokémon must be displayed, adding their names as consecutive `li` elements. The first 151 Pokémon should be shown.

  - According to the [resource list and pagination section](https://pokeapi.co/docs/v2#resource-listspagination-section), the `pokemon-species` endpoint must be used to list the Pokémon.
  - To retrieve a sufficiently long list, a `limit` parameter must be added, as described in the documentation.

- When a Pokémon on the list is clicked, relevant data should be filled in:

  - The data should appear in a `div` with the `pokemon-content` class, displayed as `flex`.
  - Some data will be available from the [`pokemon-species`](https://pokeapi.co/docs/v2#pokemon-species) endpoint, and some from the [`pokemon`](https://pokeapi.co/docs/v2#pokemon) endpoint.

    - The `pokemon-species` endpoint can be queried with the Pokémon's ID or name from the list.
    - To find the corresponding URL in the `pokemon` endpoint, the [`PokemonSpeciesVariety`](https://pokeapi.co/docs/v2#pokemonspeciesvariety) array in the `pokemon-species` data must be located. One of its elements will have `is_default` set to `true`. That object contains the URL to the `pokemon` endpoint for the Pokémon whose data must be displayed.

  - The name of the Pokémon is the species name, which is the same as the name displayed on the list; it can also be found in the `pokemon-species` data.

    - The name should appear in an `h2` element.

  - The image URL can be found in the `pokemon` endpoint response, in the [`PokemonSprites`](https://pokeapi.co/docs/v2#pokemonsprites) object.

    - It can be assumed that every Pokémon has a defined `front_default`, which is the image URL.
    - The image should be an `img` element with the `pokemon-image` class.

  - The Pokémon's types can be found in the `pokemon` endpoint, in the [`PokemonType`](https://pokeapi.co/docs/v2#pokemontype) array.

    - The types should be placed in a `div` with the `types` class, as separate `span` elements with the `type` class.

  - The Pokémon's stats can be found in the `pokemon` endpoint, in the [`PokemonStat`](https://pokeapi.co/docs/v2#pokemonstat) array.

    - Each stat name should be displayed along with its value (`base_stat`).
    - The stats should be placed in a `div` with the `stats` class. Each stat should be a `div` with the `stat` class, containing two `span` elements — one for the name, and one for the value.

  - The Pokémon description can be found in the `pokemon-species` endpoint, in the [`FlavorText`](https://pokeapi.co/docs/v2#flavortext) array.

    - The array contains many descriptions. Any description in English (`en`) may be shown.
    - The description text is under the `flavor_text` key, but may contain special characters from the original games. These must be removed.
      - The API documentation describes this problem, along with a sample solution (to be adapted to JavaScript).
    - The description should be placed in a `div` with the `flavor-text` class.

- In case of an error (either while fetching the list or the Pokémon data), a `div` with the `error-text` class and the message `Failed to load Pokémon data.` must be displayed instead of the content.

- During loading (both the list and a specific Pokémon’s data), a `div` with the `loading` class must be displayed.

  - Full points will be awarded only if the loading message disappears **after** **all** data has been fully loaded (`pokemon-species`, `pokemon`, and the Pokémon image).

    <details>
    <summary>Hint</summary>

    > The main issue is waiting for the image to finish loading. There are several ways to handle this. One can listen for the `load` or `onload` event on the image, by writing a custom `Promise` or using an Event Listener.
    > However, a more modern solution involves preloading the image using the `decode` method. For example:

    ```js
    async function preloadImage(src) {
      const img = new Image();
      img.src = src;
      await img.decode();
      return img;
    }
    ```

    > Calling this function with a valid URL will preload the image. One can wait for the loading to complete, and then either update the `src` of an image already in the DOM, or insert the loaded image directly.

    </details>
