#ifndef STRUMIENIE_H
#define STRUMIENIE_H

#include <fstream>
#include <string>
#include <ios>

// Forward declarations
class wejscie;
class wyjscie;

class klucz_manip
{
    int k;

public:
    klucz_manip(int key) : k(key) {}
    friend wejscie &operator>>(wejscie &in, const klucz_manip &km);
    friend wyjscie &operator<<(wyjscie &out, const klucz_manip &km);
};

klucz_manip klucz(int key);

class wejscie
{
private:
    std::ifstream file;
    int key;

    std::string deszyfruj(const std::string &s) const;

public:
    wejscie(const std::string &filename);
    ~wejscie();

    std::string czytaj();
    bool is_eof() const; // New public method
    friend wejscie &operator>>(wejscie &in, const klucz_manip &km);
};

class wyjscie
{
private:
    std::ofstream file;
    int key;

    std::string szyfruj(const std::string &s) const;

public:
    wyjscie(const std::string &filename);
    ~wyjscie();

    void pisz(const std::string &line);
    friend wyjscie &operator<<(wyjscie &out, const klucz_manip &km);
};

#endif // STRUMIENIE_H