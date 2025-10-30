#include "podzial.h"
void zwolnij(char **tablica, int liczba) {
    if (tablica) {
        for (int i = 0; i < liczba; i++) {
            free(tablica[i]);
        }
        free(tablica);
    }
}
int porownaj_slowo(const void *a, const void *b) {
    const char *slowo_a = *(const char **)a;
    const char *slowo_b = *(const char **)b;
    return strlen(slowo_a) - strlen(slowo_b);
}
char **wczytaj_slownik(const char *nazwa_pliku, int *rozmiar_slownika) {
    FILE *plik = fopen(nazwa_pliku, "r");
    if (!plik) {
        return NULL;
    }
    char **slownik = NULL;
    char linia[128];
    int licznik = 0;
    while (fgets(linia, sizeof(linia), plik)) {
        linia[strcspn(linia, "\n")] = '\0';
        char **tmp = (char**)realloc(slownik, (licznik + 1) * sizeof(char *));
        if (!tmp) {
            for (int i = 0; i < licznik; i++) free(slownik[i]);
            free(slownik);
            fclose(plik);
            return NULL;
        }
        slownik = tmp;
        slownik[licznik] = strdup(linia);
        if (!slownik[licznik]) {
            for (int i = 0; i < licznik; i++) free(slownik[i]);
            free(slownik);
            fclose(plik);
            return NULL;
        }
        licznik++;
    }
    fclose(plik);
    qsort(slownik, licznik, sizeof(char *), porownaj_slowo);
    *rozmiar_slownika = licznik;
    return slownik;
}
int najlepszy_podzial(const char *tekst, char **slownik, int rozmiar_slownika, char ***wynik, int *licznik, char ***najlepszy, int *najlepsza_liczba) {
    if (*tekst == '\0') {
        if (*najlepsza_liczba == -1 || *licznik < *najlepsza_liczba) {
            zwolnij(*najlepszy, *najlepsza_liczba);
            *najlepszy = (char**)malloc(*licznik * sizeof(char *));
            if (!*najlepszy) return 0;
            for (int i = 0; i < *licznik; i++) {
                (*najlepszy)[i] = strdup((*wynik)[i]);
                if (!(*najlepszy)[i]) return 0;
            }
            *najlepsza_liczba = *licznik;
        }
        return 1;
    }
    const char *znaki_interpunkcyjne = ".,!?";

    for (int i = 0; i < rozmiar_slownika; i++) {
        size_t dlugosc_slowa = strlen(slownik[i]);
        const char *tekst_po_slowniku = tekst + dlugosc_slowa;
        int dopasowanie = 1;
        int zmniejszono[dlugosc_slowa];
        memset(zmniejszono, 0, dlugosc_slowa * sizeof(int));
        for (size_t j = 0; j < dlugosc_slowa; j++) {
            if (tolower((unsigned char)tekst[j]) != tolower((unsigned char)slownik[i][j])) {
                dopasowanie = 0;
                break;
            }
            if (isupper((unsigned char)tekst[j])) {
                zmniejszono[j] = 1;
            }
        }
        if (!dopasowanie) continue;
        char znak_interpunkcyjny = '\0';
        if (*tekst_po_slowniku && strchr(znaki_interpunkcyjne, *tekst_po_slowniku)) {
            znak_interpunkcyjny = *tekst_po_slowniku;
            tekst_po_slowniku++;
        }
        char **tmp = (char**)realloc(*wynik, (*licznik + 1) * sizeof(char *));
        if (!tmp) return 0;
        *wynik = tmp;
        (*wynik)[*licznik] = (char*)malloc(dlugosc_slowa + 2);
        if (!(*wynik)[*licznik]) return 0;
        for (size_t j = 0; j < dlugosc_slowa; j++) {
            (*wynik)[*licznik][j] = zmniejszono[j] ? toupper((unsigned char)slownik[i][j]) : slownik[i][j];
        }
        if (znak_interpunkcyjny != '\0') {
            (*wynik)[*licznik][dlugosc_slowa] = znak_interpunkcyjny;
            (*wynik)[*licznik][dlugosc_slowa + 1] = '\0';
        } else {
            (*wynik)[*licznik][dlugosc_slowa] = '\0';
        }
        (*licznik)++;
        if (!najlepszy_podzial(tekst_po_slowniku, slownik, rozmiar_slownika, wynik, licznik, najlepszy, najlepsza_liczba)) {
            return 0;
        }
        free((*wynik)[--(*licznik)]);
    }
    return 1;
}
char **podziel_na_zdania(const char *tekst, int *liczba_zdan) {
    if (!tekst || !liczba_zdan) return NULL;
    const char *znaki_konca = ".!?";
    char **zdania = NULL;
    int licznik = 0;
    const char *start = tekst;
    while (*start) {
        const char *koniec = start;
        while (*koniec && !strchr(znaki_konca, *koniec)) {
            koniec++;
        }
        if (!*koniec) {
            koniec = tekst + strlen(tekst);
        }
        size_t dlugosc = koniec - start + (*koniec ? 1 : 0);
        char *zdanie = (char*)malloc(dlugosc + 1);
        if (!zdanie) {
            for (int i = 0; i < licznik; i++) {
                free(zdania[i]);
            }
            free(zdania);
            return NULL;
        }
        strncpy(zdanie, start, dlugosc);
        zdanie[dlugosc] = '\0';
        char **tmp = (char**)realloc(zdania, (licznik + 1) * sizeof(char *));
        if (!tmp) {
            free(zdanie);
            for (int i = 0; i < licznik; i++) {
                free(zdania[i]);
            }
            free(zdania);
            return NULL;
        }
        zdania = tmp;
        zdania[licznik++] = zdanie;
        if (*koniec) {
            start = koniec + 1;
        } else {
            break;
        }
        while (*start == ' ') start++;
    }
    *liczba_zdan = licznik;
    return zdania;
}

