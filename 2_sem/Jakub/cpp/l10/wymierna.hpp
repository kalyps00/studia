#ifndef WYMIERNA_HPP
#define WYMIERNA_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <cmath>

namespace obliczenia {

class wyjatek_wymierny : public std::logic_error {
public:
    wyjatek_wymierny(const std::string& what) : std::logic_error(what) {}
};

class dzielenie_przez_0 : public wyjatek_wymierny {
public:
    dzielenie_przez_0() : wyjatek_wymierny("Dzielenie przez zero") {}
};

class przekroczenie_zakresu : public wyjatek_wymierny {
public:
    przekroczenie_zakresu() : wyjatek_wymierny("Przekroczenie zakresu") {}
};

class wymierna {
private:
    int licz;
    int mian;

    static int computeGCD(int a, int b);

public:
    wymierna(int licz_l, int mian_l);
    wymierna(int n) : wymierna(n, 1) {}
    wymierna() : wymierna(0, 1) {}

    wymierna(const wymierna& other) = default;
    wymierna& operator=(const wymierna& other) = default;

    int getLicznik() const noexcept { return licz; }
    int getMianownik() const noexcept { return mian; }

    wymierna operator-() const;
    wymierna operator!() const;

    wymierna& operator+=(const wymierna& other);
    wymierna& operator-=(const wymierna& other);
    wymierna& operator*=(const wymierna& other);
    wymierna& operator/=(const wymierna& other);

    friend wymierna operator+(const wymierna& a, const wymierna& b);
    friend wymierna operator-(const wymierna& a, const wymierna& b);
    friend wymierna operator*(const wymierna& a, const wymierna& b);
    friend wymierna operator/(const wymierna& a, const wymierna& b);

    operator double() const;
    explicit operator int() const;

    friend std::ostream& operator<<(std::ostream& wy, const wymierna& w);
};

} 

#endif