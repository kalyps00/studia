#include <bits/stdc++.h>
using namespace std;

static int n;
static vector<int> tow_block_dyn;

static long long max_pile_jas = -1;
static long long min_abs_diff = (1LL << 60);

void dfs(int idx, long long sum_jas, long long tw_block_maja)
{
    if (idx == n)
    {
        if (sum_jas == 0 || tw_block_maja == 0)
        {
            return; // każda wieża musi mieć co najmniej 1 klocek
        }

        long long diff = llabs(sum_jas - tw_block_maja);
        if (diff == 0)
        {
            max_pile_jas = max(max_pile_jas, sum_jas);
        }
        min_abs_diff = min(min_abs_diff, diff);
        return;
    }

    // 1) klocek pomijamy
    dfs(idx + 1, sum_jas, tw_block_maja);

    // 2) klocek trafia do wieży Jasia
    dfs(idx + 1, sum_jas + tow_block_dyn[idx], tw_block_maja);

    // 3) klocek trafia do wieży Mai
    dfs(idx + 1, sum_jas, tw_block_maja + tow_block_dyn[idx]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    tow_block_dyn.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tow_block_dyn[i];
    }

    dfs(0, 0, 0);

    if (max_pile_jas >= 1)
    {
        cout << "TAK\n"
             << max_pile_jas << "\n";
    }
    else
    {
        cout << "NIE\n"
             << min_abs_diff << "\n";
    }

    return 0;
}
