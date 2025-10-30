#ifndef WYMIERNA_HPP
#define WYMIERNA_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <numeric> // For std::gcd
#include <limits>  // For std::numeric_limits
#include <cmath>   // For std::round

namespace obliczenia
{

    // Exception hierarchy
    class wyjatek_wymierny : public std::logic_error
    {
    public:
        explicit wyjatek_wymierny(const std::string &what_arg) : std::logic_error(what_arg) {}
        explicit wyjatek_wymierny(const char *what_arg) : std::logic_error(what_arg) {}
    };

    class dzielenie_przez_0 : public wyjatek_wymierny
    {
    public:
        dzielenie_przez_0() : wyjatek_wymierny("Dzielenie przez zero") {}
    };

    class przekroczenie_zakresu : public wyjatek_wymierny
    {
    public:
        przekroczenie_zakresu() : wyjatek_wymierny("Przekroczenie zakresu dla typu int") {}
    };

    class wymierna
    {
    private:
        long long licz; // Use long long internally to help detect overflow before assigning to int
        long long mian;

        void normalizuj() noexcept;
        static long long gcd(long long a, long long b) noexcept;

    public:
        // Constructors
        wymierna() noexcept;        // 0/1
        wymierna(int l, int m = 1); // l/m, also converts from int

        // Getters
        int get_licz() const noexcept;
        int get_mian() const noexcept;

        // Unary operators
        wymierna operator-() const; // Negation
        wymierna operator!() const; // Inverse

        // Binary assignment operators (members)
        wymierna &operator+=(const wymierna &other);
        wymierna &operator-=(const wymierna &other);
        wymierna &operator*=(const wymierna &other);
        wymierna &operator/=(const wymierna &other);

        // Type conversion operators
        explicit operator int() const noexcept;
        operator double() const noexcept;

        // Friend binary arithmetic operators
        friend wymierna operator+(const wymierna &w1, const wymierna &w2);
        friend wymierna operator-(const wymierna &w1, const wymierna &w2);
        friend wymierna operator*(const wymierna &w1, const wymierna &w2);
        friend wymierna operator/(const wymierna &w1, const wymierna &w2);

        // Friend stream output operator
        friend std::ostream &operator<<(std::ostream &wy, const wymierna &w);
    };

} // namespace obliczenia

#endif // WYMIERNA_HPP
