#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    cout.tie(0);
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        int ans = 0;
        int sq = sqrt(num);
        for (int j = 1; j <= sq; j++)
        {

            if (num % j == 0)
            {
                if (j * j == num)
                    ans--;
                ans += 2;
            }
        }
        cout << ans << '\n';
    }
}