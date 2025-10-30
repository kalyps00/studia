#include <stdio.h>
int main()
{
    int n;
    int check = scanf("%d", &n);
    if (!check || n < 1)
    {
        return 0;
    }
    int arr[n + 5];
    arr[0] = 1;
    for (int i = 1; i < n + 5; i++) // wypelneinie zerami
    {
        arr[i] = 0;
    }
    int operation, last_op = 1;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &operation);
        if (operation == 1) // operacja 1
        {
            arr[i] = arr[i - 1] + 1;
            // lastgreater = i;
            last_op = 1;
        }
        else // operacja -1
        {
            if (arr[i - 1] > 1) // poprzedni >1
            {
                if (last_op == 1)
                {
                    arr[i] = 1;
                }
                else
                {
                    arr[i] = arr[i - 1] - 1; // obecny = poprzedni-1;
                }
                last_op = -1;
            }
            else // poprzedni =1
            {
                arr[i] = 1;
                for (int j = i; arr[j] == arr[j - 1]; j--) // poprzednie malejace +=1
                {
                    arr[j - 1]++;
                }
                last_op = -1;
            }
        }
    }
    for (int i = 0; i < n; i++) // wypisanie
    {
        printf("%d ", arr[i]);
    }
}