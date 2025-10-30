#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD1 1000000007
#define MOD2 1000000009
#define BASE1 37
#define BASE2 53
vector<ll> powers1, powers2;
vector<ll> hash_forward1, hash_forward2;
vector<ll> hash_backward1, hash_backward2;
string s;
int n;

ll getHashForward1(int l, int r)
{
    return (hash_forward1[r + 1] - (hash_forward1[l] * powers1[r - l + 1]) % MOD1 + MOD1) % MOD1;
}

ll getHashForward2(int l, int r)
{
    return (hash_forward2[r + 1] - (hash_forward2[l] * powers2[r - l + 1]) % MOD2 + MOD2) % MOD2;
}

ll getHashBackward1(int l, int r)
{
    int rev_l = n - 1 - r;
    int rev_r = n - 1 - l;
    return (hash_backward1[rev_r + 1] - (hash_backward1[rev_l] * powers1[rev_r - rev_l + 1]) % MOD1 + MOD1) % MOD1;
}

ll getHashBackward2(int l, int r)
{
    int rev_l = n - 1 - r;
    int rev_r = n - 1 - l;
    return (hash_backward2[rev_r + 1] - (hash_backward2[rev_l] * powers2[rev_r - rev_l + 1]) % MOD2 + MOD2) % MOD2;
}

bool isPalindrome(int l, int r)
{
    bool hash_match = (getHashForward1(l, r) == getHashBackward1(l, r)) &&
                      (getHashForward2(l, r) == getHashBackward2(l, r));
    return hash_match;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> s;
    n = s.length();

    powers1.resize(n);
    powers2.resize(n);
    powers1[0] = powers2[0] = 1;
    for (int i = 1; i < n; i++)
    {
        powers1[i] = (powers1[i - 1] * BASE1) % MOD1;
        powers2[i] = (powers2[i - 1] * BASE2) % MOD2;
    }

    hash_forward1.resize(n + 1, 0);
    hash_forward2.resize(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        hash_forward1[i + 1] = (hash_forward1[i] * BASE1 + (s[i] - 'a' + 1)) % MOD1;
        hash_forward2[i + 1] = (hash_forward2[i] * BASE2 + (s[i] - 'a' + 1)) % MOD2;
    }

    hash_backward1.resize(n + 1, 0);
    hash_backward2.resize(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        hash_backward1[n - i] = (hash_backward1[n - i - 1] * BASE1 + (s[i] - 'a' + 1)) % MOD1;
        hash_backward2[n - i] = (hash_backward2[n - i - 1] * BASE2 + (s[i] - 'a' + 1)) % MOD2;
    }

    int max_len = 0;
    int start_pos = 0;

    // Sprawdzanie palindromów o nieparzystej długości
    for (int center = 0; center < n; center++)
    {
        int left = 0, right = min(center, n - 1 - center);

        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (isPalindrome(center - mid, center + mid))
            {
                if (2 * mid + 1 > max_len)
                {
                    max_len = 2 * mid + 1;
                    start_pos = center - mid;
                }
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }

    // Sprawdzanie palindromów o parzystej długości
    for (int center = 0; center < n - 1; center++)
    {
        int left = 0, right = min(center, n - 2 - center);

        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (isPalindrome(center - mid, center + 1 + mid))
            {
                if (2 * (mid + 1) > max_len)
                {
                    max_len = 2 * (mid + 1);
                    start_pos = center - mid;
                }
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }

    cout << s.substr(start_pos, max_len) << "\n";
    return 0;
}