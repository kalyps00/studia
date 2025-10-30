#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>
namespace math
{

    class Complex
    {
        double r, i;

    public:
        Complex(double a = 0, double b = 0) : r(a), i(b) {}

    public:
        double re() const;
        double im() const;
        void re(double r);
        void im(double i);
        Complex conjugated() const;
    };
    Complex operator+(const Complex &x, const Complex &y);
    Complex operator-(const Complex &x, const Complex &y);
    Complex operator*(const Complex &x, const Complex &y);
    Complex operator/(const Complex &x, const Complex &y);
    std::ostream &operator<<(std::ostream &os, const Complex &c);
    std::istream &operator>>(std::istream &is, Complex &c);
}
#endif