#include "wymierna.hpp"
#include <stdexcept>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

namespace obliczenia
{

    long long wymierna::gcd(long long a, long long b) noexcept
    {
        return std::abs(std::gcd(a, b));
    }

    void wymierna::normalizuj() noexcept
    {
        if (mian == 0)
        {
            licz = 0;
            mian = 1;
            return;
        }

        if (mian < 0)
        {
            licz = -licz;
            mian = -mian;
        }

        if (licz == 0)
        {
            mian = 1;
        }
        else
        {
            long long wsp_dziel = gcd(licz, mian);
            licz /= wsp_dziel;
            mian /= wsp_dziel;
        }
    }

    wymierna::wymierna() noexcept : licz(0), mian(1) {}

    wymierna::wymierna(int l, int m) : licz(l), mian(m)
    {
        if (m == 0)
        {
            throw dzielenie_przez_0();
        }
        normalizuj();
    }

    int wymierna::get_licz() const noexcept
    {
        return static_cast<int>(licz);
    }

    int wymierna::get_mian() const noexcept
    {
        return static_cast<int>(mian);
    }

    wymierna wymierna::operator-() const
    {
        wymierna temp(-this->licz, this->mian);
        if (temp.licz < std::numeric_limits<int>::min() || temp.licz > std::numeric_limits<int>::max() ||
            temp.mian < std::numeric_limits<int>::min() || temp.mian > std::numeric_limits<int>::max())
        {
            throw przekroczenie_zakresu();
        }
        return temp;
    }

    wymierna wymierna::operator!() const
    {
        if (licz == 0)
        {
            throw dzielenie_przez_0();
        }
        long long new_licz = mian;
        long long new_mian = licz;
        if (new_mian < 0)
        {
            new_licz = -new_licz;
            new_mian = -new_mian;
        }
        if (new_licz > std::numeric_limits<int>::max() || new_licz < std::numeric_limits<int>::min() ||
            new_mian > std::numeric_limits<int>::max() || new_mian < std::numeric_limits<int>::min())
        {
            throw przekroczenie_zakresu();
        }
        return wymierna(static_cast<int>(new_licz), static_cast<int>(new_mian));
    }

    wymierna &wymierna::operator+=(const wymierna &other)
    {
        long long nowy_licz = this->licz * other.mian + other.licz * this->mian;
        long long nowy_mian = this->mian * other.mian;

        this->licz = nowy_licz;
        this->mian = nowy_mian;
        normalizuj();

        if (this->licz > std::numeric_limits<int>::max() || this->licz < std::numeric_limits<int>::min() ||
            this->mian > std::numeric_limits<int>::max() || this->mian < std::numeric_limits<int>::min())
        {
            throw przekroczenie_zakresu();
        }
        return *this;
    }

    wymierna &wymierna::operator-=(const wymierna &other)
    {
        long long nowy_licz = this->licz * other.mian - other.licz * this->mian;
        long long nowy_mian = this->mian * other.mian;
        this->licz = nowy_licz;
        this->mian = nowy_mian;
        normalizuj();
        if (this->licz > std::numeric_limits<int>::max() || this->licz < std::numeric_limits<int>::min() ||
            this->mian > std::numeric_limits<int>::max() || this->mian < std::numeric_limits<int>::min())
        {
            throw przekroczenie_zakresu();
        }
        return *this;
    }

    wymierna &wymierna::operator*=(const wymierna &other)
    {
        long long nowy_licz = this->licz * other.licz;
        long long nowy_mian = this->mian * other.mian;
        this->licz = nowy_licz;
        this->mian = nowy_mian;
        normalizuj();
        if (this->licz > std::numeric_limits<int>::max() || this->licz < std::numeric_limits<int>::min() ||
            this->mian > std::numeric_limits<int>::max() || this->mian < std::numeric_limits<int>::min())
        {
            throw przekroczenie_zakresu();
        }
        return *this;
    }

    wymierna &wymierna::operator/=(const wymierna &other)
    {
        if (other.licz == 0)
        {
            throw dzielenie_przez_0();
        }
        long long nowy_licz = this->licz * other.mian;
        long long nowy_mian = this->mian * other.licz;
        this->licz = nowy_licz;
        this->mian = nowy_mian;
        normalizuj();
        if (this->licz > std::numeric_limits<int>::max() || this->licz < std::numeric_limits<int>::min() ||
            this->mian > std::numeric_limits<int>::max() || this->mian < std::numeric_limits<int>::min())
        {
            throw przekroczenie_zakresu();
        }
        return *this;
    }

    wymierna::operator double() const noexcept
    {
        return static_cast<double>(licz) / mian;
    }

    wymierna::operator int() const noexcept
    {
        return static_cast<int>(std::round(static_cast<double>(licz) / mian));
    }

    wymierna operator+(const wymierna &w1, const wymierna &w2)
    {
        wymierna temp = w1;
        temp += w2;
        return temp;
    }

    wymierna operator-(const wymierna &w1, const wymierna &w2)
    {
        wymierna temp = w1;
        temp -= w2;
        return temp;
    }

    wymierna operator*(const wymierna &w1, const wymierna &w2)
    {
        wymierna temp = w1;
        temp *= w2;
        return temp;
    }

    wymierna operator/(const wymierna &w1, const wymierna &w2)
    {
        if (w2.licz == 0)
        {
            throw dzielenie_przez_0();
        }
        wymierna temp = w1;
        temp /= w2;
        return temp;
    }

    std::ostream &operator<<(std::ostream &wy, const wymierna &w)
    {
        if (w.mian == 1)
        {
            wy << w.licz;
            return wy;
        }

        long long num = w.licz;
        long long den = w.mian;

        if (den == 0)
        {
            wy << "Error: Division by zero in stream output";
            return wy;
        }

        if (num < 0)
        {
            wy << "-";
            num = -num;
        }

        long long integer_part = num / den;
        wy << integer_part;

        long long remainder = num % den;
        if (remainder == 0)
        {
            return wy;
        }

        wy << ".";

        std::string decimal_part_str;
        std::map<long long, int> remainder_positions;

        int position = 0;
        while (remainder != 0 && remainder_positions.find(remainder) == remainder_positions.end())
        {
            remainder_positions[remainder] = position;
            remainder *= 10;
            decimal_part_str += std::to_string(remainder / den);
            remainder %= den;
            position++;
        }

        if (remainder == 0)
        {
            wy << decimal_part_str;
        }
        else
        {
            int non_repeating_len = remainder_positions[remainder];
            wy << decimal_part_str.substr(0, non_repeating_len);
            wy << "(" << decimal_part_str.substr(non_repeating_len) << ")";
        }

        return wy;
    }

} // namespace obliczenia
