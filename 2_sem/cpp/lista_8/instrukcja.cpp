#include "instrukcja.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace obliczenia
{

    // Helper method for generating indentation
    std::string instrukcja::generujWciecie(int poziom) const
    {
        return std::string(poziom * 2, ' ');
    }

    // DEKLARACJA class implementation
    deklaracja::deklaracja(const std::string &nazwa) : nazwa(nazwa)
    {
        if (nazwa.empty())
        {
            throw std::invalid_argument("Nazwa zmiennej nie może być pusta");
        }
        if (zmienna::istnieje(nazwa))
        {
            throw std::logic_error("Zmienna o nazwie '" + nazwa + "' już istnieje");
        }
    }

    void deklaracja::wykonaj()
    {
        zmienna::dodaj(nazwa, 0);
    }

    std::string deklaracja::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + "var " + nazwa + ";";
    }

    // PRZYPISANIE class implementation
    przypisanie::przypisanie(const std::string &nazwa, std::shared_ptr<wyrazenie> wyrazenie)
        : nazwa(nazwa), expr(wyrazenie)
    {
        if (nazwa.empty())
        {
            throw std::invalid_argument("Nazwa zmiennej nie może być pusta");
        }
        if (!wyrazenie)
        {
            throw std::invalid_argument("Wyrażenie nie może być nullptr");
        }
    }

    void przypisanie::wykonaj()
    {
        if (!zmienna::istnieje(nazwa))
        {
            throw std::logic_error("Zmienna o nazwie '" + nazwa + "' nie istnieje");
        }
        zmienna::zmien(nazwa, expr->oblicz());
    }

    std::string przypisanie::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + nazwa + " = " + expr->zapis() + ";";
    }

    // BLOK class implementation
    blok::blok(std::initializer_list<std::shared_ptr<instrukcja>> instrukcje)
        : instrukcje(instrukcje)
    {
        for (const auto &instr : instrukcje)
        {
            if (!instr)
            {
                throw std::invalid_argument("Instrukcja w bloku nie może być nullptr");
            }
        }
    }

    void blok::wykonaj()
    {
        utworzoneZmienne.clear(); // Reset the list of created variables

        // Execute all instructions in the block
        for (const auto &instr : instrukcje)
        {
            // Check if the instruction is a variable declaration
            auto *decl = dynamic_cast<deklaracja *>(instr.get());
            if (decl)
            {
                // Use a direct way to get variable name instead of parsing the string
                // from zapis() which is error-prone
                const deklaracja *d = static_cast<const deklaracja *>(decl);
                auto nazwaZmiennej = d->getNazwa(); // Add this method to deklaracja class
                utworzoneZmienne.push_back(nazwaZmiennej);
            }

            instr->wykonaj();
        }

        // Clean up variables created in this block when execution is complete
        for (const auto &nazwa : utworzoneZmienne)
        {
            if (zmienna::istnieje(nazwa))
            {
                zmienna::usun(nazwa);
            }
        }
    }

    std::string blok::zapis(int wciecie) const
    {
        std::string result = generujWciecie(wciecie) + "{\n";

        for (const auto &instr : instrukcje)
        {
            result += instr->zapis(wciecie + 1) + "\n";
        }

        result += generujWciecie(wciecie) + "}";
        return result;
    }

    // INSTRUKCJA_WARUNKOWA class implementation
    instrukcja_warunkowa::instrukcja_warunkowa(std::shared_ptr<wyrazenie> warunek, std::shared_ptr<instrukcja> blok_prawda)
        : warunek(warunek), blok_prawda(blok_prawda)
    {
        if (!warunek || !blok_prawda)
        {
            throw std::invalid_argument("Warunek lub blok nie może być nullptr");
        }
    }

    void instrukcja_warunkowa::wykonaj()
    {
        if (warunek->oblicz() != 0)
        {
            blok_prawda->wykonaj();
        }
    }

    std::string instrukcja_warunkowa::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + "if (" + warunek->zapis() + ") " + blok_prawda->zapis(0);
    }

    // INSTRUKCJA_WARUNKOWA_ELSE class implementation
    instrukcja_warunkowa_else::instrukcja_warunkowa_else(
        std::shared_ptr<wyrazenie> warunek,
        std::shared_ptr<instrukcja> blok_prawda,
        std::shared_ptr<instrukcja> blok_falsz)
        : instrukcja_warunkowa(warunek, blok_prawda), blok_falsz(blok_falsz)
    {
        if (!blok_falsz)
        {
            throw std::invalid_argument("Blok else nie może być nullptr");
        }
    }

    void instrukcja_warunkowa_else::wykonaj()
    {
        if (warunek->oblicz() != 0)
        {
            blok_prawda->wykonaj();
        }
        else
        {
            blok_falsz->wykonaj();
        }
    }

    std::string instrukcja_warunkowa_else::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + "if (" + warunek->zapis() + ") " +
               blok_prawda->zapis(0) + "\n" + generujWciecie(wciecie) + "else " +
               blok_falsz->zapis(0);
    }

    // PETLA_DOPOKI class implementation
    petla_dopoki::petla_dopoki(std::shared_ptr<wyrazenie> warunek, std::shared_ptr<instrukcja> blok)
        : warunek(warunek), blok(blok)
    {
        if (!warunek || !blok)
        {
            throw std::invalid_argument("Warunek lub blok nie może być nullptr");
        }
    }

    void petla_dopoki::wykonaj()
    {
        while (warunek->oblicz() != 0)
        {
            blok->wykonaj();
        }
    }

    std::string petla_dopoki::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + "while (" + warunek->zapis() + ") " + blok->zapis(0);
    }

    // PETLA_WYKONUJ_DOPOKI class implementation
    petla_wykonuj_dopoki::petla_wykonuj_dopoki(std::shared_ptr<wyrazenie> warunek, std::shared_ptr<instrukcja> blok)
        : petla_dopoki(warunek, blok) {}

    void petla_wykonuj_dopoki::wykonaj()
    {
        do
        {
            blok->wykonaj();
        } while (warunek->oblicz() != 0);
    }

    std::string petla_wykonuj_dopoki::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + "do " + blok->zapis(0) + "\n" +
               generujWciecie(wciecie) + "while (" + warunek->zapis() + ");";
    }

    // CZYTANIE class implementation
    czytanie::czytanie(const std::string &nazwa) : nazwa(nazwa)
    {
        if (nazwa.empty())
        {
            throw std::invalid_argument("Nazwa zmiennej nie może być pusta");
        }
    }

    void czytanie::wykonaj()
    {
        if (!zmienna::istnieje(nazwa))
        {
            throw std::logic_error("Zmienna o nazwie '" + nazwa + "' nie istnieje");
        }

        int wartosc;
        std::cout << "Podaj wartość dla zmiennej " << nazwa << ": ";
        std::cin >> wartosc;
        zmienna::zmien(nazwa, wartosc);
    }

    std::string czytanie::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + "read " + nazwa + ";";
    }

    // PISANIE class implementation
    pisanie::pisanie(std::shared_ptr<wyrazenie> wyrazenie) : expr(wyrazenie)
    {
        if (!wyrazenie)
        {
            throw std::invalid_argument("Wyrażenie nie może być nullptr");
        }
    }

    void pisanie::wykonaj()
    {
        std::cout << expr->oblicz() << std::endl;
    }

    std::string pisanie::zapis(int wciecie) const
    {
        return generujWciecie(wciecie) + "write " + expr->zapis() + ";";
    }

} // namespace obliczenia