#ifndef OPERATORY_HPP
#define OPERATORY_HPP

#include "wyrazenie.hpp"
#include <memory>
#include <cmath>

namespace obliczenia
{

    class operator1 : public wyrazenie
    {
    public:
        virtual ~operator1() = default;

    protected:
        operator1(std::shared_ptr<wyrazenie> arg);
        std::shared_ptr<wyrazenie> arg;
    };

    class minus : public operator1
    {
    public:
        minus(std::shared_ptr<wyrazenie> arg);
        int oblicz() const override;
        std::string zapis() const override;
    };

    class abs : public operator1
    {
    public:
        abs(std::shared_ptr<wyrazenie> arg);
        int oblicz() const override;
        std::string zapis() const override;
    };

    class sgn : public operator1
    {
    public:
        sgn(std::shared_ptr<wyrazenie> arg);
        int oblicz() const override;
        std::string zapis() const override;
    };

    class operator2 : public operator1
    {
    public:
        virtual ~operator2() = default;

    protected:
        operator2(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        std::shared_ptr<wyrazenie> arg2;

        // Helper methods for formatting expressions with proper parentheses
        virtual int priorytet() const = 0;
        bool potrzebujeMniejNawiasow(const wyrazenie *w, bool lewa_strona = true) const;
        std::string zapisArg1() const;
        std::string zapisArg2() const;
    };

    // Arytmetyczne operatory binarne

    class dodawanie : public operator2
    {
    public:
        dodawanie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 1; }
    };

    class odejmowanie : public operator2
    {
    public:
        odejmowanie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 1; }
    };

    class mnozenie : public operator2
    {
    public:
        mnozenie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 2; }
    };

    class dzielenie : public operator2
    {
    public:
        dzielenie(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 2; }
    };

    class modulo : public operator2
    {
    public:
        modulo(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 2; }
    };

    class potega : public operator2
    {
    public:
        potega(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 3; }
    };

    class logarytm : public operator2
    {
    public:
        logarytm(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 3; }
    };

    // Operatory relacyjne

    class mniejsze : public operator2
    {
    public:
        mniejsze(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 0; }
    };

    class wieksze : public operator2
    {
    public:
        wieksze(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 0; }
    };

    class mniejszeRowne : public operator2
    {
    public:
        mniejszeRowne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 0; }
    };

    class wiekszeRowne : public operator2
    {
    public:
        wiekszeRowne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 0; }
    };

    class rowne : public operator2
    {
    public:
        rowne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 0; }
    };

    class rozne : public operator2
    {
    public:
        rozne(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 0; }
    };

    // Dodatkowe operatory binarne

    class minimum : public operator2
    {
    public:
        minimum(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 2; }
    };

    class maksimum : public operator2
    {
    public:
        maksimum(std::shared_ptr<wyrazenie> arg1, std::shared_ptr<wyrazenie> arg2);
        int oblicz() const override;
        std::string zapis() const override;
        int priorytet() const override { return 2; }
    };

} // namespace obliczenia

#endif // OPERATORY_HPP