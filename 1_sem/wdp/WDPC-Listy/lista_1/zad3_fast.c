#include <stdio.h>
int main()
{
    int n;
    int check = scanf("%d", &n);
    if (!check || n < 1)
    {
        return 0;
    }
    int arr[n];
    for (int i = 0; i < n; i++) // wypelneinie zerami
    {
        arr[i] = 1;
    }
    int operation, count = 0, last1 = 0;
    for (int i = 1; i < n; i++) // wychodzi z petli zanim wypisze -1
    {
        scanf("%d", &operation);
        if (operation == -1)
        {
            count++; // git
        }
        if (operation == 1 || i == n - 1) // || i= n-1; // to moze sie jebac troche i nie licyzyc ostateniego
        {
            if (count > 0) // nadal zepsute
            {
                if (arr[last1] <= count) // update 1
                {
                    arr[last1] = count + 1;
                }

                for (int j = last1 + 1; count > 0; j++) // wpisanie -1
                {
                    arr[j] = count;
                    count--;
                }
            }
            if (operation == 1) // g
            {
                arr[i] = arr[i - 1] + 1; // wpisywanie 1
            }
            last1 = i;
            count = 0;
        }
    }
    for (int i = 0; i < n; i++) // wypisanie //wychodzi z petli zanim wypisze wynik jesli n-1=-1
    {
        printf("%d ", arr[i]);
    }
}