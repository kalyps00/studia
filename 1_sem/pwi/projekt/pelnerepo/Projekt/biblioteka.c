#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteka.h"

#define MAX_WORD_LENGHT 1000
#define MAX_TEXT_SIZE 1000000

void statystyki(const char *text, TextStats *stats) {
    for (int i = 0; i < 52; i++) stats->tablica_liter[i] = 0;
    int i = 0, dlugosc_slowa = 0, dlugosc_zdania = 0;
    stats->liczba_wyrazow = stats->liczba_akapitow = stats->liczba_cyfr = stats->liczba_znakow = stats->liczba_zdan = stats->liczba_liter = 0;
    stats->srednia_dlugosc_slowa = stats->srednia_dlugosc_zdania = stats->liczba_znakow_specjalnych = stats->zlozonosc_leksykalna = 0;
    stats->max_dlugosc_slowa = 0;
    stats->min_dlugosc_slowa = MAX_WORD_LENGHT;
    
    while (text[i] != '\0') {
        char znak = text[i];
        stats->liczba_znakow++;

        if (isalpha(znak)) {
            stats->liczba_liter++;
            dlugosc_slowa++;
            if ('a' <= znak && znak <= 'z') stats->tablica_liter[(int)znak-97]++;
            if ('A' <= znak && znak <= 'Z') stats->tablica_liter[(int)znak-65+26]++;
        }
        else if (isdigit(znak)) stats->liczba_cyfr++;
        else if (ispunct(znak)) stats->liczba_znakow_specjalnych++;

        if (isspace(znak)) {
            if (znak == '\n' && (i == 0 || text[i-1] == '\n')) stats->liczba_akapitow++;
            if (dlugosc_slowa > 0 && znak == ' ') {
                stats->liczba_wyrazow++;
                if (dlugosc_slowa > stats->max_dlugosc_slowa) stats->max_dlugosc_slowa = dlugosc_slowa;
                if (dlugosc_slowa < stats->min_dlugosc_slowa) stats->min_dlugosc_slowa = dlugosc_slowa;
                dlugosc_zdania = dlugosc_zdania + dlugosc_slowa + 1;
                dlugosc_slowa = 0;
            }
        }

        if (znak == '.' || znak == '!' || znak == '?') {
            stats->liczba_zdan++;
            stats->srednia_dlugosc_zdania += dlugosc_zdania;
            dlugosc_zdania = 0;
        }

        i++;
    }
    
    if (dlugosc_slowa > 0) {
        stats->liczba_wyrazow++;
        if (dlugosc_slowa > stats->max_dlugosc_slowa) stats->max_dlugosc_slowa = dlugosc_slowa;
        if (dlugosc_slowa < stats->min_dlugosc_slowa) stats->min_dlugosc_slowa = dlugosc_slowa;
        dlugosc_zdania = dlugosc_zdania + dlugosc_slowa + 1;
    }
        

    stats->srednia_dlugosc_slowa = (float) stats->liczba_znakow / stats->liczba_wyrazow;
    stats->srednia_dlugosc_zdania = (float) stats->srednia_dlugosc_zdania / stats->liczba_zdan;
    stats->zlozonosc_leksykalna = (float) stats->liczba_wyrazow / stats->liczba_zdan;
}

void wyszukiwanie_wzorca(const char *text, const char *pattern) {
    const char *text_copy = text;
    char buffer[MAX_TEXT_SIZE];       

    if ((pattern[0] == '.' && strlen(pattern) == 1) || (pattern[0] == '!' && strlen(pattern) == 1) || (pattern[0] == '?' && strlen(pattern) == 1) || (pattern[0] == '-' && strlen(pattern) == 1)) wyszukiwanie_znaku_specjalnego(text, pattern);

    while (strstr(text_copy, pattern) != NULL) {
        text_copy = strstr(text_copy, pattern);

        // zdanie przed patternem
        int i = 1;
        while ((text_copy - i) >= text && text_copy[-i] != '\t' && text_copy[-i] != '\n' && text_copy[-i] != '-' && text_copy[-i] != '.'  && text_copy[-i] != '!'  && text_copy[-i] != '?') {
            buffer[i-1] = text_copy[-i];
            i++;
        }
        int licznik = 1;
        while (buffer[strlen(buffer)-licznik] == ' ') licznik++;
        for (int j = strlen(buffer)-licznik; j >= 0; j--) printf("%c", buffer[j]);
        memset(buffer, 0, sizeof(buffer));

        //pattern
        printf("\033[0;31m");
        for (int j = 0; j < strlen(pattern); j++) printf("%c", text_copy[j]);
        printf("\033[0m");

        // reszta zdania
        int k = strlen(pattern);
        while (text_copy[k] != '\n' && text_copy[k] != '.'  && text_copy[k] != '!'  && text_copy[k] != '?' && text_copy[k] != '\0') {
            printf("%c", text_copy[k]);
            k++;
        }
        printf("%c", text_copy[k]);

        text_copy += strlen(pattern);
        putchar('\n');
    }
}

