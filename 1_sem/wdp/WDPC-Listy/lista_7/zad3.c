#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
long long nwd(long long a, long long b)
{
    while (b)
    {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}
long long nww(long long a, long long b)
{
    return a / nwd(a, b) * b;
}

// Funkcja porównawcza dla sortowania
int compare(const void *a, const void *b)
{
    long long x = *(long long *)a;
    long long y = *(long long *)b;

    if (y > x)
    {
        return 1; // Liczba y powinna być przed x
    }
    else if (y < x)
    {
        return -1; // Liczba x powinna być przed y
    }
    else
    {
        return 0; // Liczby są równe
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    long long j[n], m[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &j[i]);
    }

    for (int i = 0; i < n; i++)
    {
        m[i] = nww(j[(i + n - 1) % n], nww(j[i], j[(i + 1) % n]));
    }

    long long r, p, q;
    scanf("%lld %lld %lld", &r, &p, &q);

    // 1
    long long left = 1, right = 1e18, answer1 = -1;
    while (left <= right)
    {
        long long mid = (left + right) / 2;
        long long count = 0;
        for (int i = 0; i < n; i++)
        {
            count += mid / m[i];
            if (count >= r)
                break;
        }
        if (count >= r)
        {
            answer1 = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    // 2
    long long events[n];
    for (int i = 0; i < n; i++)
    {
        events[i] = p / m[i];
    }
    qsort(events, n, sizeof(long long), compare);

    long long sum = 0, answer2 = 0;
    for (int i = 0; i < n; i++)
    {
        sum += events[i];
        answer2++;
        if (sum >= q)
            break;
    }

    printf("%lld %lld\n", answer1, answer2);
    return 0;
}
