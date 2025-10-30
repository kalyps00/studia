#include <stdio.h>
#include <string.h>
#include <ctype.h>

int if_can_create(int cnt_a[66], int cnt_b[66])
{
    for (int i = 0; i < 66; i++)
    {
        if (cnt_a[i] < cnt_b[i])
            return 0;
    }
    return 1;
}
int main()
{
    int tests = 0;

    int err = scanf("%d", &tests);

    err = err;
    if (tests <= 0)
    {
        printf("0");
        return 0;
    }

    unsigned long long result = 0;
    int czworka = 0;

    while (tests--)
    {

        int words;

        int err1 = scanf("%d", &words);
        err1 = err1;

        int char_counter[words][66];

        for (int i = 0; i < words; i++)
        {
            for (int j = 0; j < 66; j++)
            {
                char_counter[i][j] = 0;
            }
        }

        for (int i = 0; i < words; i++)
        {
            char word[256];

            int err2 = scanf("%s", word);
            err2 = err2;

            for (int j = 0; word[j] != '\0'; j++)
            {
                int c = (int)word[j];
                char_counter[i][c - 63]++;
            }
        }

        unsigned long long ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0;

        for (int i = 0; i < words; i++)
        {
            unsigned long long q1 = 1, q2 = 1, q3 = 1, q4 = 1;

            for (int j = 0; j < words; j++)
            {
                if (i != j)
                {
                    if (!if_can_create(char_counter[i], char_counter[j]))
                    {
                        q1 = 0;
                    }
                    else
                    {
                        q4 = 0;
                    }
                    if (!if_can_create(char_counter[j], char_counter[i]))
                    {
                        q2 = 0;
                    }
                    else
                    {
                        q3 = 0;
                    }
                    if (q1 == 0 && q2 == 0 && q3 == 0 && q4 == 0)
                    {
                        break;
                    }
                }
            }

            ans1 |= q1;
            ans2 |= (q2 << 1);
            ans3 |= (q3 << 2);
            ans4 |= (q4 << 3);
        }
        result += ((ans1 + ans2 + ans3 + ans4) << (czworka * 4));

        czworka++;
    }
    printf("%llu", result);
}