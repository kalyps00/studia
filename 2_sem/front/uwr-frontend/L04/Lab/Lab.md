# Zadanie: Formularz Kontaktowy (10p)

Twoim zadaniem będzie stworzyć responsywny formularz kontaktowy. W przeciwieństwie do poprzednich zadań, w tym zadaniu samodzielnie zdefiniujesz **jak** formularz ma wyglądać, i jak będzie zaimplementowana responsywność. Można użyć flexboxa, grida, można używać mediaquery a można podejść do problemu zupełnie inaczej. Design może mieć kilka różnych wersji, a może być całkowicie płynny. Wybrane rozwiązanie należy oczywiście uargumentować: podać jego wady i zalety.

Choć zadanie jest dość otwarte, poniżej znajdują się wytyczne, definiujące minimalne wymagania które formularz musi spełnić.

## Przykład

Przykładowe rozwiązanie: [Pełny Rozmiar](./form_fullsize.png) ([wysoka rozdzielczość](./form_fullsize_fullres.png)), [Mały Rozmiar](./form_smallsize_fullres.png), [Telefon](./form_phone_fullres.png), [Duża Czcionka](./form_bigfont.png) ([wysoka rozdzielczość](./form_bigfont_fullres.png)).

## Materiały

W ramach tego zadania przydatne okazać się mogą materiały dotyczące [Grida](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Grid_Layout), [Flexboxa](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Flexible_Box_Layout/Basic_Concepts_of_Flexbox), a także [poradnik o makro-layoutach](https://web.dev/learn/design/macro-layouts/). Dodatkowo, w części formularzy wymagane będzie napisanie prostej walidacji. Do tego może przydać się [edytor regexów](https://regex101.com/).

## Wymagania

1.  Style powinny być łatwe w zarządzaniu i czytelne dla innych programistów. W tym celu użyj jednej z popularnych metodologii (np. BEM). Postaraj się, by wszystkie stylowane elementy posiadały odpowiednią klasę (chyba, że uważasz, że w danej sytuacji użycie innego selektora jest sensowniejsze).
1.  Formularz powinien znaleźć się na "karcie", zachowującą odpowiednie odstępy od brzegów ekranu, zależną od ilości dostępnego miejsca.
1.  Formularz powinien zawierać:
    1. Nagłówek, będący tekstem
    1. Imię (wymagane) - pole tekstowe
    1. Nazwisko - pole tekstowe
    1. E-mail (wymagane) - pole tekstowe
    1. Telefon - pole tekstowe
    1. Zapis do newslettera - checkbox
    1. Powód kontaktu (wymagane) - pole wyboru, z kilkoma opcjami (mogą być dowolne)
    1. Wiadomość (wymagane) - pole tekstowe, ale odpowiednio większe
    1. Przycisk "wyślij", który wysyła formularz
1.  Formularz powinien być odpowiednio skonstruowany. Każde pole powinno zawierać labelkę, pola input powinny mieć odpowiednie typy, a sam formularz powinien znaleźć się w odpowiednim tagu.
1.  Przycisk "wyślij" powinien być odpowiednio duży i zwracać uwagę
1.  Czcionka powinna zależeć od szerokości urządzenia użytkownika. Powinna być również zależna od wielkości czcionki preferowanej przez użytkownika, ale nie powinna rozrosnąć się zbyt bardzo.

    <details>
      <summary>Podpowiedź</summary>

    > Choć responsywna czcionka nie jest czymś standardowym, to w tym zadaniu chcemy przede wszystkim zapoznać się z możliwościami. Najbardziej standardowym sposobem by nadać czcionce wielkość zależną od wielkości urządzenia, jest użycie odpowiedniej jednostki (`vw`, `vh`, `vmin`, `vmax`: która jest tu najlepsza?) i nadanie czcionce głównej (tej z tagu `html`) odpowiedniej wielkości.
    >
    > By czcionka brała pod uwagę preferencje użytkownika, możemy użyć funkcji `calc` i dodać do czcionki jednostkę relatywną, np. `rem`.
    >
    > By czcionka zbyt bardzo się nie rozrosła, możemy użyć funkcji `clamp`.
    >
    > Przydać sie może: https://www.smashingmagazine.com/2022/01/modern-fluid-typography-css-clamp/

    </details>

1.  Jeśli użytkownik przegląda stronę na urządzeniu, na którym zaznacza rzeczy palcem, pole `checkbox`a może być ciężkie do zaznaczenia. Jako, że bardzo chcemy, by użytkownik mógł je z łatwością zaznaczyć, na tych urządzeniach pole wyboru powinno być trochę większe. _Uwaga:_ W tym zadaniu **nie możesz** założyć że urządzenie mobilne to takie z odpowiednio małym ekranem: musisz znaleźć inne rozwiązanie.

    <details>
      <summary>Podpowiedź</summary>

    > [To może sie przydać](https://developer.mozilla.org/en-US/docs/Web/CSS/@media/pointer)

    </details>

1.  Formularz powinien być walidowany:

    1.  Wymagane pola powinny rzeczywiście być wymagane
    1.  Pole E-mail powinno wymagać podania poprawnego adresu e-mail. Na potrzeby tego zadania możemy założyć, że poprawny adres email składa się z pewnego ciągu znaków, znaku "@", pewnego ciągu znaków, kropki i pewnego ciągu znaków.

        <details>
          <summary>Podpowiedź</summary>

        > Problem sprawdzenia, czy dany adres email jest poprawny, jest zaskakująco skomplikowany. Istnieją [skomplikowane wyrażenia regularne](http://www.ex-parrot.com/~pdw/Mail-RFC822-Address.html) rozwiązujące ten problem, jednak przepisywanie ich do HTML'a może okazać się nużące. "Pewny ciąg znaków" w treści jest celowo nieprecyzyjny: zdefiniuj go tak, by miało to jakiś sens. Celem zadania nie jest sprawdzić, czy potrafisz napisać skomplikowane wyrażenie regularne.
        >
        > Przydatny może okazać się atrybut `pattern`.

        </details>

    1.  Pole telefon powinno wymagać podania poprawnego telefonu. Możemy przyjąć, że wszystkie numery telefonów które nas interesują składają się z 9 cyfr (i tylko cyfr).
    1.  Wszystkie pola wypełnione błędnie powinny dawać odpowiednią wizualną informację, np. zapalając ramkę na czerwono.
         <details>
           <summary>Podpowiedź</summary>

        > Bardzo przydatna może okazać się pseudoklasa `:invalid`

         </details>

1.  Formularz powinien być responsywny
    1. Liczba kolumn powinna różnić się w zależności od ilości dostępnego miejsca. Jeśli miejsca jest więcej, kolumn powinno być więcej, jeśli miejsca jest mniej, kolumn może być mniej.
    1. Strona nie powinna się "rozjechać". W pewnym momencie karta nie powinna móc się bardziej zmniejszyć. Wielkość ta powinna być uzależniona od wielkości czcionki użytkownika. To znaczy, z dowolną wielkością czcionki i na dowolnym ekranie formularz powinien wyglądać w porządku, nawet jeśli oznaczałoby to pokazanie scrolla.
    1. Wielkość checkboxa powinna być również zależna od wielkości czcionki użytkownika.
