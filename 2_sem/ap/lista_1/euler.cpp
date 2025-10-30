#include <iostream>
#include <vector>
using namespace std;
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    vector<int> ans(1000000 + 1);
    for (int i = 0; i < ans.size(); i++)
    {
        ans[i] = i;
    }
    for (int i = 2; i < ans.size(); i++)
    {
        if (ans[i] == i)
        {
            for (int j = i; j < ans.size(); j += i)
            {
                ans[j] -= ans[j] / i;
            }
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        cout << ans[a] << '\n';
    }
}