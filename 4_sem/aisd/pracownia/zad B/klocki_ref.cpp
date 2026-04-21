#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> tow_block_dyn(n);
    int sum_h = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> tow_block_dyn[i];
        sum_h += tow_block_dyn[i];
    }

    vector<int> dp(sum_h + 1, -1), next_dp(sum_h + 1, -1);
    vector<int> active, next_active;
    vector<char> in_next(sum_h + 1, 0);

    dp[0] = 0;
    active.push_back(0);

    for (int h : tow_block_dyn)
    {
        next_active.clear();

        auto push_state = [&](int diff, int low)
        {
            if (low > next_dp[diff])
            {
                next_dp[diff] = low;
            }
            if (!in_next[diff])
            {
                in_next[diff] = 1;
                next_active.push_back(diff);
            }
        };

        for (int diff : active)
        {
            int low = dp[diff];
            if (low < 0)
            {
                continue;
            }

            // 1) pomijamy klocek
            push_state(diff, low);

            // 2) dokładamy do wyższej wieży
            push_state(diff + h, low);

            // 3) dokładamy do niższej wieży
            if (h <= diff)
            {
                push_state(diff - h, low + h);
            }
            else
            {
                push_state(h - diff, low + diff);
            }
        }

        for (int diff : active)
        {
            dp[diff] = -1;
        }
        for (int diff : next_active)
        {
            dp[diff] = next_dp[diff];
            next_dp[diff] = -1;
            in_next[diff] = 0;
        }

        active.swap(next_active);
    }

    long long max_pile_jas = dp[0];
    if (max_pile_jas > 0)
    {
        cout << "TAK\n"
             << max_pile_jas << "\n";
        return 0;
    }

    int tw_block_maja = -1;
    for (int diff = 1; diff <= sum_h; diff++)
    {
        if (dp[diff] > 0)
        {
            tw_block_maja = diff;
            break;
        }
    }

    cout << "NIE\n"
         << tw_block_maja << "\n";
    return 0;
}
