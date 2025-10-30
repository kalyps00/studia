#include "strumienie.h"
#include <cctype>
#include <stdexcept>

// Manipulator
klucz_manip klucz(int key)
{
    return klucz_manip(key);
}

// Implementacja wejscie
wejscie::wejscie(const std::string &filename) : key(0)
{
    file.open(filename);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Nie można otworzyć pliku: " + filename);
    }
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
}

wejscie::~wejscie()
{
    if (file.is_open())
    {
        file.close();
    }
}

std::string wejscie::deszyfruj(const std::string &s) const
{
    std::string result = s;
    int normalized_key = (key % 26 + 26) % 26; // Normalizacja klucza

    for (char &c : result)
    {
        if (std::isupper(c))
        {
            c = 'A' + (c - 'A' - normalized_key + 26) % 26;
        }
        else if (std::islower(c))
        {
            c = 'a' + (c - 'a' - normalized_key + 26) % 26;
        }
    }
    return result;
}

std::string wejscie::czytaj()
{
    std::string line;
    std::getline(file, line);
    if (key != 0)
    {
        line = deszyfruj(line);
    }
    return line;
}

bool wejscie::is_eof() const
{
    return file.eof();
}

wejscie &operator>>(wejscie &in, const klucz_manip &km)
{
    in.key = km.k;
    return in;
}

// Implementacja wyjscie
wyjscie::wyjscie(const std::string &filename) : key(0)
{
    file.open(filename);
    if (!file.is_open())
    {
        throw std::ios_base::failure("Nie można otworzyć pliku: " + filename);
    }
    file.exceptions(std::ofstream::badbit | std::ofstream::failbit);
}

wyjscie::~wyjscie()
{
    if (file.is_open())
    {
        file.close();
    }
}

std::string wyjscie::szyfruj(const std::string &s) const
{
    std::string result = s;
    int normalized_key = (key % 26 + 26) % 26; // Normalizacja klucza

    for (char &c : result)
    {
        if (std::isupper(c))
        {
            c = 'A' + (c - 'A' + normalized_key) % 26;
        }
        else if (std::islower(c))
        {
            c = 'a' + (c - 'a' + normalized_key) % 26;
        }
    }
    return result;
}

void wyjscie::pisz(const std::string &line)
{
    std::string output = line;
    if (key != 0)
    {
        output = szyfruj(output);
    }
    file << output << '\n';
}

wyjscie &operator<<(wyjscie &out, const klucz_manip &km)
{
    out.key = km.k;
    return out;
}