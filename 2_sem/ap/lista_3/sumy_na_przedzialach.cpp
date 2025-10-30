#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> numbers(n);
    int len = ceil(sqrt(n));
    vector<ll> blocks(len, 0);

    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
        blocks[i / len] += numbers[i];
    }

    for (int i = 0; i < q; i++)
    {
        int operation, a, b;
        cin >> operation >> a >> b;
        ll sum = 0;

        if (operation == 1)
        {
            a--;
            blocks[a / len] += (b - numbers[a]);
            numbers[a] = b;
        }
        else
        {
            a--;
            b--;
            int left = a / len, right = b / len;
            if (left == right)
            {
                for (int j = a; j <= b; j++)
                {
                    sum += numbers[j];
                }
            }
            else
            {
                // Sumujemy elementy od indeksu a do końca lewego bloku
                for (int j = a; j < (left + 1) * len; j++)
                {
                    sum += numbers[j];
                }
                // Sumujemy całe bloki między lewym a prawym
                for (int j = left + 1; j < right; j++)
                {
                    sum += blocks[j];
                }
                // Sumujemy elementy od początku prawego bloku do indeksu b włącznie
                for (int j = right * len; j <= b; j++)
                {
                    sum += numbers[j];
                }
            }
            cout << sum << '\n';
        }
    }
    return 0;
}
