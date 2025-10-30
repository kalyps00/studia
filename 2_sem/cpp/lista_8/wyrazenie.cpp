#include "wyrazenie.hpp"
#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace obliczenia
{

    // Initialize static variable for storing variables
    std::vector<std::pair<std::string, int>> zmienna::zmienne;

    // ZMIENNA class implementation
    zmienna::zmienna(const std::string &nazwa) : nazwa(nazwa)
    {
        if (!istnieje(nazwa))
        {
            throw std::logic_error("Zmienna o nazwie '" + nazwa + "' nie istnieje");
        }
    }

    int zmienna::oblicz() const
    {
        return znajdz(nazwa);
    }

    std::string zmienna::zapis() const
    {
        return nazwa;
    }

    void zmienna::dodaj(const std::string &nazwa, int wartosc)
    {
        if (istnieje(nazwa))
        {
            throw std::logic_error("Zmienna o nazwie '" + nazwa + "' już istnieje");
        }
        zmienne.push_back({nazwa, wartosc});
    }

    void zmienna::usun(const std::string &nazwa)
    {
        auto it = std::find_if(zmienne.begin(), zmienne.end(),
                               [&nazwa](const auto &p)
                               { return p.first == nazwa; });
        if (it == zmienne.end())
        {
            throw std::logic_error("Nie można usunąć nieistniejącej zmiennej '" + nazwa + "'");
        }
        zmienne.erase(it);
    }

    void zmienna::zmien(const std::string &nazwa, int wartosc)
    {
        auto it = std::find_if(zmienne.begin(), zmienne.end(),
                               [&nazwa](const auto &p)
                               { return p.first == nazwa; });
        if (it == zmienne.end())
        {
            throw std::logic_error("Nie można zmienić wartości nieistniejącej zmiennej '" + nazwa + "'");
        }
        it->second = wartosc;
    }

    int zmienna::znajdz(const std::string &nazwa)
    {
        auto it = std::find_if(zmienne.begin(), zmienne.end(),
                               [&nazwa](const auto &p)
                               { return p.first == nazwa; });
        if (it == zmienne.end())
        {
            throw std::logic_error("Zmienna o nazwie '" + nazwa + "' nie istnieje");
        }
        return it->second;
    }

    bool zmienna::istnieje(const std::string &nazwa)
    {
        auto it = std::find_if(zmienne.begin(), zmienne.end(),
                               [&nazwa](const auto &p)
                               { return p.first == nazwa; });
        return it != zmienne.end();
    }

    // LICZBA class implementation
    liczba::liczba(int wartosc) : wartosc(wartosc) {}

    int liczba::oblicz() const
    {
        return wartosc;
    }

    std::string liczba::zapis() const
    {
        return std::to_string(wartosc);
    }

} // namespace obliczenia