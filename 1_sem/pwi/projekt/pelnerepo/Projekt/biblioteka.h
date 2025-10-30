typedef struct {
    int liczba_znakow;
    int liczba_liter;
    int liczba_wyrazow;
    int liczba_zdan;
    int liczba_akapitow;
    int liczba_znakow_specjalnych;
    int liczba_cyfr;
    int min_dlugosc_slowa;
    int max_dlugosc_slowa;
    float srednia_dlugosc_slowa;
    float srednia_dlugosc_zdania;
    float zlozonosc_leksykalna;
    int tablica_liter[52];
} TextStats;

void statystyki(const char *text, TextStats *stats);

void wyszukiwanie_wzorca(const char *text, const char *pattern);

void wyszukiwanie_znaku_specjalnego (const char* text, const char *znak);

void ignorowanie_wielkosci_liter(const char* text, const char *pattern);

void wypisz_tekst_wersja1(const char* text, int x, int pattern_len);

void wypisz_tekst_wersja2(const char* text, int x, int pattern_len);

void wypisanie_statystyk_liter(TextStats stats);

int zliczanie_wzorca(const char *text, const char *pattern);

void podmiana_wzorca(const char *text, const char *pattern, const char *rereplacement, char *result);

