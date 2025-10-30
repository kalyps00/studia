#ifndef WIERSZE_H
#define WIERSZE_H
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Struktura reprezentująca wiersz tekstu podzielony na słowa.
typedef struct wiersz
{
    char **slowa;   // Tablica wskaźników na słowa w wierszu.
    int ilosc_slow; // Liczba słów w wierszu.
    int bufor_slow; // Rozmiar aktualnie zaalokowanego bufora na słowa.
} Wiersz;

// Tworzy nowy wiersz (inicjalizuje strukturę Wiersz).
// Zwraca wskaźnik na zaalokowaną strukturę lub NULL w przypadku błędu alokacji.
Wiersz *nowy();

// Wypisuje wszystkie słowa w wierszu na standardowe wyjście, oddzielone spacjami.
// Parametr w: wskaźnik na wiersz, który ma zostać wypisany.
void wypisz(Wiersz *w);

// Zwalnia pamięć zaalokowaną dla wiersza, w tym jego słów.
// Parametr w: wskaźnik na wiersz, którego pamięć ma zostać zwolniona.
void zwolnij_wiersz(Wiersz *w);

// Dodaje nowe słowo do wiersza, dynamicznie rozszerzając bufor, jeśli to konieczne.
// Parametry:
// - w: wskaźnik na wiersz, do którego dodawane jest słowo.
// - slowo: wskaźnik na ciąg znaków reprezentujący słowo.
void dodajslowo(Wiersz *w, char *slowo);

// Wczytuje linię tekstu ze standardowego wejścia, zwracając wskaźnik na nią.
// Linia jest alokowana dynamicznie, zakończona znakiem '\0'.
// Zwraca NULL, jeśli osiągnięto koniec wejścia lub wystąpił błąd alokacji.
char *readline();

// Dzieli wczytaną linię na słowa, tworząc nową strukturę Wiersz.
// Parametr linia: wskaźnik na linię tekstu do podzielenia.
// Zwraca wskaźnik na strukturę Wiersz lub NULL w przypadku błędu alokacji.
Wiersz *podzial(char *linia);

// Typ wskaźnika na funkcję porównującą dwa wiersze.
// Funkcja porównująca powinna zwracać:
// - liczbę ujemną, jeśli pierwszy wiersz powinien być przed drugim,
// - 0, jeśli wiersze są równe,
// - liczbę dodatnią, jeśli pierwszy wiersz powinien być za drugim.
typedef int (*comparator)(const Wiersz *, const Wiersz *);

// Funkcja porównująca dwa wiersze w celu ustalenia ich kolejności.
// Parametry:
// - w1: wskaźnik na pierwszy wiersz.
// - w2: wskaźnik na drugi wiersz.
// Zwraca wartość zgodną z zasadami funkcji porównującej.
int komperator(const Wiersz *w1, const Wiersz *w2);

// Sortuje tablicę wierszy przy użyciu wskazanej funkcji porównującej.
// Parametry:
// - tablica: wskaźnik na tablicę wskaźników na wiersze do posortowania.
// - n: liczba elementów w tablicy.
// - komperator: wskaźnik na funkcję porównującą.
void sort(Wiersz **tablica, size_t n, comparator komperator);

#endif