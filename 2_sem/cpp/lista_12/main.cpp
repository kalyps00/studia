#include "strumienie.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Użycie: " << argv[0] << " <plik_we> <plik_wy> <klucz>" << std::endl;
        return 1;
    }

    std::string plik_we = argv[1];
    std::string plik_wy = argv[2];
    int klucz_param = std::atoi(argv[3]);

    try
    {
        wejscie in(plik_we);
        wyjscie out(plik_wy);

        if (klucz_param >= 0)
        {
            // Szyfrowanie: ustaw klucz na wyjściu
            out << klucz(klucz_param);
        }
        else
        {
            // Deszyfrowanie: ustaw klucz na wejściu
            in >> klucz(-klucz_param);
        }

        while (true)
        {
            try
            {
                std::string line = in.czytaj();
                // Sprawdzenie EOF po próbie odczytu
                if (in.is_eof() && line.empty())
                {
                    break; // Koniec pliku i linia jest pusta
                }
                out.pisz(line);
            }
            catch (const std::ios_base::failure &e)
            {
                // Sprawdzenie EOF w bloku catch, jeśli odczyt rzucił wyjątek
                if (in.is_eof())
                {
                    break; // Koniec pliku
                }
                else
                {
                    throw; // Inny błąd
                }
            }
        }
    }
    catch (const std::ios_base::failure &e)
    {
        std::cerr << "Błąd strumienia: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}