void polacz_wyniki_do_ciagu(char **zdania, int liczba_zdan, char **wynik, char **slownik, int rozmiar_slownika) {
      size_t calkowita_dlugosc = 0;
      for (int i = 0; i < liczba_zdan; i++) {
          char **wynik_slow = NULL;
          char **najlepszy = NULL;
          int licznik = 0;
          int najlepsza_liczba = -1;
          najlepszy_podzial(zdania[i], slownik, rozmiar_slownika, &wynik_slow, &licznik, &najlepszy, &najlepsza_liczba);
          for (int j = 0; j < najlepsza_liczba; j++) {
              calkowita_dlugosc += strlen(najlepszy[j]) + 1;
          }
          zwolnij(najlepszy, najlepsza_liczba);
      }
      *wynik =(char*)malloc(calkowita_dlugosc + 1);
      if (!*wynik) {
          printf("Blad alokacji pamieci dla wyniku.");
          return;
      }
      (*wynik)[0] = '\0';
      for (int i = 0; i < liczba_zdan; i++) {
          char **wynik_slow = NULL;
          char **najlepszy = NULL;
          int licznik = 0;
          int najlepsza_liczba = -1;
          najlepszy_podzial(zdania[i], slownik, rozmiar_slownika, &wynik_slow, &licznik, &najlepszy, &najlepsza_liczba);
          for (int j = 0; j < najlepsza_liczba; j++) {
              strcat(*wynik, najlepszy[j]);
              if (i != liczba_zdan - 1 || j != najlepsza_liczba - 1) {
                  strcat(*wynik, " ");
              }
          }
          zwolnij(najlepszy, najlepsza_liczba);
      }
  }

void sprawdz_gramatyke(const char *tekst) {
    bool oczekuj_duzej_litery = true;
    int indeks = 0;
    bool poprawny = true;
    while (tekst[indeks] != '\0') {
        char znak = tekst[indeks];
        // Sprawdzanie dużej litery na początku zdania
        if (oczekuj_duzej_litery && !isspace(znak)) {
            if (isalpha(znak) && isupper(znak)) {
                oczekuj_duzej_litery = false;
            } else {
                printf("Zdanie zaczyna się od malej litery (znajduje sie na pozycji: %d)\n", indeks+1);
                poprawny = false;
                oczekuj_duzej_litery = false;
            }
        }
        // Sprawdzanie spacji po znakach interpunkcyjnych
        if (( znak == ';' || znak == ':' || znak == '.' || znak == ',' || znak == '!' || znak == '?') && tekst[indeks + 1] != '\0') {
            if (!isspace(tekst[indeks + 1]) && tekst[indeks + 1] != '"') {
                printf("Brak spacji po znaku interpunkcyjnym (znajduje sie na pozycji: %d)\n", indeks+1);
                poprawny = false;
            }
        }
        // Sprawdzanie liczby spacji między wyrazami
        if (isspace(znak) && isspace(tekst[indeks + 1])) {
            printf("Po slowie zbyt wiele spacji (specje zaczynaja sie na pozycji %d)\n", indeks+1);
            poprawny = false;
        }
        if (znak == '.' || znak == '!' || znak == '?') {
            oczekuj_duzej_litery = true;
        }
        indeks++;
    }
    if (poprawny) {
        printf("Tekst jest gramatycznie poprawny.\n");
    }
}
