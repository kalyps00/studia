#include "Polynomial.hpp"
#include <utility>

namespace calc
{
    // Default Constructor
    Polynomial::Polynomial() : n(0), a(new math::Complex[1]{math::Complex()}) {}

    // Initializer List Constructor
    Polynomial::Polynomial(std::initializer_list<math::Complex> coeffs)
    {
        if (coeffs.size() == 0)
        {
            // Create default polynomial (same as default constructor)
            n = 0;
            a = new math::Complex[1]{math::Complex()};
        }
        else
        {
            n = coeffs.size() - 1;
            a = new math::Complex[n + 1];
            int i = 0;
            for (const auto &coeff : coeffs)
                a[i++] = coeff;
        }
    }

    // Copy Constructor
    Polynomial::Polynomial(const Polynomial &other) : n(other.n), a(new math::Complex[other.n + 1])
    {
        for (int i = 0; i <= n; ++i)
            a[i] = other.a[i];
    }

    // Move Constructor
    Polynomial::Polynomial(Polynomial &&other) : n(other.n), a(other.a)
    {
        other.a = nullptr;
        other.n = 0;
    }

    // Destructor
    Polynomial::~Polynomial()
    {
        delete[] a;
    }

    // Copy Assignment
    Polynomial &Polynomial::operator=(const Polynomial &other)
    {
        if (this == &other)
            return *this;
        delete[] a;
        n = other.n;
        a = new math::Complex[n + 1];
        for (int i = 0; i <= n; ++i)
            a[i] = other.a[i];
        return *this;
    }

    // Move Assignment
    Polynomial &Polynomial::operator=(Polynomial &&other)
    {
        if (this == &other)
            return *this;
        delete[] a;
        n = other.n;
        a = other.a;
        other.a = nullptr;
        other.n = 0;
        return *this;
    }

    // Accessors
    int Polynomial::degree() const
    {
        return n;
    }

    math::Complex Polynomial::operator[](int i) const
    {
        if (i < 0 || i > n)
            throw std::out_of_range("Index out of range.");
        return a[i];
    }

    math::Complex &Polynomial::operator[](int i)
    {
        if (i < 0 || i > n)
            throw std::out_of_range("Index out of range.");
        return a[i];
    }

    // Arithmetic Operators
    Polynomial operator+(const Polynomial &p1, const Polynomial &p2)
    {
        int max_deg = std::max(p1.n, p2.n);
        Polynomial result;
        delete[] result.a;
        result.n = max_deg;
        result.a = new math::Complex[max_deg + 1]{};

        for (int i = 0; i <= max_deg; ++i)
        {
            if (i <= p1.n)
                result.a[i] = result.a[i] + p1.a[i];
            if (i <= p2.n)
                result.a[i] = result.a[i] + p2.a[i];
        }
        return result;
    }

    Polynomial operator-(const Polynomial &p1, const Polynomial &p2)
    {
        int max_deg = std::max(p1.n, p2.n);
        Polynomial result;
        delete[] result.a;
        result.n = max_deg;
        result.a = new math::Complex[max_deg + 1]{};

        for (int i = 0; i <= max_deg; ++i)
        {
            if (i <= p1.n)
                result.a[i] = result.a[i] + p1.a[i];
            if (i <= p2.n)
                result.a[i] = result.a[i] - p2.a[i];
        }
        return result;
    }

    Polynomial operator*(const Polynomial &p, const math::Complex &c)
    {
        Polynomial result = p;
        for (int i = 0; i <= result.n; ++i)
            result.a[i] = result.a[i] * c;
        return result;
    }

    Polynomial operator*(const Polynomial &p1, const Polynomial &p2)
    {
        int result_deg = p1.n + p2.n;
        Polynomial result;
        delete[] result.a;
        result.n = result_deg;
        result.a = new math::Complex[result_deg + 1]{};

        for (int i = 0; i <= p1.n; ++i)
        {
            for (int j = 0; j <= p2.n; ++j)
            {
                result.a[i + j] = result.a[i + j] + (p1.a[i] * p2.a[j]);
            }
        }
        return result;
    }

    // Function Call Operator
    math::Complex Polynomial::operator()(const math::Complex &x) const
    {
        math::Complex result = a[n];
        for (int i = n - 1; i >= 0; --i)
            result = result * x + a[i];
        return result;
    }

    // Stream Operators
    std::ostream &operator<<(std::ostream &os, const Polynomial &p)
    {
        for (int i = p.n; i >= 0; --i)
        {
            os << p.a[i];
            if (i > 0)
                os << "x^" << i << " + ";
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Polynomial &p)
    {
        int degree;
        is >> degree;
        if (degree < 0)
            throw std::invalid_argument("Degree cannot be negative.");
        Polynomial temp;
        delete[] temp.a;
        temp.n = degree;
        temp.a = new math::Complex[degree + 1];
        for (int i = 0; i <= degree; ++i)
            is >> temp.a[i];
        p = std::move(temp);
        return is;
    }
}
