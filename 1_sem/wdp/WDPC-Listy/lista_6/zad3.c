#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDLENGTH 255

// zaliczone test : 1, 2 ,4 ,7

// Sprawdza, czy histogram `hist1` może ułożyć histogram `hist2`
int can_be_formed(int hist1[66], int hist2[66])
{
    for (int i = 0; i < 66; i++)
    {
        if (hist1[i] < hist2[i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int tests;
    int check = scanf("%d", &tests);
    check = check; // Usuwanie ostrzeżeń
    if (tests <= 0)
    {
        printf("0");
        return 0;
    }
    unsigned long long fullanswer = 0;
    int czworka = 0;

    for (int test = 0; test < tests; test++, czworka++)
    { // Pętla testów
        int wcount;
        int nic = scanf("%d", &wcount);
        nic = nic; // Usuwanie ostrzeżeń

        // Tworzenie histogramów
        int word_histogram[wcount][66];
        for (int i = 0; i < wcount; i++)
        {
            for (int j = 0; j < 66; j++)
            {
                word_histogram[i][j] = 0;
            }
        }

        // Odczyt słów i wypełnienie histogramów
        for (int i = 0; i < wcount; i++)
        {
            char word[MAX_WORDLENGTH + 1];
            int nic = scanf("%s", word);
            nic = nic; // Usuwanie ostrzeżeń

            for (int j = 0; word[j] != '\0'; j++)
            {
                int c = (int)word[j];
                word_histogram[i][c - '?']++;
            }
        }

        int ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0;
        for (int i = 0; i < wcount; i++)
        {
            int pyt1 = 1; // Czy da się ułożyć każde inne słowo z tego słowa
            int pyt2 = 1; // Czy to słowo da się ułożyć z każdego innego słowa
            int pyt3 = 1; // Czy nie da się ułożyć tego słowa z żadnego innego
            int pyt4 = 1; // Czy z tego słowa nie da się ułożyć żadnego innego

            for (int j = 0; j < wcount; j++)
            {
                if (i != j)
                {
                    if (!can_be_formed(word_histogram[i], word_histogram[j]))
                    {
                        pyt1 = 0;
                    }
                    else
                        pyt4 = 0;
                    if (!can_be_formed(word_histogram[j], word_histogram[i]))
                    {
                        pyt2 = 0;
                    }
                    else
                        pyt3 = 0;
                    if (pyt1 == 0 && pyt2 == 0 && pyt3 == 0 && pyt4 == 0)
                        break;
                }
            }
            // foramtowanie odpowiedzi
            ans1 |= pyt1;
            ans2 |= (pyt2 << 1);
            ans3 |= (pyt3 << 2);
            ans4 |= (pyt4 << 3);
        }
        // wynik finalny przesuwany o odpowiednia ilosc bitow
        fullanswer += ((ans1 + ans2 + ans3 + ans4) << (czworka * 4));
    }

    printf("%llu", fullanswer);
    return 0;
}
