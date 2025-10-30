
#include "beneficjent.h"

int main()
{
    struct Osoba *jakub = nowa_osoba("Jakub", 19);
    if (jakub == NULL)
    {
        printf("Nie udało się stworzyć obiektu Jakub.\n");
        return 1;
    }

    ustaw_statystyki(jakub, 1, INT_MAX);

    if (czy_dostanie_prezent(jakub))
    {
        printf("Jakub dostanie prezent!\n");
    }
    else
    {
        printf("Jakub nie dostanie prezentu.\n");
    }

    zmien_imie(jakub, "Kuba");
    zmien_wiek(jakub, 20);

    if (czy_dostanie_prezent(jakub))
    {
        printf("Kuba dostanie prezent!\n");
    }
    else
    {
        printf("Kuba nie dostanie prezentu.\n");
    }

    dodaj_zasluge(jakub);
    dodaj_szelmostwo(jakub);

    wypisz_info(jakub);

    struct Osoba *ania = nowa_osoba("Ania", 3);
    if (ania == NULL)
    {
        printf("Nie udało się stworzyć obiektu Ania.\n");
        usun_osobe(jakub);
        return 1;
    }

    ustaw_statystyki(ania, 1, 0);

    if (czy_dostanie_prezent(ania))
    {
        printf("Ania dostanie prezent!\n");
    }
    else
    {
        printf("Ania nie dostanie prezentu.\n");
    }

    wypisz_info(ania);

    int cmp_result = komparator(jakub, ania);
    if (cmp_result < 0)
    {
        printf("Jakub ma większą szansę na prezent niż Ania.\n");
    }
    else if (cmp_result > 0)
    {
        printf("Ania ma większą szansę na prezent niż Jakub.\n");
    }
    else
    {
        printf("Jakub i Ania mają równe szanse na prezent.\n");
    }

    usun_osobe(jakub);
    usun_osobe(ania);

    return 0;
}
