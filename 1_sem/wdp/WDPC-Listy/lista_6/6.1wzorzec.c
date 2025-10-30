#include <stdio.h>
#include <math.h>
#include <ctype.h>
#define ll long long
int main()
{
    ll wzorzec = 0, tekst = 0;
    char c;
    int licznik = 0;
    int ind = 0;
    while ((c = getchar()) != 0 && c != '\n') // wczytanie wzorca
    {
        wzorzec = (wzorzec * 2) + c - '0';
        licznik++;
    }
    int maska = (1 << licznik) - 1;
    // maska ktora ma dl=licznik , 0 na pcoztaku i 1 wszedzie indziej np 0111
    while ((c = getchar()) != 0 && c != '\n')
    {
        if (licznik) // zrownaj tekst z wzorcem
        {
            tekst = (tekst * 2) + c - '0';
            licznik--;
        }
        else
        {
            if (wzorzec == tekst)
                printf("%d\n", ind);
            tekst = ((tekst << 1) + c - '0') & maska;
            // przesun o 1 w lewo -> dodaj znak -> usun skrajnie lewy znak
            ind++;
        }
    }
}