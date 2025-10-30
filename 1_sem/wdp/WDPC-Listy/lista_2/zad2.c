#include <stdio.h>
#include <limits.h>
int prime_factorization(int num)
{
    int count = 0;
    for (int i = 2; i * i < num; i++)
    {
        while (num % i == 0)
            count++;
        num = num / i;
    }
    return count;
}
int main()
{
    int n;
    int check = scanf("%d", &n);
    if (!check || n < 3) // check input
    {
        return 0;
    }
    int first = INT_MAX, second = INT_MAX, third = INT_MAX;
    for (int i = 0; i < n; i++) // check if num is greather than any of previu minimum values
    {
        int num;
        scanf("%d", &num);
        if (num < first)
        {
            third = second;
            second = first;
            first = num;
        }
        else if (num < second)
        {
            third = second;
            second = num;
        }
        else if (num < third)
        {
            third = num;
        }
    }
    printf("%d %d %d\n", first, second, third);
    int factor_first = prime_factorization(first),
        factor_second = prime_factorization(second), // factorize all three numbers
        factor_third = prime_factorization(third);

    if (factor_first > factor_second) // print one with most primes
    {
        if (factor_first > factor_third)
        {
            printf("%d", first);
        }
        else
        {
            printf("%d", third);
        }
    }
    else if (factor_second > factor_third)
    {
        printf("%d", second);
    }
    else
    {
        printf("%d", third);
    }
}