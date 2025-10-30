int queens()
{
    int k = 1;
    b[0] = 0;
    int licznik = 0;
    while (k < n && k >= 0)
    {
        do
        {
            b[k]++;
        } while (b[k] < n && !isfree(k, b[k]));

        if (k == n - 1 && b[k] < n)
        {
            licznik++;
            continue;
        }

        if (b[k] < n)
            k++;
        else
        {
            b[k] = -1;
            k--;
        }
    }
    return licznik;