void wyszukiwanie_znaku_specjalnego(const char *text, const char *znak) {
    const char *text_copy = text;
    char buffer[MAX_TEXT_SIZE];

    if (znak[0] == '.' || znak[0] == '!' || znak[0] == '?') {
        while (strstr(text_copy, znak) != NULL) {
        text_copy = strstr(text_copy, znak);

        int i = 1;
        while ((text_copy - i) > text && text_copy[-i] != '\t' && text_copy[-i] != '\n' && text_copy[-i] != '.'  && text_copy[-i] != '!'  && text_copy[-i] != '?' && text_copy[-i] != '-') {
            buffer[i-1] = text_copy[-i];
            i++;
        }
        //for (int j = i-3; j >= 0; j--) printf("%c", buffer[j]);
        for (int j = strlen(buffer)-1; j >= 0; j--) printf("%c", buffer[j]);

        printf("\033[0;31m%s\033[0m\n", znak);
        text_copy++;
        }
    }

    if (znak[0] == '-') {
        while (strstr(text_copy, znak) != NULL) {
            text_copy = strstr(text_copy, znak);

            if (text_copy[-1] == '\n' || text_copy[-1] == '\t') {
                printf("\033[0;31m%s\033[0m\n", znak);
                int k = 1;
                while (text_copy[k] != '\n' && text_copy[k] != '.'  && text_copy[k] != '!'  && text_copy[k] != '?') {
                    printf("%c", text_copy[k]);
                    k++;    
                }
                printf("%c", text_copy[k]);
            }
            
            else {
                // zdanie przed patternem
                const char *pattern = znak; 
                int i = 1;
                while ((text_copy - i) > text && text_copy[-i] != '\t' && text_copy[-i] != '\n' && text_copy[-i] != '.'  && text_copy[-i] != '!'  && text_copy[-i] != '?') {
                    buffer[i-1] = text_copy[-i];
                    i++;
                }
                for (int j = i-3; j >= 0; j--) printf("%c", buffer[j]);

                //pattern
                printf("\033[0;31m");
                for (int j = 0; j < strlen(pattern); j++) printf("%c", text_copy[j]);
                printf("\033[0m");

                // reszta zdania
                int k = strlen(pattern);
                while (text_copy[k] != '\n' && text_copy[k] != '.'  && text_copy[k] != '!'  && text_copy[k] != '?' && text_copy[k] != '\0') {
                    printf("%c", text_copy[k]);
                    k++;
                }
                printf("%c", text_copy[k]);
            }

            text_copy++;
            putchar('\n');
        }
    }
}

void ignorowanie_wielkosci_liter(const char *text, const char *pattern) {

    if (text == NULL || pattern == NULL) {
        perror("Blad alokacji pamieci");
        return;
    }

    if (strlen(pattern) > strlen(text)) return;


    for (int i = 0; i <= strlen(text) - strlen(pattern); i++) {
        if (tolower(text[i]) != tolower(pattern[0])) continue;

        for (int j = i; j < i + strlen(pattern); j++) {
            if (tolower(text[j]) != tolower(pattern[j-i])) {
                i = j;
                break;
            }
            if (j == i + strlen(pattern) - 1 && tolower(text[j]) == tolower(pattern[j-i])) {
                wypisz_tekst_wersja2(text, i, strlen(pattern));
                i = j;
            }
        }
    } 
}

void wypisz_tekst_wersja1(const char* text, int x, int pattern_len) {
    int end = x-1;
    char buffer[MAX_TEXT_SIZE];
    while (end >= 0 && text[end] != '.' && text[end] != '!' && text[end] != '?' && text[end] != '\n' && text[end] != '\t') {
        buffer[x-1-end] = text[end];
        end--;
    }
    int licznik = 1;
    while (buffer[strlen(buffer)-licznik] == ' ') licznik++;
    if (buffer[strlen(buffer)-licznik] == '-') licznik += 2;
    if (buffer[strlen(buffer)-licznik] == '"') licznik++;
    for (int i = strlen(buffer)-licznik; i >= 0; i--) printf("%c", buffer[i]);
    memset(buffer, 0, sizeof(buffer));

    printf("\033[0;31m");
    for (int j = x; j < x + pattern_len; j++) printf("%c", text[j]);
    printf("\033[0m");

    int i;
    for (i = x + pattern_len; text[i] != '.' && text[i] != '\n' && text[i] != '\t' && text[i] != '!' && text[i] != '?' && text[i] != EOF; i++) printf("%c", text[i]);
    if (text[i] != '\n' && text[i] != '\t' && text[i] != EOF) printf("%c", text[i]);

    putchar('\n');
}

