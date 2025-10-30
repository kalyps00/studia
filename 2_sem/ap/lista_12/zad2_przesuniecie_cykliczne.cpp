#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007
#define BASE 37
vector<ll> power;
vector<ll> prefix_hash;
string doubled;
int n;

ll get_substring_hash(int l, int r)
{
    return (prefix_hash[r + 1] - (prefix_hash[l] * power[r - l + 1]) % MOD + MOD) % MOD;
}

bool compare_rotations(int pos1, int pos2)
{
    if (get_substring_hash(pos1, pos1 + n - 1) == get_substring_hash(pos2, pos2 + n - 1))
        return false;

    // szukanie pierwszego rozniacaego sie
    int left = 0, right = n - 1;
    while (left < right)
    {
        int mid = (left + right) / 2;

        if (get_substring_hash(pos1, pos1 + mid) == get_substring_hash(pos2, pos2 + mid))
            left = mid + 1;
        else
            right = mid;
    }

    return doubled[pos1 + left] < doubled[pos2 + left];
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    string s;
    cin >> s;
    n = s.length();

    doubled = s + s;
    power.resize(2 * n + 1);
    power[0] = 1;
    for (int i = 1; i <= 2 * n; i++)
    {
        power[i] = (power[i - 1] * BASE) % MOD;
    }

    prefix_hash.resize(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++)
    {
        prefix_hash[i + 1] = (prefix_hash[i] * BASE + (doubled[i] - 'a' + 1)) % MOD;
    }

    int min_rotation = 0;
    for (int i = 1; i < n; i++)
    {
        if (compare_rotations(i, min_rotation))
        {
            min_rotation = i;
        }
    }
    cout << doubled.substr(min_rotation, n) << '\n';

    return 0;
}