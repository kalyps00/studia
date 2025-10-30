#include "Complex.hpp"
#include "Polynomial.hpp"
#include <iostream>
#include <cmath>

// Helper function to calculate square root of complex number
math::Complex complexSqrt(const math::Complex &z)
{
    double r = std::sqrt(z.re() * z.re() + z.im() * z.im());
    double theta = std::atan2(z.im(), z.re());

    double real = std::sqrt(r) * std::cos(theta / 2);
    double imag = std::sqrt(r) * std::sin(theta / 2);

    return math::Complex(real, imag);
}

// Function to solve quadratic equation ax^2 + bx + c = 0
std::pair<math::Complex, math::Complex> solveQuadratic(const math::Complex &a, const math::Complex &b, const math::Complex &c)
{
    // Calculate discriminant: D = b^2 - 4ac
    math::Complex four(4.0, 0.0);
    math::Complex discriminant = b * b - four * a * c;

    // Calculate roots using quadratic formula: x = (-b ± sqrt(D)) / (2a)
    math::Complex sqrtD = complexSqrt(discriminant);
    math::Complex two(2.0, 0.0);
    math::Complex negB = math::Complex(-b.re(), -b.im());

    math::Complex root1 = (negB + sqrtD) / (two * a);
    math::Complex root2 = (negB - sqrtD) / (two * a);

    return {root1, root2};
}

void testComplexNumbers()
{
    std::cout << "\n=== Testing Complex Numbers ===\n";

    // Test constructors
    math::Complex c1(3.0, 4.0);
    math::Complex c2(1.0, -2.0);
    math::Complex c3; // Default constructor

    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    std::cout << "c3 = " << c3 << std::endl;

    // Test arithmetic operations
    std::cout << "c1 + c2 = " << c1 + c2 << std::endl;
    std::cout << "c1 - c2 = " << c1 - c2 << std::endl;
    std::cout << "c1 * c2 = " << c1 * c2 << std::endl;
    std::cout << "c1 / c2 = " << c1 / c2 << std::endl;

    // Test conjugate
    std::cout << "Conjugate of c1 = " << c1.conjugated() << std::endl;

    // Test real and imaginary parts
    std::cout << "Real part of c1 = " << c1.re() << std::endl;
    std::cout << "Imaginary part of c1 = " << c1.im() << std::endl;

    // Test setters
    c3.re(5.0);
    c3.im(6.0);
    std::cout << "After setting re and im, c3 = " << c3 << std::endl;
}

void testPolynomials()
{
    std::cout << "\n=== Testing Polynomials ===\n";

    // Test constructors
    calc::Polynomial p1{math::Complex(1), math::Complex(2), math::Complex(3)}; // 3x^2 + 2x + 1
    calc::Polynomial p2{math::Complex(2), math::Complex(1)};                   // x + 2
    calc::Polynomial p3;                                                       // Default constructor

    std::cout << "p1(x) = " << p1 << std::endl;
    std::cout << "p2(x) = " << p2 << std::endl;
    std::cout << "p3(x) = " << p3 << std::endl;

    // Test degree
    std::cout << "Degree of p1: " << p1.degree() << std::endl;
    std::cout << "Degree of p2: " << p2.degree() << std::endl;
    std::cout << "Degree of p3: " << p3.degree() << std::endl;

    // Test coefficient access
    std::cout << "p1 coefficients: ";
    for (int i = 0; i <= p1.degree(); ++i)
    {
        std::cout << p1[i] << " ";
    }
    std::cout << std::endl;

    // Test arithmetic operations
    std::cout << "p1 + p2 = " << p1 + p2 << std::endl;
    std::cout << "p1 - p2 = " << p1 - p2 << std::endl;
    std::cout << "p1 * math::Complex(2) = " << p1 * math::Complex(2) << std::endl;
    std::cout << "p1 * p2 = " << p1 * p2 << std::endl;

    // Test evaluation
    math::Complex z(1, 1);
    std::cout << "p1(1+i) = " << p1(z) << std::endl;

    // Test copy and move
    calc::Polynomial p4 = p1;
    std::cout << "p4 (copy of p1) = " << p4 << std::endl;

    calc::Polynomial p5 = std::move(p4);
    std::cout << "p5 (moved from p4) = " << p5 << std::endl;

    // Test modifying a coefficient
    p5[0] = math::Complex(10);
    std::cout << "After modifying p5[0] = 10, p5 = " << p5 << std::endl;
}

void quadraticSolver()
{
    std::cout << "\n=== Quadratic Equation Solver ===\n";
    std::cout << "This will solve a quadratic equation ax^2 + bx + c = 0 with complex coefficients.\n";

    math::Complex a, b, c;

    std::cout << "Enter coefficient a: ";
    std::cin >> a;

    std::cout << "Enter coefficient b: ";
    std::cin >> b;

    std::cout << "Enter coefficient c: ";
    std::cin >> c;

    std::cout << "Equation: (" << a << ")x^2 + (" << b << ")x + (" << c << ") = 0\n";

    try
    {
        if (a.re() == 0 && a.im() == 0)
        {
            if (b.re() == 0 && b.im() == 0)
            {
                std::cout << "Not a valid equation (both a and b are zero)." << std::endl;
            }
            else
            {
                // Linear equation: bx + c = 0
                math::Complex root = math::Complex(-c.re(), -c.im()) / b;
                std::cout << "This is a linear equation with one root:\n";
                std::cout << "x = " << root << std::endl;

                // Verify
                calc::Polynomial linear{c, b};
                std::cout << "\nVerifying: P(x) = " << linear(root) << std::endl;
            }
        }
        else
        {
            // Quadratic equation
            auto roots = solveQuadratic(a, b, c);

            std::cout << "Roots:\n";
            std::cout << "x1 = " << roots.first << std::endl;
            std::cout << "x2 = " << roots.second << std::endl;

            // Verify the roots
            calc::Polynomial quadratic{c, b, a};
            std::cout << "\nVerifying roots using the Polynomial class:\n";
            std::cout << "P(x1) = " << quadratic(roots.first) << std::endl;
            std::cout << "P(x2) = " << quadratic(roots.second) << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Complex Number and Polynomial Testing Program\n";
    std::cout << "============================================\n";

    try
    {
        testComplexNumbers();
        testPolynomials();
        quadraticSolver();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
/*
    sudo mv *.so /lib
    sudo ldconfig

    export LD_LIBRARY_PATH=.
    g++ main.cpp -L. -lmath -lpolynomial

    g++  -shared -fPIC -o libmath.so Complex.cpp
    g++  -shared -fPIC -o libpolynomial.so Polynomial.cpp

*/
