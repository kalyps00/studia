#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <forward_list>

namespace kalkulator
{

    // Abstract base class for all symbols in RPN expression
    class symbol
    {
    public:
        virtual ~symbol() = default;
        virtual double eval() const = 0;
        virtual std::string toString() const = 0;
    };

    // Base class for operands (values)
    class operand : public symbol
    {
    public:
        virtual ~operand() = default;
    };

    // Numeric literal
    class liczba : public operand
    {
    private:
        double wartosc;

    public:
        liczba(double w) : wartosc(w) {}
        double eval() const override { return wartosc; }
        std::string toString() const override { return std::to_string(wartosc); }
    };

    // Variable class with static collection of all variables
    class zmienna : public operand
    {
    private:
        std::string nazwa;
        static std::unordered_map<std::string, double> zmienne;

    public:
        zmienna(const std::string &n) : nazwa(n)
        {
            if (!isValidName(n))
            {
                throw std::invalid_argument("Invalid variable name: " + n);
            }
        }

        static bool isValidName(const std::string &name)
        {
            if (name.empty() || name.size() > 7)
                return false;

            // First character must be a letter
            if (!isalpha(name[0]))
                return false;

            // Rest can be letters or digits
            for (size_t i = 1; i < name.size(); ++i)
            {
                if (!isalnum(name[i]))
                    return false;
            }

            // Check if it's a reserved keyword
            const std::vector<std::string> keywords = {"print", "set", "to", "clear", "exit"};
            if (std::find(keywords.begin(), keywords.end(), name) != keywords.end())
            {
                return false;
            }

            // Check if it's a function name
            const std::vector<std::string> functions = {
                "+", "-", "*", "/", "mod", "log", "pow", "neg", "ln", "exp"};
            if (std::find(functions.begin(), functions.end(), name) != functions.end())
            {
                return false;
            }

            return true;
        }

        double eval() const override
        {
            auto it = zmienne.find(nazwa);
            if (it == zmienne.end())
            {
                throw std::runtime_error("Variable not defined: " + nazwa);
            }
            return it->second;
        }

        std::string toString() const override { return nazwa; }

        // Static methods for variable management
        static void set(const std::string &name, double value)
        {
            if (!isValidName(name))
            {
                throw std::invalid_argument("Invalid variable name: " + name);
            }
            zmienne[name] = value;
        }

        static void clearAll()
        {
            zmienne.clear();
        }

        static bool isDefined(const std::string &name)
        {
            return zmienne.find(name) != zmienne.end();
        }
    };

    // Initialize static member
    std::unordered_map<std::string, double> zmienna::zmienne;

    // Constants like pi, e, fi
    class stala : public operand
    {
    private:
        std::string nazwa;
        double wartosc;
        static std::unordered_map<std::string, double> stale;

    public:
        stala(const std::string &n) : nazwa(n)
        {
            auto it = stale.find(n);
            if (it == stale.end())
            {
                throw std::invalid_argument("Unknown constant: " + n);
            }
            wartosc = it->second;
        }

        static void initialize()
        {
            stale["e"] = 2.718281828459;
            stale["pi"] = 3.141592653589;
            stale["fi"] = 1.618033988750;
        }

        static bool isConstant(const std::string &name)
        {
            return stale.find(name) != stale.end();
        }

        double eval() const override { return wartosc; }
        std::string toString() const override { return nazwa; }
    };

    // Initialize static member
    std::unordered_map<std::string, double> stala::stale;

    // Function base class
    class funkcja : public symbol
    {
    public:
        virtual ~funkcja() = default;
        virtual void wykonaj(std::stack<double> &stos) const = 0;
        double eval() const override
        {
            throw std::logic_error("Cannot directly evaluate a function");
        }
    };

    // Binary operation base class
    class funkcja_binarna : public funkcja
    {
    public:
        void wykonaj(std::stack<double> &stos) const override
        {
            if (stos.size() < 2)
            {
                throw std::runtime_error("Not enough operands for binary operation");
            }
            double b = stos.top();
            stos.pop();
            double a = stos.top();
            stos.pop();
            stos.push(oblicz(a, b));
        }

        virtual double oblicz(double a, double b) const = 0;
    };

    // Unary operation base class
    class funkcja_unarna : public funkcja
    {
    public:
        void wykonaj(std::stack<double> &stos) const override
        {
            if (stos.empty())
            {
                throw std::runtime_error("Not enough operands for unary operation");
            }
            double a = stos.top();
            stos.pop();
            stos.push(oblicz(a));
        }

        virtual double oblicz(double a) const = 0;
    };

    // Binary operations implementations
    class dodawanie : public funkcja_binarna
    {
    public:
        double oblicz(double a, double b) const override { return a + b; }
        std::string toString() const override { return "+"; }
    };

    class odejmowanie : public funkcja_binarna
    {
    public:
        double oblicz(double a, double b) const override { return a - b; }
        std::string toString() const override { return "-"; }
    };

    class mnozenie : public funkcja_binarna
    {
    public:
        double oblicz(double a, double b) const override { return a * b; }
        std::string toString() const override { return "*"; }
    };

    class dzielenie : public funkcja_binarna
    {
    public:
        double oblicz(double a, double b) const override
        {
            if (b == 0)
                throw std::runtime_error("Division by zero");
            return a / b;
        }
        std::string toString() const override { return "/"; }
    };

