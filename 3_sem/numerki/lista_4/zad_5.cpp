#include <iostream>
#include <cmath>

using namespace std;

void find_inverse(double R, double x0, double epsilon)
{
    double x = x0;
    int iterations = 0;
    while (fabs(x - 1.0 / R) > epsilon)
    {
        x = x * (2 - R * x);
        iterations++;
    }
    cout << "R=" << R << ", x0=" << x0 << ", wynik=" << x << ", iteracje=" << iterations << endl;
}

int main()
{
    double epsilon = 1e-15;
    double R_values[] = {2, 10, 0.5};
    double x0_values[] = {0.1, 0.01, 0.001};
    for (double R : R_values)
    {
        for (double x0 : x0_values)
        {
            if (x0 > 0 && x0 < 1.0 / R)
            {
                find_inverse(R, x0, epsilon);
            }
        }
    }
    return 0;
}