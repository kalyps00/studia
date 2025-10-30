#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
char podciagi[CHAR_MAX][25];
void genpodciag(char *nowy, char *ciag, int index, int dlciagu, int *ilosc)
{
    if (strlen(nowy) != 0)
    {
        strcpy(podciagi[*ilosc], nowy);
        (*ilosc)++;
    }

    if (index == dlciagu)
    {
        return;
    }

    for (int i = index; i < dlciagu; i++)
    {
        int dlnowy = strlen(nowy);
        nowy[dlnowy] = ciag[i];
        nowy[dlnowy + 1] = '\0';

        genpodciag(nowy, ciag, i + 1, dlciagu, ilosc);

        nowy[dlnowy] = '\0';
    }
}

int main(int argc, char *argv[])
{
    // printf("%d", argc);
    if (argc >= 2) // czy 1 argument to napis sprawdzamy tak bo zawsze jak on jest
    {
        for (int i = 0; argv[1][i] != 0; i++)
        {
            if (argv[1][i] < 'a' || argv[1][i] > 'z')
            {
                printf("napis zawiera niedozwolne znaki");
                return 0;
            }
        }
    }
    if ((argc < 2) ||                                                             // za malo
        argc > 4 ||                                                               // za duzo
        (argc > 2 && strcmp(argv[2], "-i") != 0 && strcmp(argv[2], "-a") != 0) || // nie flagi
        (argc > 2 && strcmp(argv[2], "-i") == 0 && argc != 4) ||                  // flaga -i ale za nia brak
        (argc > 2 && strcmp(argv[2], "-a") == 0 && argc != 3))                    // flaga -a ale za nia cos
    {
        printf("złe argumenty\n");
        return 0;
    }
    if (argc > 3 && strcmp(argv[2], "-i") == 0) // sprawdzenie czy za -i jest liczba
    {
        for (int i = 0; argv[3][i] != 0; i++)
        {
            if (argv[3][i] < '0' || argv[3][i] > '9')
            {
                printf("złe argumenty\n");
                return 0;
            }
        }
    }

    char *ciag = argv[1];
    char nowy[25] = "";

    int ilosc = 0;
    int dlciagu = strlen(ciag);

    genpodciag(nowy, ciag, 0, dlciagu, &ilosc);
    if (argc > 2)
    {
        if (strcmp(argv[2], "-a") == 0)
        {
            for (int i = 0; i < ilosc; i++)
            {
                printf("%s\n", podciagi[i]);
            }
        }
        else if (strcmp(argv[2], "-i") == 0)
        {

            int indeks = atoi(argv[3]);
            printf("%s\n", podciagi[indeks - 1]);
        }
    }
    else
    {

        srand(time(NULL));
        int randomnum = rand() % (ilosc);
        printf("%s", podciagi[randomnum]);
    }

    return 0;
}