    class modulo : public funkcja_binarna
    {
    public:
        double oblicz(double a, double b) const override
        {
            if (b == 0)
                throw std::runtime_error("Modulo by zero");
            return std::fmod(a, b);
        }
        std::string toString() const override { return "mod"; }
    };

    class logarytm : public funkcja_binarna
    {
    public:
        double oblicz(double a, double b) const override
        {
            if (a <= 0 || b <= 0 || a == 1)
                throw std::runtime_error("Invalid logarithm arguments");
            return std::log(b) / std::log(a);
        }
        std::string toString() const override { return "log"; }
    };

    class potegowanie : public funkcja_binarna
    {
    public:
        double oblicz(double a, double b) const override
        {
            return std::pow(a, b);
        }
        std::string toString() const override { return "pow"; }
    };

    // Unary operations implementations
    class negacja : public funkcja_unarna
    {
    public:
        double oblicz(double a) const override { return -a; }
        std::string toString() const override { return "neg"; }
    };

    class logarytm_naturalny : public funkcja_unarna
    {
    public:
        double oblicz(double a) const override
        {
            if (a <= 0)
                throw std::runtime_error("Invalid logarithm argument");
            return std::log(a);
        }
        std::string toString() const override { return "ln"; }
    };

    class funkcja_exp : public funkcja_unarna
    {
    public:
        double oblicz(double a) const override { return std::exp(a); }
        std::string toString() const override { return "exp"; }
    };

    // Factory function to create appropriate symbol from a token
    std::unique_ptr<symbol> createSymbol(const std::string &token)
    {
        // Try to parse as a number
        try
        {
            size_t pos = 0;
            double value = std::stod(token, &pos);
            if (pos == token.length())
            {
                return std::make_unique<liczba>(value);
            }
        }
        catch (const std::exception &)
        {
            // Not a number
        }

        // Check if it's a constant
        if (stala::isConstant(token))
        {
            return std::make_unique<stala>(token);
        }

        // Check if it's a variable
        if (zmienna::isDefined(token) || zmienna::isValidName(token))
        {
            return std::make_unique<zmienna>(token);
        }

        // Check if it's a function
        if (token == "+")
            return std::make_unique<dodawanie>();
        if (token == "-")
            return std::make_unique<odejmowanie>();
        if (token == "*")
            return std::make_unique<mnozenie>();
        if (token == "/")
            return std::make_unique<dzielenie>();
        if (token == "mod")
            return std::make_unique<modulo>();
        if (token == "log")
            return std::make_unique<logarytm>();
        if (token == "pow")
            return std::make_unique<potegowanie>();
        if (token == "neg")
            return std::make_unique<negacja>();
        if (token == "ln")
            return std::make_unique<logarytm_naturalny>();
        if (token == "exp")
            return std::make_unique<funkcja_exp>();

        throw std::invalid_argument("Unrecognized token: " + token);
    }

    // Parse expression into a forward_list of symbols
    std::forward_list<std::unique_ptr<symbol>> parseExpression(const std::string &expression)
    {
        std::forward_list<std::unique_ptr<symbol>> symbols;
        auto it = symbols.before_begin();
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token)
        {
            try
            {
                it = symbols.insert_after(it, createSymbol(token));
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error("Error parsing token '" + token + "': " + e.what());
            }
        }

        return symbols;
    }

    // Evaluate an RPN expression from a forward_list of symbols
    double evaluateRPN(std::forward_list<std::unique_ptr<symbol>> &symbols)
    {
        std::stack<double> stos;

        for (auto &symbol : symbols)
        {
            if (auto *func = dynamic_cast<funkcja *>(symbol.get()))
            {
                try
                {
                    func->wykonaj(stos);
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Error executing function '" + func->toString() + "': " + e.what());
                }
            }
            else
            {
                try
                {
                    stos.push(symbol->eval());
                }
                catch (const std::exception &e)
                {
                    throw std::runtime_error("Error evaluating symbol '" + symbol->toString() + "': " + e.what());
                }
            }
        }

        if (stos.size() != 1)
        {
            std::string errorMsg = "Invalid expression: ";
            errorMsg += (stos.empty() ? "no result" : "too many values on stack");
            throw std::runtime_error(errorMsg);
        }

        return stos.top();
    }

} // namespace kalkulator

int main()
{
    // Initialize constants
    kalkulator::stala::initialize();

    std::cout << "RPN Calculator\n";
    std::cout << "Commands: print <expr>, set <var> to <expr>, clear, exit\n";

    std::string line;
    while (true)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "exit")
        {
            break;
        }

        try
        {
            std::istringstream iss(line);
            std::string command;
            iss >> command;

            if (command == "print")
            {
                std::string expr;
                std::getline(iss, expr);
                auto symbols = kalkulator::parseExpression(expr);
                double result = kalkulator::evaluateRPN(symbols);
                std::cout << result << std::endl;
            }
            else if (command == "set")
            {
                std::string varName;
                std::string to;
                iss >> varName >> to;

                if (to != "to")
                {
                    std::clog << "Error: Expected 'to' after variable name" << std::endl;
                    continue;
                }

                std::string expr;
                std::getline(iss, expr);
                auto symbols = kalkulator::parseExpression(expr);
                double result = kalkulator::evaluateRPN(symbols);
                kalkulator::zmienna::set(varName, result);
                std::cout << result << std::endl;
            }
            else if (command == "clear")
            {
                kalkulator::zmienna::clearAll();
                std::cout << "All variables cleared" << std::endl;
            }
            else
            {
                std::clog << "Unknown command: " << command << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::clog << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
