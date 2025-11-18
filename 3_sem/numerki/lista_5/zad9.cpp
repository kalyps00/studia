#include <bits/stdc++.h>
using namespace std;

vector<long double> olver_method(const function<long double(long double)> &f,
                                 const function<long double(long double)> &fp,
                                 const function<long double(long double)> &fpp,
                                 long double x0,
                                 long double tol = 1e-15L,
                                 int max_iter = 1000)
{
    long double x = x0;
    vector<long double> iterations;
    iterations.push_back(x);

    for (int i = 0; i < max_iter; ++i)
    {
        long double fx = f(x);
        long double fpx = fp(x);
        long double fppx = fpp(x);

        if (fabsl(fpx) < 1e-15L)
            break;

        long double delta_n = fx / fpx;
        long double correction = 0.5L * (fppx / fpx) * (delta_n * delta_n);
        long double x_new = x - delta_n - correction;

        iterations.push_back(x_new);

        if (fabsl(x_new - x) < tol)
            break;
        x = x_new;
    }

    return iterations;
}

vector<long double> calculate_p(const vector<long double> &iterations)
{
    vector<long double> p_values;
    size_t n = iterations.size();
    if (n < 4)
        return p_values;

    for (size_t i = 2; i + 1 < n; ++i)
    {
        long double diff1 = fabsl(iterations[i + 1] - iterations[i]);
        long double diff2 = fabsl(iterations[i] - iterations[i - 1]);
        long double diff3 = fabsl(iterations[i - 1] - iterations[i - 2]);

        if (diff2 < 1e-15L || diff3 < 1e-15L)
            continue;

        long double ratio1 = diff1 / diff2;
        long double ratio2 = diff2 / diff3;

        if (ratio1 > 0.0L && ratio2 > 0.0L)
        {
            long double p = logl(ratio1) / logl(ratio2);
            p_values.push_back(p);
        }
    }

    return p_values;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto f1 = [](long double x)
    { return x * x - 2.0L; };
    auto f1p = [](long double x)
    { return 2.0L * x; };
    auto f1pp = [](long double /*x*/)
    { return 2.0L; };

    auto f2 = [](long double x)
    { return x * x * x - 2.0L * x - 5.0L; };
    auto f2p = [](long double x)
    { return 3.0L * x * x - 2.0L; };
    auto f2pp = [](long double x)
    { return 6.0L * x; };

    auto f3 = [](long double x)
    { return sinl(x) - x / 2.0L; };
    auto f3p = [](long double x)
    { return cosl(x) - 0.5L; };
    auto f3pp = [](long double x)
    { return -sinl(x); };

    auto f4 = [](long double x)
    { return expl(x) + x - 2.0L; };
    auto f4p = [](long double x)
    { return expl(x) + 1.0L; };
    auto f4pp = [](long double x)
    { return expl(x); };

    auto f5 = [](long double x)
    { return expl(x) - 2.0L; };
    auto f5p = [](long double x)
    { return expl(x); };
    auto f5pp = [](long double x)
    { return expl(x); };

    vector<long double> iterations1 = olver_method(f1, f1p, f1pp, 1.5L);
    vector<long double> p_values1 = calculate_p(iterations1);

    vector<long double> iterations2 = olver_method(f2, f2p, f2pp, 2.0L);
    vector<long double> p_values2 = calculate_p(iterations2);

    vector<long double> iterations3 = olver_method(f3, f3p, f3pp, 2.0L);
    vector<long double> p_values3 = calculate_p(iterations3);

    vector<long double> iterations4 = olver_method(f4, f4p, f4pp, 1.0L);
    vector<long double> p_values4 = calculate_p(iterations4);

    vector<long double> iterations5 = olver_method(f5, f5p, f5pp, 0.5L);
    vector<long double> p_values5 = calculate_p(iterations5);

    // Wypisz z wysoką precyzją
    cout.setf(std::ios::fixed);
    cout << setprecision(50);

    cout << "p=" << p_values1[0] << '\n';

    cout << "p=" << p_values2[0] << '\n';

    cout << "p=" << p_values3[0] << '\n';

    cout << "p=" << p_values4[0] << '\n';

    cout << "p=" << p_values5[0] << '\n';

    return 0;
}
