#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include "Complex.hpp"
#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace calc
{
    class Polynomial
    {
    private:
        int n;
        math::Complex *a; // Coefficients array

    public:
        // Constructors and Destructor
        Polynomial();
        Polynomial(std::initializer_list<math::Complex> coeffs);
        Polynomial(const Polynomial &other);
        Polynomial(Polynomial &&other);
        ~Polynomial();

        // Assignment Operators
        Polynomial &operator=(const Polynomial &other);
        Polynomial &operator=(Polynomial &&other);

        // Accessors
        int degree() const;
        math::Complex operator[](int i) const;
        math::Complex &operator[](int i);

        // Arithmetic Operators
        friend Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
        friend Polynomial operator-(const Polynomial &p1, const Polynomial &p2);
        friend Polynomial operator*(const Polynomial &p, const math::Complex &c);
        friend Polynomial operator*(const Polynomial &p1, const Polynomial &p2);

        // Function Call Operator
        math::Complex operator()(const math::Complex &x) const;

        // Stream Operators
        friend std::ostream &operator<<(std::ostream &os, const Polynomial &p);
        friend std::istream &operator>>(std::istream &is, Polynomial &p);
    };
}

#endif
