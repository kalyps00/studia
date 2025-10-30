#include <stdio.h>
int length(char word[])
{
    int count = 0;
    while (word[count] != 0)
    {
        count++;
    }
    return count;
}
int main(int argc, char *argv[])
{
    if (argc <= 1)
        return 0;
    int len = length(argv[1]), coin_value = 0, decimal_point = 1;
    int coins[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    int flag = 1;
    for (int i = len - 1; i >= 0; i--) //>=
    {

        if (argv[1][i] == ',' || argv[1][i] == '.') // check for end of grosze
        {
            if (len - i - 1 > 2) // handle to many decimal points e.g 10.337
            {
                printf("BLAD\n");
                return 0;
            }
            flag = 0;
            decimal_point = 100; // whole coins to ?grosze?
            continue;
        }
        if (argv[1][i] < '0' || argv[1][i] > '9') // handle non numbers
        {
            printf("BLAD\n");
            return 0;
        }
        coin_value += (argv[1][i] - '0') * decimal_point; // calculate value of current digit
        decimal_point *= 10;
    }
    if (flag) // no decimal part
        coin_value *= 100;
    for (int i = 0; i < 9; i++) // print values
    {
        int num_of_coins = coin_value / coins[i];
        if (num_of_coins > 0)
        {
            if (i < 3) // case zl
            {
                printf("%dx%dzl\n", num_of_coins, coins[i] / 100);
            }
            else // case grosze
            {
                printf("%dx%dgr\n", num_of_coins, coins[i]);
            }
        }
        coin_value %= coins[i];
    }
}
