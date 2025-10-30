#include "operatory.hpp"
#include <stdexcept>
#include <cmath>

namespace obliczenia
{

    // BASE OPERATOR1 class implementation
    operator1::operator1(std::shared_ptr<wyrazenie> arg) : arg(arg)
    {
        if (!arg)
        {
            throw std::invalid_argument("Argument operatora nie może być nullptr");
        }
    }

    // UNARY OPERATORS
    minus::minus(std::shared_ptr<wyrazenie> arg) : operator1(arg) {}

    int minus::oblicz() const
    {
        return -arg->oblicz();
    }

    std::string minus::zapis() const
    {
        return "-" + arg->zapis();
    }

    abs::abs(std::shared_ptr<wyrazenie> arg) : operator1(arg) {}

    int abs::oblicz() const
    {
        return std::abs(arg->oblicz());
    }

    std::string abs::zapis() const
    {
        return "|" + arg->zapis() + "|";
    }

    sgn::sgn(std::shared_ptr<wyrazenie> arg) : operator1(arg) {}

    int sgn::oblicz() const
    {
        int val = arg->oblicz();
        return (val > 0) - (val < 0);
    }

    std::string sgn::zapis() const
    {
        return "sgn(" + arg->zapis() + ")";
    }

    // BASE OPERATOR2 class implementation
    operator2::operator2(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator1(arg1), arg2(arg2)
    {
        if (!arg2)
        {
            throw std::invalid_argument("Drugi argument operatora nie może być nullptr");
        }
    }

    bool operator2::potrzebujeMniejNawiasow(const wyrazenie *w, bool lewa_strona) const
    {
        if (!w)
        {
            return true; // Safety check for null pointers
        }

        const operator2 *op = dynamic_cast<const operator2 *>(w);
        if (!op)
        {
            return true; // Jeśli to nie jest operator2, to nawiasy prawdopodobnie nie są potrzebne
        }

        if (this->priorytet() > op->priorytet())
        {
            return true; // Wyższy priorytet tego operatora, nawiasy nie są potrzebne
        }

        if (this->priorytet() == op->priorytet())
        {
            // Dla operatorów o tym samym priorytecie, decyduje łączność
            if (priorytet() == 3)
            { // Potęgowanie i logarytmowanie - prawostronnie łączne
                return !lewa_strona;
            }
            return lewa_strona; // Inne operatory są lewostronnie łączne
        }

        return false; // Niższy priorytet tego operatora, nawiasy są potrzebne
    }

    std::string operator2::zapisArg1() const
    {
        if (potrzebujeMniejNawiasow(arg.get(), true))
        {
            return arg->zapis();
        }
        else
        {
            return "(" + arg->zapis() + ")";
        }
    }

    std::string operator2::zapisArg2() const
    {
        if (potrzebujeMniejNawiasow(arg2.get(), false))
        {
            return arg2->zapis();
        }
        else
        {
            return "(" + arg2->zapis() + ")";
        }
    }

    // BINARY ARITHMETIC OPERATORS
    dodawanie::dodawanie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int dodawanie::oblicz() const
    {
        return arg->oblicz() + arg2->oblicz();
    }

    std::string dodawanie::zapis() const
    {
        return zapisArg1() + " + " + zapisArg2();
    }

    odejmowanie::odejmowanie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int odejmowanie::oblicz() const
    {
        return arg->oblicz() - arg2->oblicz();
    }

    std::string odejmowanie::zapis() const
    {
        return zapisArg1() + " - " + zapisArg2();
    }

    mnozenie::mnozenie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int mnozenie::oblicz() const
    {
        return arg->oblicz() * arg2->oblicz();
    }

    std::string mnozenie::zapis() const
    {
        return zapisArg1() + " * " + zapisArg2();
    }

    dzielenie::dzielenie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int dzielenie::oblicz() const
    {
        int mianownik = arg2->oblicz();
        if (mianownik == 0)
        {
            throw std::runtime_error("Dzielenie przez zero");
        }
        return arg->oblicz() / mianownik;
    }

    std::string dzielenie::zapis() const
    {
        return zapisArg1() + " / " + zapisArg2();
    }

    modulo::modulo(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int modulo::oblicz() const
    {
        int mianownik = arg2->oblicz();
        if (mianownik == 0)
        {
            throw std::runtime_error("Modulo przez zero");
        }
        return arg->oblicz() % mianownik;
    }

    std::string modulo::zapis() const
    {
        return zapisArg1() + " % " + zapisArg2();
    }

    potega::potega(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int potega::oblicz() const
    {
        return static_cast<int>(std::pow(arg->oblicz(), arg2->oblicz()));
    }

    std::string potega::zapis() const
    {
        return zapisArg1() + " ^ " + zapisArg2();
    }

    logarytm::logarytm(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int logarytm::oblicz() const
    {
        int podstawa = arg->oblicz();
        int liczba = arg2->oblicz();

        if (podstawa <= 1 || liczba <= 0)
        {
            throw std::runtime_error("Nieprawidłowe argumenty logarytmu");
        }

        int wynik = 0;
        while (liczba >= podstawa)
        {
            liczba /= podstawa;
            ++wynik;
        }
        return wynik;
    }

    std::string logarytm::zapis() const
    {
        return zapisArg1() + " _ " + zapisArg2();
    }

    // RELATIONAL OPERATORS
    mniejsze::mniejsze(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int mniejsze::oblicz() const
    {
        return arg->oblicz() < arg2->oblicz();
    }

    std::string mniejsze::zapis() const
    {
        return zapisArg1() + " < " + zapisArg2();
    }

    wieksze::wieksze(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int wieksze::oblicz() const
    {
        return arg->oblicz() > arg2->oblicz();
    }

    std::string wieksze::zapis() const
    {
        return zapisArg1() + " > " + zapisArg2();
    }

    mniejszeRowne::mniejszeRowne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int mniejszeRowne::oblicz() const
    {
        return arg->oblicz() <= arg2->oblicz();
    }

    std::string mniejszeRowne::zapis() const
    {
        return zapisArg1() + " <= " + zapisArg2();
    }

    wiekszeRowne::wiekszeRowne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int wiekszeRowne::oblicz() const
    {
        return arg->oblicz() >= arg2->oblicz();
    }

    std::string wiekszeRowne::zapis() const
    {
        return zapisArg1() + " >= " + zapisArg2();
    }

    rowne::rowne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int rowne::oblicz() const
    {
        return arg->oblicz() == arg2->oblicz();
    }

    std::string rowne::zapis() const
    {
        return zapisArg1() + " == " + zapisArg2();
    }

    rozne::rozne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int rozne::oblicz() const
    {
        return arg->oblicz() != arg2->oblicz();
    }

    std::string rozne::zapis() const
    {
        return zapisArg1() + " != " + zapisArg2();
    }

    // ADDITIONAL BINARY OPERATORS
    minimum::minimum(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int minimum::oblicz() const
    {
        return std::min(arg->oblicz(), arg2->oblicz());
    }

    std::string minimum::zapis() const
    {
        return "min(" + arg->zapis() + ", " + arg2->zapis() + ")";
    }

    maksimum::maksimum(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2)
        : operator2(arg1, arg2) {}

    int maksimum::oblicz() const
    {
        return std::max(arg->oblicz(), arg2->oblicz());
    }

    std::string maksimum::zapis() const
    {
        return "max(" + arg->zapis() + ", " + arg2->zapis() + ")";
    }

} // namespace obliczenia