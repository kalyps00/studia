#include <bits/stdc++.h>
using namespace std;
double f(double x) { return 3 * x * x - 5 * cos(7 * x - 1); }
const double L = sqrt(5.0 / 3.0), eps = 1e-7, STEP = 1e-3;
vector<double> R;
double bisect(double a, double b)
{
    double fa = f(a), fb = f(b);
    double len = b - a;
    if (len <= 0)
        return (a + b) / 2;
    double ratio = len / eps;
    if (ratio <= 1.0)
        return 0.5 * (a + b);
    int steps = (int)ceil(log2(ratio)); // minimalna liczba podziałów
    for (int i = 0; i < steps; ++i)
    {
        double m = (a + b) / 2, fm = f(m);
        if (fm == 0)
            return m;
        if (fa * fm <= 0)
        {
            b = m;
            fb = fm;
        }
        else
        {
            a = m;
            fa = fm;
        }
    }
    return (a + b) / 2;
}
void search(double a, double b, double fa, double fb)
{
    if (fa == 0)
    {
        R.push_back(a);
        return;
    }
    if (fb == 0)
    {
        R.push_back(b);
        return;
    }
    if (fa * fb > 0)
        return;
    if (b - a <= STEP)
    {
        R.push_back(bisect(a, b));
        return;
    }
    double m = (a + b) / 2, fm = f(m);
    search(a, m, fa, fm);
    search(m, b, fm, fb);
}
int main()
{
    for (double x = -L; x < L; x += STEP)
    {
        double x2 = min(x + STEP, L);
        double fx = f(x), fx2 = f(x2);
        if (fx * fx2 <= 0)
            search(x, x2, fx, fx2);
    }
    sort(R.begin(), R.end());
    cout << fixed << setprecision(9);
    for (double r : R)
        cout << r << " f(x0)=" << f(r) << "\n";
}
