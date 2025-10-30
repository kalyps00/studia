#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define MOD 694202137
struct Node
{
    Node *next[2] = {nullptr, nullptr};
    int count = 0;
};
Node *trie = new Node;
void insert_trie(int n)
{
    Node *node = trie;
    node->count++;
    for (int i = 20; i >= 0; i--)
    {
        int bit = (n >> i) & 1;
        if (!node->next[bit])
            node->next[bit] = new Node;
        node = node->next[bit];
        node->count++;
    }
}
ll querry(int v, int k)
{
    Node *node = trie;
    ll result = 0;
    for (int i = 20; i >= 0 && node; i--)
    {
        int newval_bit = (v >> i) & 1;
        int k_bit = (k >> i) & 1;
        if (k_bit == 1)
        {
            node = node->next[newval_bit ^ 1];
        }
        else
        {
            Node *bigger = node->next[newval_bit ^ 1];
            if (bigger)
                result += bigger->count;
            node = node->next[newval_bit];
        }
    }
    if (node)
        result += node->count;
    return result;
}
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    ll answer = 0;
    for (int i = 0; i < n; i++)
    {
        answer += querry(a[i], k);
        insert_trie(a[i]);
    }
    cout << answer;
}