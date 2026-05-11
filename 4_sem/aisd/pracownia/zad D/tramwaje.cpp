#include <bits/stdc++.h>
using namespace std;

int leaf_offset;

void update(vector<int> &tree, int idx, int val)
{
    idx += leaf_offset;
    tree[idx] = max(tree[idx], val);
    while (idx > 1)
    {
        idx /= 2;
        tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
    }
}

int query(const vector<int> &tree, int start, int end)
{
    if (start > end)
        return 0;

    start += leaf_offset;
    end += leaf_offset;
    int res = tree[start];

    if (start != end)
        res = max(res, tree[end]);

    while (start / 2 != end / 2)
    {
        if (start % 2 == 0)
            res = max(res, tree[start + 1]);
        if (end % 2 == 1)
            res = max(res, tree[end - 1]);
        start /= 2;
        end /= 2;
    }
    return res;
}

int get_pos(int x, const vector<int> &arr, int size)
{
    int l = 0, r = size - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return 0;
}

void solve()
{
    int n;
    if (!(cin >> n))
        return;

    vector<int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    if (n == 0)
    {
        cout << 0 << "\n";
        return;
    }

    vector<int> dp_pref(n, 1), dp_suff(n, 1);
    for (int i = 1; i < n; i++)
        if (A[i] > A[i - 1])
            dp_pref[i] = dp_pref[i - 1] + 1;

    for (int i = n - 2; i >= 0; i--)
        if (A[i] < A[i + 1])
            dp_suff[i] = dp_suff[i + 1] + 1;

    vector<int> uniq_A = A;
    sort(uniq_A.begin(), uniq_A.end());
    uniq_A.erase(unique(uniq_A.begin(), uniq_A.end()), uniq_A.end());
    int u_size = uniq_A.size();

    leaf_offset = 1;
    while (leaf_offset < u_size)
        leaf_offset *= 2;

    vector<int> tree(2 * leaf_offset, 0);
    int global_ans = 0;

    for (int i = 0; i < n; i++)
        global_ans = max(global_ans, dp_pref[i]);

    for (int i = 0; i < n; i++)
    {
        int pos = get_pos(A[i], uniq_A, u_size);

        if (pos > 0)
        {
            int max_L = query(tree, 0, pos - 1);
            if (max_L > 0)
                global_ans = max(global_ans, max_L + dp_suff[i]);
        }
        update(tree, pos, dp_pref[i]);
    }

    cout << global_ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    if (cin >> t)
    {
        while (t--)
        {
            solve();
        }
    }
    return 0;
}