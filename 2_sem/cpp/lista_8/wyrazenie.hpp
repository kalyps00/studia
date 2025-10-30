#ifndef WYRAZENIE_HPP
#define WYRAZENIE_HPP

#include <string>
#include <vector>
#include <utility>
#include <stdexcept>

namespace obliczenia
{

    class wyrazenie
    {
    public:
        virtual int oblicz() const = 0;
        virtual std::string zapis() const = 0;

        // Prevent copying and moving
        wyrazenie(const wyrazenie &) = delete;
        wyrazenie &operator=(const wyrazenie &) = delete;
        wyrazenie(wyrazenie &&) = delete;
        wyrazenie &operator=(wyrazenie &&) = delete;

        virtual ~wyrazenie() = default;

    protected:
        wyrazenie() = default;
    };

    class zmienna : public wyrazenie
    {
    public:
        zmienna(const std::string &nazwa);
        int oblicz() const override;
        std::string zapis() const override;

        static void dodaj(const std::string &nazwa, int wartosc = 0);
        static void usun(const std::string &nazwa);
        static void zmien(const std::string &nazwa, int wartosc);
        static int znajdz(const std::string &nazwa);
        static bool istnieje(const std::string &nazwa);

    private:
        std::string nazwa;
        static std::vector<std::pair<std::string, int>> zmienne;
    };

    class liczba : public wyrazenie
    {
    public:
        liczba(int wartosc);
        int oblicz() const override;
        std::string zapis() const override;

    private:
        int wartosc;
    };

} // namespace obliczenia

#endif // WYRAZENIE_HPP