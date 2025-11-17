#include <bits/stdc++.h>
using namespace std;

double func(double x)
{
    return x * x * x * x * x - x + 1;
}
double pochodna(double x)
{
    return 5 * x * x * x * x - 1;
}
double bisection(double a, double b)
{
    double fa = func(a);
    double fb = func(b);

    int max_iter = 1000;
    double c;
    for (int i = 0; i < max_iter; i++)
    {
        c = (a + b) / 2.0;
        double fc = func(c);

        if (abs(fc) < 1e-16 || (b - a) / 2.0 < 1e-16)
        {
            cout << "Bisekcja: zbiezność po " << i + 1 << " iteracjach" << endl;
            return c;
        }

        if (fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }

    cout << "Bisekcja: osiagnieto maksymalna liczbe iteracji" << endl;
    return c;
}
double newton(double x0)
{
    double x = x0;
    double eps = 1e-16;
    int max_iter = 1000;
    for (int i = 0; i < max_iter; i++)
    {
        double fx = func(x);
        double fpx = pochodna(x);
        double x_new = x - fx / fpx;
        if (abs(x_new - x) < eps)
        {
            cout << "Newton: zbiezność po " << i + 1 << " iteracjach" << endl;
            return x_new;
        }
        x = x_new;
    }
    cout << "Newton: osiagnieto maksymalna liczbe iteracji" << endl;
    return x;
}
double sieczne(double x0, double x1)
{
    double f0 = func(x0);
    double f1 = func(x1);
    double eps = 1e-16;
    int max_iter = 1000;
    for (int i = 0; i < max_iter; i++)
    {

        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);

        if (abs(x2 - x1) < eps)
        {
            cout << "Sieczne: zbiezność po " << i + 1 << " iteracjach" << endl;
            return x2;
        }

        x0 = x1;
        x1 = x2;
        f0 = f1;
        f1 = func(x2);
    }

    cout << "Sieczne: osiagnieto maksymalna liczbe iteracji" << endl;
    return x1;
}
double regula_falsi(double a, double b)
{
    double fa = func(a);
    double fb = func(b);
    double eps = 1e-16;
    int max_iter = 1000;

    double c;
    for (int i = 0; i < max_iter; i++)
    {
        c = (a * fb - b * fa) / (fb - fa);
        double fc = func(c);

        if (abs(fc) < eps)
        {
            cout << "Regula falsi: zbiezność po " << i + 1 << " iteracjach" << endl;
            return c;
        }

        if (fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }

    cout << "Regula falsi: osiagnieto maksymalnej liczbe iteracji:" << "" << endl;
    return c;
}
int main()
{
    cout << fixed << setprecision(16);

    const double root = -1.1673039782614186842560458998548;

    cout << "Dokładna wartość pierwiastka: " << root << endl;
    cout << "----------------------------------------" << endl;

    // Metoda bisekcji
    double result_bisection = bisection(-2.0, -1.0);
    cout << "Wynik bisekcji:    " << result_bisection << endl;
    cout << "Bład:              " << abs(result_bisection - root) << endl;
    cout << endl;

    // Metoda Newtona
    double result_newton = newton(-1.5);
    cout << "Wynik Newtona:     " << result_newton << endl;
    cout << "Bład:              " << abs(result_newton - root) << endl;
    cout << endl;

    // Metoda siecznych
    double result_sieczne = sieczne(-2.0, -1.0);
    cout << "Wynik siecznych:   " << result_sieczne << endl;
    cout << "Bład:              " << abs(result_sieczne - root) << endl;
    cout << endl;

    // Metoda regula falsi
    double result_regula_falsi = regula_falsi(-2.0, -1.0);
    cout << "Wynik regula falsi: " << result_regula_falsi << endl;
    cout << "Bład:               " << abs(result_regula_falsi - root) << endl;

    return 0;
}