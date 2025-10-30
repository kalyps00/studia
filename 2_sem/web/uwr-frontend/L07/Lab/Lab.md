# Zadanie: Todo List (10p)

W tym zadaniu rozszerzysz gotową TODO-listę o funkcjonalności, dodając odpowiednie skrypty. Wszystkie pliki znajdziesz w folderze [todo-list](./todo-list/). Modyfikacja pozostałych plików jest dozwolona nie tylko w zakresie przykładowych danych (których usunięcie może okazać się konieczne).

Przykładowe dane prezentują strukturę dodawanych elementów. Poza tym, w odpowiednich miejscach w poniższej treści dodana będzie informacja o wymaganych przez konkretne elementy klasach.

Zadanie można zrobić na dwa sposoby: opierając się całkowicie o "stan" elementów, albo tworząc dodatkową tablicę, przechowującą listę elementów todo, i funkcję `render`, która na podstawie tej listy przygotuje odpowiednią strukturę strony. Wybierz jedno z tych dwóch podejść. Prowadzący ma prawo wymagać uzasadnienia twojego wyboru.

## Materiały

Przydać mogą się:

- [getElementById](https://developer.mozilla.org/en-US/docs/Web/API/Document/getElementById)
- [querySelector](https://developer.mozilla.org/en-US/docs/Web/API/Document/querySelector)
- [addEventListener](https://developer.mozilla.org/en-US/docs/Web/API/EventTarget/addEventListener)
- [preventDefault](https://developer.mozilla.org/en-US/docs/Web/API/Event/preventDefault)
- Ogólna wiedza na temat [Elementów](https://developer.mozilla.org/en-US/docs/Web/API/Element).

## Wymagania

- Todo lista powinna umożliwiać dodawanie elementów.
  - Dodawanie elementów powinno opierać się o `form`.
  - Nowy element powinien zostać dodany jako `li` do elementu `ul` (id: `todo-list`).
  - Element `li` powinien mieć klasę `todo__container`
  - Element `li` elementu wykonanego, powinien dodatkowo mieć klasę `todo__container--completed`
  - Wewnątrz elementu `li` znajdą się składowe
    - Każdy z nich bedzie miał klasę `todo-element`
    - Dodatkowo, każdy przycisk będzie miał klasę `todo-button`.
    - Specyfikacja elementów:
      - Element przechowujący nazwę, powinien być `div`em, z dodatkową klasą `todo-name`.
      - Przyciski ruchu w górę/dół powinny dodatkowo mieć adekwatne klasy (`move-up` i `move-down`). **Nie musisz** dbać o to by przycisk w górę nie pojawiał się w pierwszym, a przycisk w dół w ostatnim elemencie. Dba o to CSS.
      - Przycisk `Done` powinien pojawić się tylko dla elementu niewykonanego, a przycisk `Revert` tylko dla elementu wykonanego
      - Przycisk Remove
- Todo lista powinna umożliwić usunięcie elementu z listy za pomocą przycisku `Remove`.
- Todo lista powinna umożliwiać oznaczanie elementu jako wykonanego za pomocą przycisku `Done`
- Todo lista powinna umożliwiać odznaczenie elementu jako wykonanego za pomocą przycisku `Revert`.
- Counter, na górze listy (`Todo List (4 remaining) `) powinien zawsze zawierać liczbę obecnie pozostałych do wykonania zadań (zadań, nie oznaczonych jako wykonane).
- Przycisk clear all powinien umożliwiać całkowite wyczyszczenie listy (usunięcie wszystkich elementów).
- Przyciski "w górę" i "w dół" powinny umożliwić zamianę miejscami odpowiednich elementów.
