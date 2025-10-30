#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007

struct Node
{
    Node *next[26] = {nullptr};
    bool is_word = false;
};

Node *root = new Node;

void insert_trie(const string &word)
{
    Node *node = root;
    for (char c : word)
    {
        int idx = c - 'a';
        if (!node->next[idx])
        {
            node->next[idx] = new Node();
        }
        node = node->next[idx];
    }
    node->is_word = true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string text;
    cin >> text;
    int n = text.length();

    int k;
    cin >> k;

    for (int i = 0; i < k; i++)
    {
        string word;
        cin >> word;
        insert_trie(word);
    }
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        if (dp[i] == 0)
            continue;

        Node *node = root;
        for (int j = i; j < n; j++)
        {
            int idx = text[j] - 'a';
            if (!node->next[idx])
                break; // nie istnieje

            node = node->next[idx];
            if (node->is_word)
            {
                dp[j + 1] = (dp[j + 1] + dp[i]) % MOD;
            }
        }
    }
    cout << dp[n] << endl;

    return 0;
}