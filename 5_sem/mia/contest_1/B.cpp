#include <bits/stdc++.h>
using namespace std;
bool isCoverable(const vector<pair<int, int>> &positions, int fixed_val, bool fix_row)
{
    int other_val = -1;
    for (const auto &p : positions)
    {
        int r = p.first, c = p.second;
        if (fix_row && r != fixed_val)
        {
            if (other_val == -1)
                other_val = c;
            else if (other_val != c)
                return false;
        }
        else if (!fix_row && c != fixed_val)
        {
            if (other_val == -1)
                other_val = r;
            else if (other_val != r)
                return false;
        }
    }
    return true;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    int max_val = 0;
    vector<pair<int, int>> max_coords;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int val;
            cin >> val;
            if (val > max_val)
            {
                max_val = val;
                max_coords.clear();
                max_coords.push_back({i, j});
            }
            else if (val == max_val)
            {
                max_coords.push_back({i, j});
            }
        }
    }

    if (max_coords.empty())
    {
        cout << 0 << "\n";
        return;
    }
    bool covered = isCoverable(max_coords, max_coords[0].first, true);
    if (!covered)
    {
        covered = isCoverable(max_coords, max_coords[0].second, false);
    }

    if (covered)
    {
        cout << max_val - 1 << "\n";
    }
    else
    {
        cout << max_val << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}