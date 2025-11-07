#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Funkcja do obliczania 1/sqrt(m) metodą Newtona
double inverse_sqrt_newton(double m, double y0, double epsilon, int max_iter)
{
    double y = y0;
    for (int i = 0; i < max_iter; i++)
    {
        double y_prev = y;
        y = y * (1.5 - 0.5 * m * y * y);
        if (fabs(y - y_prev) < epsilon)
        {
            break;
        }
    }
    return y;
}
double my_sqrt(double a, double x0, double epsilon = 1e-12, int max_iter = 20)
{
    if (a <= 0)
        return 0;

    // Rozkład a = m * 2^c
    int c;
    double m = frexp(a, &c); // m w [0.5, 1), c - wykładnik

    // Oblicz 1/sqrt(m) metodą Newtona
    double inv_sqrt_m = inverse_sqrt_newton(m, x0, epsilon, max_iter);

    // Oblicz sqrt(m) = m * (1/sqrt(m))
    double sqrt_m = m * inv_sqrt_m;

    // Oblicz 2^(c/2)
    double power_factor;
    if (c % 2 == 0)
    {
        // c parzyste
        power_factor = pow(2, c / 2);
    }
    else
    {
        // c nieparzyste
        power_factor = pow(2, (c - 1) / 2) * sqrt(2.0);
    }

    return sqrt_m * power_factor;
}

// Funkcja testująca zbieżność dla różnych wartości początkowych
void test_convergence(double a, const vector<double> &initial_guesses)
{
    cout << "Test zbieżności dla a = " << a << " (prawdziwy sqrt = " << sqrt(a) << ")\n";
    cout << "Rozkład: a = m * 2^c, gdzie ";

    int c;
    double m = frexp(a, &c);
    cout << "m = " << m << ", c = " << c << endl;

    for (double x0 : initial_guesses)
    {
        double result = my_sqrt(a, x0);
        double error = fabs(result - sqrt(a));
        cout << "x0 = " << x0 << " -> wynik = " << result
             << ", błąd = " << error
             << (error < 1e-10 ? " ✓" : " ✗") << endl;
    }
    cout << endl;
}

int main()
{
    // Testowane wartości
    vector<double> test_values = {0.25, 0.5, 1.0, 2.0, 4.0, 10.0, 100.0};

    // Różne wartości początkowe do przetestowania
    vector<double> initial_guesses = {0.1, 0.5, 1.0, 1.5, 2.0, 5.0, 10.0};

    cout << "BADANIE ZBIEŻNOŚCI METODY NEWTONA DLA √a\n";
    cout << "========================================\n\n";

    for (double a : test_values)
    {
        test_convergence(a, initial_guesses);
    }

    // Szczegółowe badanie dla wybranej wartości
    cout << "SZCZEGÓŁOWA ANALIZA DLA a = 2.0:\n";
    double a = 2.0;
    int c;
    double m = frexp(a, &c);
    double target = 1.0 / sqrt(m);

    cout << "m = " << m << ", c = " << c << endl;
    cout << "1/sqrt(m) = " << target << endl
         << endl;

    for (double x0 : initial_guesses)
    {
        cout << "x0 = " << x0 << ":\n";
        double y = x0;
        for (int iter = 1; iter <= 10; iter++)
        {
            y = y * (1.5 - 0.5 * m * y * y);
            double error = fabs(y - target);
            cout << "  Iteracja " << iter << ": y = " << y << ", błąd = " << error;
            if (error < 1e-15)
                cout << " ✓ ZBIEŻNOŚĆ OSIĄGNIĘTA";
            cout << endl;
            if (error < 1e-15)
                break;
        }
        cout << endl;
    }

    return 0;
}