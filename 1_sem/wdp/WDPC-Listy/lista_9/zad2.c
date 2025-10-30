#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elemListy
{
    int wiek;
    char *imie;
    struct elemListy *next;
};
typedef struct elemListy Lista;

struct queue
{
    Lista *poczatek;
    Lista *koniec;
};
typedef struct queue Queue;

void push(Queue *kolejka, char *imie, int wiek)
{
    Lista *nowy = (Lista *)malloc(sizeof(Lista));
    nowy->imie = (char *)malloc(sizeof(char) * (strlen(imie) + 1));
    strcpy(nowy->imie, imie);
    nowy->wiek = wiek;
    nowy->next = NULL;
    if (kolejka->poczatek == NULL)
    {
        kolejka->poczatek = nowy;
        kolejka->koniec = nowy;
    }
    else
    {
        kolejka->koniec->next = nowy;
        kolejka->koniec = nowy;
    }
}

void pop(Queue *kolejka)
{
    if (kolejka->poczatek == NULL)
    {
        return;
    }
    Lista *temp = kolejka->poczatek;
    kolejka->poczatek = kolejka->poczatek->next;
    free(temp->imie);
    free(temp);
}

void insert(Queue *kolejka, char *imie2, char *imie, int wiek)
{
    Lista *nowy = (Lista *)malloc(sizeof(Lista));
    nowy->imie = (char *)malloc(sizeof(char) * (strlen(imie) + 1));
    strcpy(nowy->imie, imie);
    nowy->wiek = wiek;
    nowy->next = NULL;
    Lista *prev = NULL;
    Lista *temp = kolejka->poczatek;
    while (temp != NULL)
    {
        if (strcmp(temp->imie, imie2) == 0)
        {
            if (temp == kolejka->poczatek)
            {
                kolejka->poczatek = nowy;
                nowy->next = temp;
                return;
            }
            prev->next = nowy;
            nowy->next = temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    free(nowy->imie);
    free(nowy);
}

void remove_q(Queue *kolejka, char *imie)
{
    Lista *temp = kolejka->poczatek;
    Lista *prev = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->imie, imie) == 0)
        {
            if (prev == NULL)
            {
                kolejka->poczatek = temp->next;
                if (temp == kolejka->koniec)
                {
                    kolejka->koniec = NULL;
                }
            }
            else
            {
                prev->next = temp->next;
                if (temp == kolejka->koniec)
                {
                    kolejka->koniec = prev;
                }
            }
            free(temp->imie);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

int main()
{
    Queue *kolejka = (Queue *)malloc(sizeof(Queue));
    kolejka->poczatek = NULL;
    kolejka->koniec = NULL;

    char c;
    char *imie = (char *)malloc(1000);
    char *imie2 = (char *)malloc(1000);
    int wiek;
    int n;
    int wolne_miejsca = 0;
    while ((c = getchar()) != 'Z' && c != EOF)
    {
        while (wolne_miejsca && kolejka->poczatek != NULL)
        {
            if (kolejka->poczatek->wiek >= 18)
            {
                wolne_miejsca--;
                printf("%s\n", kolejka->poczatek->imie);
            }
            pop(kolejka);
        }
        if (c == '\n' || c == ' ')
            continue;
        if (c == '+')
        {
            scanf("%s %d", imie, &wiek);
            push(kolejka, imie, wiek);
        }
        else if (c == '-')
        {
            scanf("%s", imie);
            remove_q(kolejka, imie);
        }
        else if (c == 'O')
        {
            scanf("%d", &n);
            wolne_miejsca += n;
        }
        else if (c == 'F')
        {
            scanf("%s %d %s", imie, &wiek, imie2);
            insert(kolejka, imie2, imie, wiek);
        }
    }
    free(imie);
    free(imie2);
    free(kolejka);
    return 0;
}
