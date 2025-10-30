#ifndef OPERATORY_HPP
#define OPERATORY_HPP

#include "wyrazenie.hpp"
#include <cmath>
#include <stdexcept>

namespace obliczenia
{

    // Klasa bazowa dla operatorów unarnych
    class operator1 : public wyrazenie
    {
    protected:
        std::unique_ptr<wyrazenie> operand;

    public:
        explicit operator1(std::unique_ptr<wyrazenie> operand) : operand(std::move(operand))
        {
            if (!this->operand)
            {
                throw std::invalid_argument("Operand nie może być nullptr");
            }
        }
    };

    // Klasa reprezentująca operator unarny minus
    class minus : public operator1
    {
    public:
        explicit minus(std::unique_ptr<wyrazenie> operand) : operator1(std::move(operand)) {}

        int oblicz() const override
        {
            return -operand->oblicz();
        }

        std::string zapis() const override
        {
            return "-" + operand->zapis();
        }
    };

    // Klasa bazowa dla operatorów binarnych
    class operator2 : public operator1
    {
    protected:
        std::unique_ptr<wyrazenie> operand2;

    public:
        operator2(std::unique_ptr<wyrazenie> operand1, std::unique_ptr<wyrazenie> operand2)
            : operator1(std::move(operand1)), operand2(std::move(operand2))
        {
            if (!this->operand2)
            {
                throw std::invalid_argument("Drugi operand nie może być nullptr");
            }
        }
    };

    // Klasa reprezentująca operator dodawania
    class dodawanie : public operator2
    {
    public:
        dodawanie(std::unique_ptr<wyrazenie> operand1, std::unique_ptr<wyrazenie> operand2)
            : operator2(std::move(operand1), std::move(operand2)) {}

        int oblicz() const override
        {
            return operand->oblicz() + operand2->oblicz();
        }

        std::string zapis() const override
        {
            return "(" + operand->zapis() + " + " + operand2->zapis() + ")";
        }
    };

    // Klasa reprezentująca operator mnożenia
    class mnozenie : public operator2
    {
    public:
        mnozenie(std::unique_ptr<wyrazenie> operand1, std::unique_ptr<wyrazenie> operand2)
            : operator2(std::move(operand1), std::move(operand2)) {}

        int oblicz() const override
        {
            return operand->oblicz() * operand2->oblicz();
        }

        std::string zapis() const override
        {
            return "(" + operand->zapis() + " * " + operand2->zapis() + ")";
        }
    };

    // Klasa reprezentująca operator potęgowania
    class potegowanie : public operator2
    {
    public:
        potegowanie(std::unique_ptr<wyrazenie> operand1, std::unique_ptr<wyrazenie> operand2)
            : operator2(std::move(operand1), std::move(operand2)) {}

        int oblicz() const override
        {
            return static_cast<int>(std::pow(operand->oblicz(), operand2->oblicz()));
        }

        std::string zapis() const override
        {
            return "(" + operand->zapis() + " ^ " + operand2->zapis() + ")";
        }
    };

    // Klasa reprezentująca operator unarny wartość bezwzględna (abs)
    class abs : public operator1
    {
    public:
        explicit abs(std::unique_ptr<wyrazenie> operand) : operator1(std::move(operand)) {}

        int oblicz() const override
        {
            return std::abs(operand->oblicz());
        }

        std::string zapis() const override
        {
            return "|" + operand->zapis() + "|";
        }
    };

    // Klasa reprezentująca operator binarny modulo
    class modulo : public operator2
    {
    public:
        modulo(std::unique_ptr<wyrazenie> operand1, std::unique_ptr<wyrazenie> operand2)
            : operator2(std::move(operand1), std::move(operand2)) {}

        int oblicz() const override
        {
            int divisor = operand2->oblicz();
            if (divisor == 0)
            {
                throw std::domain_error("Dzielenie przez zero w operatorze modulo");
            }
            return operand->oblicz() % divisor;
        }

        std::string zapis() const override
        {
            return "(" + operand->zapis() + " % " + operand2->zapis() + ")";
        }
    };

} // namespace obliczenia

#endif // OPERATORY_HPP