#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
// Funkcja zwalniająca pamięć przechowywaną w tablicy wskaźników
void zwolnij(char **tablica, int liczba);

// Funkcja sortująca słownik według długości słów w kolejności malejącej
int porownaj_slowo(const void *a, const void *b);

// Funkcja wczytująca słownik z pliku
char **wczytaj_slownik(const char *nazwa_pliku, int *rozmiar_slownika);


// Funkcja rekurencyjna znajdująca podział z minimalną liczbą słów
int najlepszy_podzial(const char *tekst, char **slownik, int rozmiar_slownika, char ***wynik, int *licznik, char ***najlepszy, int *najlepsza_liczba);

// Funkcja dzieląca tekst na zdania na podstawie znaków końca zdania
char **podziel_na_zdania(const char *tekst, int *liczba_zdan);

//funckja łaczy dzielenia słów i zdań by wynik był jedna zmienną
void polacz_wyniki_do_ciagu(char **zdania, int liczba_zdan, char **wynik, char **slownik, int rozmiar_slownika);

//sprawdza podstawowe zasady gramatyki - czy zdanie zaczyna sie dużą literą, czy po znakach interpunkcyjnych jest spacja, czy pomiędzy wyrazami jest spacja
void sprawdz_gramatyke(const char *tekst);
