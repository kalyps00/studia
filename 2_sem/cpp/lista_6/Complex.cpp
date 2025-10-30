#include "Complex.hpp"
#include <stdexcept>
#include <cmath>

namespace math
{
    double Complex::re() const
    {
        return r;
    }
    double Complex::im() const
    {
        return i;
    }
    void Complex::re(double r)
    {
        this->r = r;
    }
    void Complex::im(double i)
    {
        this->i = i;
    }
    Complex Complex::conjugated() const
    {
        return Complex(r, -i);
    }
    Complex operator+(const Complex &x, const Complex &y)
    {
        return Complex(x.re() + y.re(), x.im() + y.im());
    }
    Complex operator-(const Complex &x, const Complex &y)
    {
        return Complex(x.re() - y.re(), x.im() - y.im());
    }
    Complex operator*(const Complex &x, const Complex &y)
    {
        return Complex(x.re() * y.re() - x.im() * y.im(), x.re() * y.im() + x.im() * y.re());
    }
    Complex operator/(const Complex &x, const Complex &y)
    {
        if (y.re() == 0 && y.im() == 0)
            throw std::invalid_argument("Division by zero");
        double denominator = y.re() * y.re() + y.im() * y.im();
        return Complex((x.re() * y.re() + x.im() * y.im()) / denominator,
                       (x.im() * y.re() - x.re() * y.im()) / denominator);
    }
    std::ostream &operator<<(std::ostream &os, const Complex &c)
    {
        os << c.re() << (c.im() >= 0 ? "+" : "") << c.im() << "i";
        return os;
    }
    std::istream &operator>>(std::istream &is, Complex &c)
    {
        double real, imag;
        char sign, i;
        is >> real >> sign >> imag >> i;
        if (i != 'i' || (sign != '+' && sign != '-'))
            throw std::invalid_argument("Invalid complex number format");
        c.re(real);
        c.im((sign == '+') ? imag : -imag);
        return is;
    }
}