void wypisz_tekst_wersja2(const char *text, int x, int pattern_len) {
    char buffer[MAX_TEXT_SIZE];
    memset(buffer, 0, sizeof(buffer));
    int end = x - 1;
    int idx = 0;
    int cou = 0; 

    while (end >= 0 && text[end] != '\t' && cou <= 200) {
        if (idx < MAX_TEXT_SIZE - 1) {
            buffer[idx++] = text[end];
        }
        end--;
        cou++;
    }

    if (end > 0) printf("...");
    buffer[idx] = '\0';
    for (int i = idx - 1; i >= 0; i--) printf("%c", buffer[i]);
    printf("\033[0;31m");
    for (int j = x; j < x + pattern_len; j++) {
        if (text[j] == '\0' || text[j] == '\t') {
            break;
        }
        putchar(text[j]);
    }
    printf("\033[0m");

    int licznik = 0;
    int i;
    for (i = x + pattern_len; text[i] != '\0' && text[i] != '\t' && licznik < 200; i++, licznik++) {
        putchar(text[i]);
    }

    if (text[i] != '\0' && text[i] != '\t') {
        printf(" ...");
    }

    putchar('\n');
    putchar('\n');
}


void wypisanie_statystyk_liter(TextStats stats) {
    // a / A: 63 + 32 = 95 czyli 11% wszystkich liter
    printf("Instrukcja: \n");
    printf("-> 0 - wyjscie\n");
    printf("-> 1 - dokladne statystyki dla kazdej litery\n");
    printf("-> 2 - ilosciowe statystyki dla tekstu\n");
    printf("-> 3 - wyroznienia w tekscie\n");
    printf("-> 4 - instrukcja\n");

    while (1) {
        int liczba;
        scanf("%i", &liczba);
        if (liczba == 0) break;

        if (liczba == 1) {
            for (int i = 0; i < 26; i++) {
                printf("%c / %c: %i + %i = %i czyli %lf%% wszystkich znakow\n", (char) i+97, (char) i+65, stats.tablica_liter[i],
                stats.tablica_liter[i+26], stats.tablica_liter[i] + stats.tablica_liter[i+26], 
                ((double)stats.tablica_liter[i]+(double)stats.tablica_liter[i+26])/(double)stats.liczba_znakow*100);
            }
        }

        if (liczba == 2) {
            printf("Liczba wszystkich znakow: %i\n", stats.liczba_znakow);
            printf("Liczba liter: %i\n", stats.liczba_liter);
            printf("Liczba wyrazow: %i\n", stats.liczba_wyrazow);
            printf("Liczba cyfr: %i\n", stats.liczba_cyfr);
            printf("Liczba znakow specjalnych: %i\n", stats.liczba_znakow_specjalnych);
            printf("Liczba zdan: %i\n", stats.liczba_zdan);
            printf("Liczba akapitow: %i\n", stats.liczba_akapitow);
        }

        if (liczba == 3) {
            printf("Minimalna dlugosc slowa: %i\n", stats.min_dlugosc_slowa);
            printf("Maksymalna dlugosc slowa: %i\n", stats.max_dlugosc_slowa);
            printf("Srednia dlugosc slowa: %f\n", stats.srednia_dlugosc_slowa);
            printf("Srednia dlugosc zdania: %f\n", stats.srednia_dlugosc_zdania);
            printf("Zlozonosc leksykalna: %f\n", stats.zlozonosc_leksykalna);
        }

        if (liczba == 4) {
            printf("Instrukcja: \n");
            printf("-> 0 - wyjscie\n");
            printf("-> 1 - dokladne statystyki dla kazdej litery\n");
            printf("-> 2 - ilosciowe statystyki dla tekstu\n");
            printf("-> 3 - wyroznienia w tekscie\n");
            printf("-> 4 - instrukcja\n");
        }
    }
}

int zliczanie_wzorca(const char *text, const char *pattern) {
    const char *text_copy = text;
    int result = 0;

    while (strstr(text_copy, pattern) != NULL) {
        result++;
        text_copy = strstr(text_copy, pattern);
        text_copy += strlen(pattern);
    }

    return result;
}

void podmiana_wzorca(const char *text, const char* pattern, const char* replacement, char* result) {
    const char *text_copy = text;         // aktualna pozycja w tekscie
    char buffer[MAX_TEXT_SIZE];     // wynikowy tekst
    char *buffer2 = buffer;         // wskaznik

    while (strstr(text_copy, pattern) != NULL) {        // strstr to jakas funkcja ktora zwraca wskaznik na pierwsze wystapienie pattern w text_copy
        text_copy = strstr(text_copy, pattern);         
        strncpy(buffer2, text, text_copy - text);       // w buffer2 trzymamy wszystko oprocz patternu
        buffer2 += text_copy - text;                    // przesuwamy buffer do konca
        strcpy(buffer2, replacement);                   // dodajemy do buffer2 replacement
        buffer2 += strlen(replacement);                 // przesuwamy buffer do konca
        text_copy += strlen(pattern);                   
        text = text_copy;
    }

    strcpy(buffer2, text);
    strcpy(result, buffer);
}