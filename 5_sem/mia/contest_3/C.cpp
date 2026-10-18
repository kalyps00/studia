#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    long long min_rating = LLONG_MIN;
    long long max_rating = LLONG_MAX;
    bool is_possible = true;

    for (int i = 0; i < n; i++)
    {
        long long rating_change;
        int division;
        cin >> rating_change >> division;

        if (i == 0)
        {
            if (division == 1)
            {
                min_rating = 1900;
            }
            else
            {
                max_rating = 1899;
            }
        }

        if (division == 1)
        {
            min_rating = max(min_rating, 1900LL);
        }
        else
        {
            max_rating = min(max_rating, 1899LL);
        }

        if (min_rating > max_rating)
        {
            is_possible = false;
        }

        if (min_rating != LLONG_MIN)
        {
            min_rating += rating_change;
        }

        if (max_rating != LLONG_MAX)
        {
            max_rating += rating_change;
        }
    }

    if (!is_possible)
    {
        cout << "Impossible\n";
    }
    else if (max_rating == LLONG_MAX)
    {
        cout << "Infinity\n";
    }
    else
    {
        cout << max_rating << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}