#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 50
#define SUM_DIGITS 60

void sum_large_numbers(char result[SUM_DIGITS], char number[MAX_DIGITS])
{
    int carry = 0; // Przeniesienie
    for (int i = MAX_DIGITS - 1, j = SUM_DIGITS - 1; i >= 0; i--, j--)
    {
        int digit_sum = (result[j] - '0') + (number[i] - '0') + carry;
        result[j] = (digit_sum % 10) + '0';
        carry = digit_sum / 10;
    }
    // Obsługa przeniesienia poza główną część liczby
    for (int j = SUM_DIGITS - MAX_DIGITS - 1; j >= 0 && carry > 0; j--)
    {
        int digit_sum = (result[j] - '0') + carry;
        result[j] = (digit_sum % 10) + '0';
        carry = digit_sum / 10;
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    char numbers[n][MAX_DIGITS + 1]; // Tablica na 50-cyfrowe liczby
    char result[SUM_DIGITS + 1];     // Wynik (większa tablica dla przeniesień)

    // Inicjalizacja sumy zerami
    for (int i = 0; i < SUM_DIGITS; i++)
        result[i] = '0';
    result[SUM_DIGITS] = '\0';

    // Wczytywanie 50-cyfrowych liczb
    for (int i = 0; i < n; i++)
    {
        scanf("%s", numbers[i]);
    }

    // Sumowanie liczb
    for (int i = 0; i < n; i++)
    {
        sum_large_numbers(result, numbers[i]);
    }

    // Znalezienie pierwszych 9 cyfr wyniku
    int start = 0;
    while (result[start] == '0')
        start++; // Pomijanie wiodących zer

    for (int i = 0; i < 9 && result[start + i] != '\0'; i++)
    {
        putchar(result[start + i]);
    }
    putchar('\n');

    return 0;
}
