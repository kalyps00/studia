#include <iostream>
#include <cmath>

using namespace std;
struct iter_x
{
    int count;
    double result;
};

iter_x inverse_sqrt(double a, double x0, double epsilon)
{
    double x = x0;
    int iters = 0;
    while (fabs(x - 1.0 / sqrt(a)) > epsilon)
    {
        x = x * (1.5 - 0.5 * a * x * x);
        iters++;
    }
    return {iters, x};
}

int main()
{
    double a_values[] = {2, 10, 0.5};
    double x0_values[] = {0.5, 0.1, 0.01};
    double epsilon = 1e-15;
    int iterations = 0;
    for (double a : a_values)
    {
        for (double x0 : x0_values)
        {
            iter_x out = inverse_sqrt(a, x0, epsilon);
            cout << "a=" << a << ", x0=" << x0
                 << ", wynik=" << out.result
                 << ", iters=" << out.count << endl;
        }
    }
    return 0;
}