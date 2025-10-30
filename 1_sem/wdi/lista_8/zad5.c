#include <stdio.h>

int minrek(int arr[], int left, int right)
{
    if (left == right)
        return arr[left];
    int mid = (left + right) / 2;
    int min1 = minrek(arr, left, mid);
    int min2 = minrek(arr, mid + 1, right);
    if (min1 < min2)
        return min1;
    else
        return min2;
}
int main()
{
    int arr[10] = {5};
    printf("%d", minrek(arr, 0, 0));
}