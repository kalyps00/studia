#include "podzial.h"
int main() {
    const char *plik_slownika = "polski.txt";
    int rozmiar_slownika;
    char **slownik = wczytaj_slownik(plik_slownika, &rozmiar_slownika);
    if (!slownik) {
        printf("Blad wczytywania slownika z pliku: %s\n", plik_slownika);
        return 1;
    }

    const char *tekst = "starymłynstałnaskrajuwioski.Oddawnanikttamniemieszkał.Pewnegodniadrzwiotworzyłsilnywiatr.Wśrodkuchłopiecznalazłdziwnąksięgę.Odtegodniamłynznowupracował.";
    int liczba_zdan;
    char **zdania = podziel_na_zdania(tekst, &liczba_zdan);
    if (!zdania) {
        printf("\nBlad podczas dzielenia tekstu na zdania.\n");
        zwolnij(slownik, rozmiar_slownika);
        return 1;
    }

    char *wynik = NULL;
    polacz_wyniki_do_ciagu(zdania, liczba_zdan, &wynik, slownik, rozmiar_slownika);

    // Wyświetlenie wynikowego podzielonego tekstu
    printf("\nPodzielony tekst:\n%s\n", wynik);

    // Sprawdzanie gramatyki na wynikowym tekście
    printf("\nSprawdzanie gramatyki:\n");
    sprawdz_gramatyke(wynik);

    free(wynik);
    zwolnij(zdania, liczba_zdan);
    zwolnij(slownik, rozmiar_slownika);

    return 0;
}
