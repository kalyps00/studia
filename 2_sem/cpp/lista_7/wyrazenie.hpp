#ifndef WYRAZENIE_HPP
#define WYRAZENIE_HPP

#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <memory>

namespace obliczenia
{

    // Abstrakcyjna klasa bazowa dla wyrażeń
    class wyrazenie
    {
    public:
        virtual ~wyrazenie() = default;

        // Metoda obliczająca wartość wyrażenia
        virtual int oblicz() const = 0;

        // Metoda zwracająca zapis wyrażenia w postaci string
        virtual std::string zapis() const = 0;
    };

    // Klasa reprezentująca liczbę całkowitą
    class liczba : public wyrazenie
    {
    private:
        int wartosc;

    public:
        explicit liczba(int wartosc) : wartosc(wartosc) {}

        int oblicz() const override
        {
            return wartosc;
        }

        std::string zapis() const override
        {
            return std::to_string(wartosc);
        }
    };

    // Klasa abstrakcyjna dla stałych
    class stala : public wyrazenie
    {
    protected:
        std::string nazwa;
        int wartosc;

    public:
        stala(const std::string &nazwa, int wartosc) : nazwa(nazwa), wartosc(wartosc) {}

        int oblicz() const override
        {
            return wartosc;
        }

        std::string zapis() const override
        {
            return nazwa;
        }
    };

    // Klasy reprezentujące stałe zero i jeden
    class zero : public stala
    {
    public:
        zero() : stala("0", 0) {}
    };

    class jeden : public stala
    {
    public:
        jeden() : stala("1", 1) {}
    };

    // Klasa reprezentująca zmienną
    class zmienna : public wyrazenie
    {
    private:
        std::string nazwa;
        static std::vector<std::pair<std::string, int>> zmienne;

    public:
        explicit zmienna(const std::string &nazwa) : nazwa(nazwa) {}

        int oblicz() const override
        {
            for (const auto &zm : zmienne)
            {
                if (zm.first == nazwa)
                {
                    return zm.second;
                }
            }
            throw std::runtime_error("Zmienna nie została zdefiniowana: " + nazwa);
        }

        std::string zapis() const override
        {
            return nazwa;
        }

        static void dodajZmienna(const std::string &nazwa, int wartosc)
        {
            for (auto &zm : zmienne)
            {
                if (zm.first == nazwa)
                {
                    zm.second = wartosc;
                    return;
                }
            }
            zmienne.emplace_back(nazwa, wartosc);
        }

        static void usunZmienna(const std::string &nazwa)
        {
            zmienne.erase(std::remove_if(zmienne.begin(), zmienne.end(),
                                         [&nazwa](const auto &zm)
                                         { return zm.first == nazwa; }),
                          zmienne.end());
        }
    };

    std::vector<std::pair<std::string, int>> zmienna::zmienne;

} // namespace obliczenia

#endif // WYRAZENIE_HPP