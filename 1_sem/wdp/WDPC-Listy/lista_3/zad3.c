#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int primes[1000005];
int sieve[2000005];
int sumOfPairs[4000000];

void generateSieve(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (sieve[i] == 0)
            for (int j = i * i; j <= n; j += i)
            {
                sieve[j] = 1;
            }
    }
}

int contains3and7(int n)
{
    int hasThree = 0, hasSeven = 0;
    while (n)
    {
        int digit = n % 10;
        if (digit == 3)
            hasThree = 1;
        if (digit == 7)
            hasSeven = 1;
        n /= 10;
        if (hasThree && hasSeven)
            return 1;
    }
    return 0;
}

int binarySearch(int n, int left, int right)
{
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (primes[mid] >= n)
            right = mid;
        else
            left = mid + 1;
    }
    return left - 1;
}

int main()
{
    int count = 0;
    int lowerLimit = 0, upperLimit = 0, difference = 0, minDifference = __INT_MAX__;
    scanf("%d%d%d", &lowerLimit, &upperLimit, &difference);

    generateSieve(upperLimit);

    for (int i = lowerLimit; i <= upperLimit; i++)
    {
        if (sieve[i] == 0)
        {
            if (contains3and7(i))
            {
                primes[count] = i;
                count++;
            }
        }
    }

    int maxSum = -1;

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (i != j)
            {
                int sum = primes[i] + primes[j];
                sumOfPairs[sum]++;
                if (sum > maxSum)
                    maxSum = sum;
            }
        }
    }

    for (int i = 0; i < maxSum; i++)
    {
        if (sumOfPairs[i] >= 1)
        {
            int target = i - difference;
            if (target < 0)
                continue;
            int searchIndex = binarySearch(target, 0, count);

            if (searchIndex != -1)
            {
                if (binarySearch(i - primes[searchIndex], 0, count) == -1)
                {
                    int diff = i - primes[searchIndex];
                    if (diff < minDifference)
                        minDifference = diff;
                }
                else
                {
                    int newIndex = binarySearch(target, searchIndex + 1, count);
                    if (newIndex != -1)
                    {
                        int newDiff = i - primes[newIndex];
                        if (newDiff < minDifference)
                            minDifference = newDiff;
                    }
                }
            }
        }
    }

    printf("%d", minDifference);
}
