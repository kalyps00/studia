#include <bits/stdc++.h>
using namespace std;

int main()
{
    double a = 0.0, b = 1.0;
    double alpha = 0.49;
    cout << fixed << setprecision(6);
    for (int k = 1; k <= 5; ++k)
    {
        double m = 0.5 * (a + b); // m_{k}
        cout << "k=" << k << " m=" << m << " f(m)=" << (m - alpha) << " aprox |e|: " << 1.0 / pow(2, k) << '\n';
        if ((a - alpha) * (m - alpha) <= 0)
        { // if sign change in [a,m]
            b = m;
        }
        else
        {
            a = m;
        }
    }
    return 0;
}
