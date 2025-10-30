#include <bits/stdc++.h>
using namespace std;

double original(double x_k, int k)
{
    double l = x_k / pow(2.0, k);
    double wyrazenie = 1.0 - sqrt(1.0 - l * l);
    return pow(2.0, k) * sqrt(2 * wyrazenie);
}
double improved(double x_k, int k)
{
    double l = x_k / pow(2.0, k);
    double wyrazenie = 1.0 + sqrt(1.0 - l * l);
    return (sqrt(2.0) * x_k) / (sqrt(wyrazenie));
}

int main()
{

    double x_orig = 2.0;
    double x_improved = 2.0;
    for (int k = 1; k <= 35; k++)
    {
        double next_orig = original(x_orig, k);
        double next_improved = improved(x_improved, k);
        cout << fixed << setprecision(16);
        cout << "K : " << k << " " << next_orig << " " << next_improved << endl;

        x_orig = next_orig;
        x_improved = next_improved;
    }
}