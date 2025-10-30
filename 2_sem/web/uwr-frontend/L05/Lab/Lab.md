# Zadanie: Lista Zakupów (10p)

Twoim zadaniem jest stworzenie funkcji odpowiedzialnych za działanie listy zakupów. Używać będziesz tylko JavaScriptu, jednak funkcje, które napiszesz, będą mogły być w przyszłości użyte do stworzenia pełnej frontendowej strony.

W ramach tego zadania nie musisz implementować komunikacji z użytkownikiem – wystarczy możliwość wywoływania funkcji z odpowiednimi argumentami.

Na wykładzie, którego dotyczy to zadanie, nie omówiliśmy jeszcze składni **funkcji strzałkowych** (_arrow functions_). Możesz ich używać, ale pamiętaj, że prowadzący może zapytać o różnice między nimi a metodami poznanymi na wykładzie.

## Materiały

Do zadania jak zwykle przydać się może [MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide). Dobrym źródłem nauki JavaScriptu jest także [javascript.info](https://javascript.info/) (pamiętaj jednak, że na pierwszym wykładzie omówiliśmy tylko część tematów). W zadaniu będziesz pracować głównie z funkcjami i tablicami, dlatego warto przeczytać [przegląd funkcji](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Functions) oraz [dokumentację metod tablicowych](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array). Szczególnie przydatne będą `Array.prototype.push`, `Array.prototype.filter`, `Array.prototype.findIndex`, `Array.prototype.splice`, `Array.prototype.reduce`, `Array.prototype.map`, `Array.prototype.includes` oraz `Date.prototype.toDateString`.

## Lista wymagań

1. Każda napisana przez Ciebie funkcja powinna być udokumentowana za pomocą [jsDoc](https://jsdoc.app/index.html).
1. Na górze pliku zdefiniuj zmienną przechowującą listę produktów, początkowo pustą.
   - Zdefiniuj (w jsDoc) typ `Product` opisujący obiekt produktu:
     - Id produktu (`number`)
     - Nazwę (`string`)
     - Liczbę sztuk do zakupienia (`number`)
     - Datę, do której produkt powinien być zakupiony ([obiekt Date](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Date))
     - Status informujący, czy produkt został zakupiony (`boolean`)
     - Opcjonalną cenę za sztukę (dotyczy tylko zakupionych produktów)
   - Nadaj zmiennej typ tablicy obiektów `Product`.
1. Dodaj funkcję umożliwiającą dodawanie nowego produktu do listy.
   - Funkcja nie powinna przyjmować `id` – powinna je generować.
     - Możesz założyć, że losowa liczba z dużego zakresu będzie wystarczająco unikalna.
   - Funkcja nie powinna przyjmować obiektu `Date` – powinna tworzyć datę na podstawie podanego `stringa` (zakładamy poprawny format).
1. Dodaj możliwość usunięcia produktu z listy na podstawie `id`.
1. Dodaj możliwość edycji (na podstawie `id`) nazwy, statusu, liczby sztuk i daty zakupu produktu.
   1. Każde pole powinno być edytowalne w osobnej funkcji, edytującej tylko to jedno pole.
1. Dodaj możliwość zmiany kolejności produktów na liście.
   - Sposób zmiany kolejności pozostaje do Twojej decyzji – możesz np. umożliwić przesuwanie elementów w górę/dół, zamianę miejscami lub przesunięcie w dowolne miejsce.
1. Dodaj funkcję zwracającą listę produktów, które powinny zostać zakupione dziś (niezakupione produkty z dzisiejszą datą zakupu).
1. Dodaj możliwość wprowadzenia ceny dla zakupionych produktów.
   - Jeśli produkt nie jest oznaczony jako zakupiony, funkcja nie powinna nic zmieniać.
   - Upewnij się, że nie będzie możliwe przypisanie ceny do produktu, który nie jest zakupiony (w jakich sytuacjach mogłoby do tego dojść?).
1. Dodaj funkcję obliczającą koszt zakupów danego dnia.
   - Funkcja nie powinna przyjmować obiektu `Date` – powinna tworzyć datę na podstawie podanego `stringa` (zakładamy poprawny format).
   - Funkcja powinna działać nawet wtedy, gdy nie wszystkie zakupione produkty mają podaną cenę. Określ, jak powinna postępować w takich przypadkach.
1. Dodaj funkcję umożliwiającą masowe formatowanie listy zakupów.

   - Funkcja powinna przyjmować listę `id` produktów do zmodyfikowania oraz funkcję modyfikującą.
   - Możesz samodzielnie określić format funkcji modyfikującej – opisz go w komentarzu.
   - W przyszłości powinno być możliwe przekazanie funkcji, np. przewalutowującej ceny produktów, i zastosowanie jej do wybranych elementów listy.

   <details>
     <summary>Podpowiedź</summary>

   > W JavaScripcie można przekazywać funkcje jako argumenty do innych funkcji. Taką funkcję nazywa się `callbackiem`.
   >
   > Istnieją metody tablicowe umożliwiające wykonanie operacji na każdym elemencie i zwrócenie nowej tablicy. Wystarczy zastosować funkcję przekazaną jako parametr do elementów o odpowiednich `id` (pozostałe pozostają bez zmian).

   </details>

1. Przygotuj listę wywołań które będą prezentowały odpowiednie funkcjonalności.
