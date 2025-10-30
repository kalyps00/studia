#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "beneficjent.h"
struct Osoba *nowa_osoba(char *imie, uint8_t wiek)
{
    struct Osoba *nowa_os = (struct Osoba *)malloc(sizeof(struct Osoba)); // zarezerwuj pamiec na nowa os
    if (nowa_os == NULL)
    {
        free(nowa_os);
        return NULL;
    }
    nowa_os->imie = (char *)malloc(strlen(imie) + 1); // daj pamiec na to imie +1 przr '\0'
    if (nowa_os->imie == NULL)
    {
        free(nowa_os);
        return NULL;
    }
    strcpy(nowa_os->imie, imie); // dodaj to nwoe imie
    nowa_os->wiek = wiek;

    return nowa_os;
}
void usun_osobe(struct Osoba *osoba)
{
    if (osoba == NULL)
        return;
    free(osoba->imie);
    free(osoba);
}
void zmien_imie(struct Osoba *osoba, char *imie)
{
    if (osoba == NULL)
        return;
    char *nowe_imie = realloc(osoba->imie, strlen(imie) + 1);
    if (nowe_imie == NULL)
    {
        return;
    }
    osoba->imie = nowe_imie;
    strcpy(osoba->imie, imie);
}
void zmien_wiek(struct Osoba *osoba, uint8_t wiek)
{
    if (osoba == NULL)
        return;
    osoba->wiek = wiek;
}
void dodaj_zasluge(struct Osoba *osoba)
{
    if (osoba == NULL)
        return;
    osoba->zaslugi++;
}
void dodaj_szelmostwo(struct Osoba *osoba)
{
    if (osoba == NULL)
        return;
    osoba->szelmostwa++;
}
void ustaw_statystyki(struct Osoba *osoba, unsigned int zaslugi, unsigned int szelmostwa)
{
    if (osoba == NULL)
        return;
    osoba->zaslugi = zaslugi;
    osoba->szelmostwa = szelmostwa;
}
int czy_dostanie_prezent(struct Osoba *osoba) //  dodaj wiek
{
    if (osoba == NULL)
        return -1;
    if (osoba->zaslugi > osoba->szelmostwa || osoba->wiek < 4)
        return 1;
    else
        return 0;
}
void wypisz_info(struct Osoba *osoba)
{
    if (osoba == NULL)
        return;
    printf("Imie oosby: %s\n", osoba->imie);
    printf("Wiek oosby: %u\n", osoba->wiek);
    printf("Zasługi oosby: %u\n", osoba->zaslugi);
    printf("Szelmostwa oosby: %u\n", osoba->szelmostwa);
}
int komparator(const struct Osoba *os1, const struct Osoba *os2)
{
    if (os1 == NULL && os2 == NULL)
        return -2;
    else if (os1 == NULL)
        return -1;
    else if (os2 == NULL)
        return 1;
    unsigned int os1wynik = os1->zaslugi - os1->szelmostwa;
    unsigned int os2wynik = os2->zaslugi - os2->szelmostwa;
    if (os1wynik > os2wynik) // kryt 1
        return 1;
    else if (os2wynik > os1wynik)
        return -1;
    else // kryt 2
    {
        if (os1->wiek < os2->wiek)
            return 1;
        else if (os1->wiek > os2->wiek)
            return -1;
        else
            return 0;
    }
}