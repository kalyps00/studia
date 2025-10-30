# Zadanie: Todo Lista – Wersja React

Twoim zadaniem będzie przygotowanie listy zadań (todo) zgodnej z poleceniem z [Listy 7](../../W07/Lab/Lab.md), tym razem z użyciem Reacta. Możesz skopiować style i HTML z tego zadania.

Lista powinna być stworzona z użyciem Reacta i TypeScriptu. Wszystkie funkcje muszą zawierać odpowiednie typy – unikaj stosowania typu `any`.

Do stworzenia aplikacji należy użyć [Vite](https://vite.dev/).

### Wymagania:

1. Należy zachować wszystkie funkcjonalności obecne w liście zadań z Listy 7:
   - dodawanie,
   - usuwanie,
   - zmiana kolejności,
   - oznaczanie/odznaczanie jako zakończone,
   - czyszczenie całej listy.
1. W zadaniu należy korzystać z natywnych możliwości Reacta. W szczególności **zabronione** jest bezpośrednie manipulowanie DOM-em (np. użycie `document.getElement...`).
1. Listę elementów TODO należy przechowywać z użyciem [useReducer](https://react.dev/reference/react/useReducer).
   - Funkcja zawierająca logikę reducera powinna znajdować się w osobnym pliku.
1. Lista powinna być podzielona na komponenty. Podział na komponenty jest w dużej mierze dowolny, jednak następujące komponenty **muszą** znaleźć się w rozwiązaniu:
   - Komponent renderujący listę zadań (część, która w oryginalnym pliku HTML znajdowała się w elemencie `main`),
   - Komponent renderujący formularz do dodawania nowego zadania (część z elementu `form`),
   - Komponent renderujący nagłówek listy (element `header` o klasie `todos-header__container`),
   - Komponent renderujący pojedynczy element listy (element `li`).
1. Zadbaj o odpowiednią strukturę folderów: może być ona dowolna, ale przemyśl, czy jest czytelna i potencjalnie łatwa do rozszerzenia.
