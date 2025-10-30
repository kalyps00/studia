#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
    int n, m;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        v.push_back(a);
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int brek = 0, x;
        cin >> x;
        int b = -1, e = n, s = (b + e) / 2;
        while (e - b > 1)
        {
            if (x < v[s])
            {
                e = s;
            }
            else if (x > v[s])
            {
                b = s;
            }
            else
            {
                cout << s + 1 << endl;
                brek = 1;
                break;
            }
            s = (b + e) / 2;
        }
        if (brek == 0)
            cout << -1 << endl;
    }
}