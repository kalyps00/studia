#include <bits/stdc++.h>
using namespace std;
struct Result
{
    bool has_roots;
    double x1, x2;
};
Result metoda_szkolna(double a, double b, double c)
{
    Result res = {false, 0.0, 0.0};
    double delta = b * b - 4 * a * c;

    if (delta < 0)
    {
        return res;
    }
    else if (delta == 0)
    {
        res.has_roots = true;
        res.x1 = res.x2 = -b / (2 * a);
        return res;
    }
    else
    {
        res.has_roots = true;
        double sqrt_delta = sqrt(delta);
        res.x1 = (-b - sqrt_delta) / (2 * a);
        res.x2 = (-b + sqrt_delta) / (2 * a);
        return res;
    }
}

Result metoda_stabilna(double a, double b, double c)
{
    Result res = {false, 0.0, 0.0};
    double delta = b * b - 4 * a * c;

    if (delta < 0)
    {
        return res;
    }
    else if (delta == 0)
    {
        res.has_roots = true;
        res.x1 = res.x2 = -b / (2 * a);
        return res;
    }
    else
    {
        res.has_roots = true;
        double sqrt_delta = sqrt(delta);
        double q;
        if (b >= 0)
        {
            q = -0.5 * (b + sqrt_delta);
        }
        else
        {
            q = -0.5 * (b - sqrt_delta);
        }
        res.x1 = q / a;
        res.x2 = c / q;
        if (res.x1 > res.x2)
        {
            swap(res.x1, res.x2);
        }

        return res;
    }
}

int main()
{
    double a = 1.0, b = 10e8, c = 1.0;
    cout << setprecision(20);
    Result res2 = metoda_szkolna(a, b, c);
    if (res2.has_roots)
    {
        cout << "Roots (school method): " << res2.x1 << ", " << res2.x2 << endl;
    }
    Result res = metoda_stabilna(a, b, c);
    if (res.has_roots)
    {
        cout << "Roots: " << res.x1 << ", " << res.x2 << endl;
    }
}