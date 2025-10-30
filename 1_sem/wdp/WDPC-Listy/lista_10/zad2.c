#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *to_string(long long num)
{
    char *str = (char *)malloc(sizeof(char) * 20);
    for (int i = 0; i < 20; i++)
    {
        str[i] = '\0';
    }
    sprintf(str, "%lld", num);
    return str;
}
int sens_robic_dalej_2(const char *str, int odp4, int odp3, int odp7, int odp_sum, const char *str_upper_bound)
{
    int len = strlen(str);
    int max_len = strlen(str_upper_bound);
    if (odp4 != 22)
    {
        if (len > 4 || odp4 > 22 || odp4 + 9 * (4 - len) < 22)
        {
            return 0; //-1
        }
        if (len < 4)
        {
            return 1;
        }
    }
    if (odp7 == 1)
    {
        if (len % 2 == 0)
        {
            odp_sum += 7;
        }
        else
            odp_sum -= 7;
    }
    if (odp3 == 2)
    {
        if (len % 2 == 0)
        {
            odp_sum += 3;
        }
        else
            odp_sum -= 3;
    }
    odp3 = 3 - odp3;
    odp7 = 2 - odp7;
    int wyrowanie = 0;
    if (odp_sum % 9 != 0 && odp_sum > 9)
        wyrowanie = 1;
    if ((odp_sum / 9 + wyrowanie) * 2 + len + odp3 + odp7 > max_len)
    {
        /* printf("DEBUG: sens_robic_dalej -> liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d NIE_dl\n",
               str, odp4, odp3, odp7, odp_sum);
        printf("WYrowanie %d cos: %d ", wyrowanie, (int)((odp_sum / 9 + wyrowanie) * 2 + len + odp3 + odp7));
         */
        return 0;
    }
    return 1; // Jeśli przeszliśmy wszystkie warunki, warto kontynuować generowanie
}
int sens_robic_dalej(char *str, int odp4, int odp3, int odp7, int odp_sum, char *str_upper_bound)
{
    int max_len = strlen(str_upper_bound);
    int len = strlen(str);

    /*  printf("DEBUG: sens_robic_dalej -> liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d\n",
            str, odp4, odp3, odp7, odp_sum);
  */
    if (odp4 != 22)
    {
        if (odp4 + 9 * (4 - len) < 22 || len > 4 || odp4 > 22)
        {
            /* printf("DEBUG: sens_robic_dalej -> liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d: NIE_w4\n",
                   str, odp4, odp3, odp7, odp_sum);
             */
            return 0;
        }
        if (len < 4)
        {
            /*  printf("DEBUG: sens_robic_dalej -> liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d TAK_w4\n",
                    str, odp4, odp3, odp7, odp_sum);
             */
            return 1;
        }
    }

    int val_3 = 0, val_7 = 0;
    if (odp3 == 0)
        val_3 = 1;
    if (odp7 == 0)
        val_7 = 1;
    int suma = odp_sum;
    int wyr3_7 = 0;
    if (str[strlen(str) - 1] == '3' || str[strlen(str) - 1] == '7')
        wyr3_7 = 1;
    if (odp_sum < 0 || odp_sum - val_3 * 3 <= 0)
    {
        suma = 0;
    }
    else
        suma = ceil((double)((odp_sum - val_3 * 3) / 9));
    if ((val_3 * 3 + val_7 * 2) - wyr3_7 + suma + len > max_len)
    {
        /* printf("DEBUG: sens_robic_dalej -> liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d NIE_dl\n",
               str, odp4, odp3, odp7, odp_sum);
         */
        return 0;
    }
    /* printf("DEBUG: sens_robic_dalej -> liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d TAK\n",
           str, odp4, odp3, odp7, odp_sum);
     */
    return 1;
}

int solve(char *str, int odp4, int odp3, int odp7, int odp_sum, char *str_lower_bound, char *str_upper_bound, int wieksza)
{
    int ans = 0;
    int pos = strlen(str);
    /* printf("DEBUG: solve -> liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d, pos: %d\n",
           str, odp4, odp3, odp7, odp_sum, pos);
 */
    for (char c = '0'; c <= '9'; c++)
    {
        str[pos] = c;
        str[pos + 1] = '\0';
        if (strlen(str) > strlen(str_upper_bound))
            return 0;
        if (str[pos] < str_lower_bound[pos] && wieksza == 0)
            continue;
        else
            wieksza = 1;
        int new_odp4 = odp4;
        int new_odp3 = odp3;
        int new_odp7 = odp7;
        int new_odp_sum = odp_sum;

        if (pos < 4)
        {
            new_odp4 += c - '0';
        }

        if (new_odp3 < 3 && c == '3')
        {
            new_odp3++;
        }
        else if (new_odp3 < 3)
            new_odp3 = 0;

        if (new_odp7 < 2 && c == '7')
        {
            new_odp7++;
        }
        else if (new_odp7 < 2)
            new_odp7 = 0;

        if (pos % 2 == 0)
        {
            new_odp_sum += c - '0';
        }
        else
        {
            new_odp_sum -= c - '0';
        }

        /*  printf("DEBUG: Iteracja -> dodano: %c, nowa liczba: %s, odp4: %d, odp3: %d, odp7: %d, odp_sum: %d\n",
                c, str, new_odp4, new_odp3, new_odp7, new_odp_sum);
  */
        if (new_odp3 == 3 && new_odp7 == 2 && new_odp_sum <= 0 && new_odp4 == 22)
        {
            // printf("DEBUG: ZNALEZIONO LICZBĘ: %s\n", str);
            if (atoll(str) <= atoll(str_upper_bound) && atoll(str) >= atoll(str_lower_bound))
            {
                ans++;
                // printf("DEBUG: ZNALEZIONO LICZBĘ: %s\n", str);
            }
            ans += solve(str, new_odp4, new_odp3, new_odp7, new_odp_sum, str_lower_bound, str_upper_bound, wieksza);
            continue;
        }
        int sens = sens_robic_dalej(str, new_odp4, new_odp3, new_odp7, new_odp_sum, str_upper_bound);
        if (sens)
        {
            ans += solve(str, new_odp4, new_odp3, new_odp7, new_odp_sum, str_lower_bound, str_upper_bound, wieksza);
        }
    }

    return ans;
}

int main()
{
    long long lower_bound, upper_bound;
    scanf("%lld %lld", &lower_bound, &upper_bound);

    // printf("DEBUG: Zakres wejściowy -> %lld do %lld\n", lower_bound, upper_bound);

    if (upper_bound < 1777073339 || lower_bound > upper_bound)
    {
        printf("0\n");
        return 0;
    }

    char *str_upper_bound = to_string(upper_bound);
    char *str_lower_bound = to_string(lower_bound);
    char str[20];
    for (int i = 0; i < 20; i++)
    {
        str[i] = '\0';
    }

    int wynik = solve(str, 0, 0, 0, 19, str_lower_bound, str_upper_bound, 0);

    // printf("DEBUG: Wynik końcowy -> %d\n", wynik);
    printf("%d\n", wynik);

    free(str_upper_bound);
    free(str_lower_bound);

    return 0;
}
