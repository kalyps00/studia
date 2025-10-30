#include <stdio.h>
#include <math.h>
int prime(int num)
{
    int sq = sqrt(num);
    for (int i = 2; i <= sq; i++)
    {
        int guard = 0;
        while (num % i == 0)
        {
            if (guard == 1)
                return 0;
            num = num / i;
            guard++;
        }
    }
    return 1;
}
int main()
{
    int n = 0;
    int check = scanf("%d", &n);
    if (check == 0)
        return 0;
    for (int i = n; i <= n + 1000; i++)
    {
        if (prime(i))
        {
            printf("%d", i);
            return 0;
        }
    }
    printf("BRAK");
    return 0;
}
