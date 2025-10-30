#include "wymierna.hpp"
#include <stdexcept>
#include <cmath>
#include <string>
#include <climits>
namespace obliczenia
{

    int wymierna::computeGCD(int a, int b)
    {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    wymierna::wymierna(int licz_l, int mian_l)
    {
        if (mian_l == 0)
            throw dzielenie_przez_0();

        if (mian_l < 0)
        {
            licz_l = -licz_l;
            mian_l = -mian_l;
        }

        int gcd = computeGCD(licz_l, mian_l);
        licz = licz_l / gcd;
        mian = mian_l / gcd;

        if (licz == 0)
            mian = 1;
    }

    wymierna wymierna::operator-() const
    {
        return wymierna(-licz, mian);
    }

    wymierna wymierna::operator!() const
    {
        if (licz == 0)
            throw dzielenie_przez_0();
        return wymierna(mian, licz);
    }

    wymierna &wymierna::operator+=(const wymierna &other)
    {
        *this = *this + other;
        return *this;
    }

    wymierna &wymierna::operator-=(const wymierna &other)
    {
        *this = *this - other;
        return *this;
    }

    wymierna &wymierna::operator*=(const wymierna &other)
    {
        *this = *this * other;
        return *this;
    }

    wymierna &wymierna::operator/=(const wymierna &other)
    {
        *this = *this / other;
        return *this;
    }

    wymierna operator+(const wymierna &a, const wymierna &b)
    {
        long long term1 = static_cast<long long>(a.licz) * b.mian;
        long long term2 = static_cast<long long>(b.licz) * a.mian;
        long long new_licz = term1 + term2;
        long long new_mian = static_cast<long long>(a.mian) * b.mian;

        if (new_licz > INT_MAX || new_licz < INT_MIN)
            throw przekroczenie_zakresu();
        if (new_mian > INT_MAX || new_mian < INT_MIN)
            throw przekroczenie_zakresu();

        return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
    }

    wymierna operator-(const wymierna &a, const wymierna &b)
    {
        long long term1 = static_cast<long long>(a.licz) * b.mian;
        long long term2 = static_cast<long long>(b.licz) * a.mian;
        long long new_licz = term1 - term2;
        long long new_mian = static_cast<long long>(a.mian) * b.mian;

        if (new_licz > INT_MAX || new_licz < INT_MIN)
            throw przekroczenie_zakresu();
        if (new_mian > INT_MAX || new_mian < INT_MIN)
            throw przekroczenie_zakresu();

        return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
    }

    wymierna operator*(const wymierna &a, const wymierna &b)
    {
        long long new_licz = static_cast<long long>(a.licz) * b.licz;
        long long new_mian = static_cast<long long>(a.mian) * b.mian;

        if (new_licz > INT_MAX || new_licz < INT_MIN || new_mian > INT_MAX || new_mian < INT_MIN)
            throw przekroczenie_zakresu();

        return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
    }

    wymierna operator/(const wymierna &a, const wymierna &b)
    {
        if (b.licz == 0)
            throw dzielenie_przez_0();

        long long new_licz = static_cast<long long>(a.licz) * b.mian;
        long long new_mian = static_cast<long long>(a.mian) * b.licz;

        if (new_licz > INT_MAX || new_licz < INT_MIN || new_mian > INT_MAX || new_mian < INT_MIN)
            throw przekroczenie_zakresu();

        return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
    }

    wymierna::operator double() const
    {
        return static_cast<double>(licz) / mian;
    }

    wymierna::operator int() const
    {
        return static_cast<int>(std::round(static_cast<double>(licz) / mian));
    }

    std::ostream &operator<<(std::ostream &wy, const wymierna &w)
    {
        if (w.licz == 0)
        {
            wy << "0";
            return wy;
        }

        if (w.licz < 0)
            wy << "-";

        long long abs_licz = std::abs(w.licz);
        long long mian = w.mian;

        long long integer_part = abs_licz / mian;
        long long remainder = abs_licz % mian;

        wy << integer_part;

        if (remainder == 0)
            return wy;

        wy << ".";

        std::map<long long, int> remainders;
        std::string decimal;
        int pos = 0;

        while (remainder != 0 && remainders.find(remainder) == remainders.end())
        {
            remainders[remainder] = pos++;
            remainder *= 10;
            long long digit = remainder / mian;
            decimal += std::to_string(digit);
            remainder %= mian;
        }

        if (remainder == 0)
        {
            wy << decimal;
        }
        else
        {
            int start = remainders[remainder];
            wy << decimal.substr(0, start) << "(" << decimal.substr(start) << ")";
        }

        return wy;
    }

}