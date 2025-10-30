#ifndef INSTRUKCJA_HPP
#define INSTRUKCJA_HPP

#include "wyrazenie.hpp"
#include "operatory.hpp"
#include <memory>
#include <vector>
#include <initializer_list>
#include <string>
#include <iostream>

namespace obliczenia
{

    class instrukcja
    {
    public:
        virtual void wykonaj() = 0;
        virtual std::string zapis(int wciecie = 0) const = 0;

        // Prevent copying and moving
        instrukcja(const instrukcja &) = delete;
        instrukcja &operator=(const instrukcja &) = delete;
        instrukcja(instrukcja &&) = delete;
        instrukcja &operator=(instrukcja &&) = delete;

        virtual ~instrukcja() = default;

    protected:
        instrukcja() = default;
        std::string generujWciecie(int poziom) const;
    };

    class deklaracja : public instrukcja
    {
    public:
        deklaracja(const std::string &nazwa);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

        // Add method to get variable name
        const std::string &getNazwa() const { return nazwa; }

    private:
        std::string nazwa;
    };

    class przypisanie : public instrukcja
    {
    public:
        przypisanie(const std::string &nazwa, std::shared_ptr<wyrazenie> wyrazenie);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

    private:
        std::string nazwa;
        std::shared_ptr<wyrazenie> expr;
    };

    class blok : public instrukcja
    {
    public:
        blok(std::initializer_list<std::shared_ptr<instrukcja>> instrukcje);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

    private:
        std::vector<std::shared_ptr<instrukcja>> instrukcje;
        std::vector<std::string> utworzoneZmienne;
    };

    class instrukcja_warunkowa : public instrukcja
    {
    public:
        instrukcja_warunkowa(std::shared_ptr<wyrazenie> warunek, std::shared_ptr<instrukcja> blok_prawda);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

    protected:
        std::shared_ptr<wyrazenie> warunek;
        std::shared_ptr<instrukcja> blok_prawda;
    };

    class instrukcja_warunkowa_else : public instrukcja_warunkowa
    {
    public:
        instrukcja_warunkowa_else(std::shared_ptr<wyrazenie> warunek,
                                  std::shared_ptr<instrukcja> blok_prawda,
                                  std::shared_ptr<instrukcja> blok_falsz);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

    private:
        std::shared_ptr<instrukcja> blok_falsz;
    };

    class petla_dopoki : public instrukcja
    {
    public:
        petla_dopoki(std::shared_ptr<wyrazenie> warunek, std::shared_ptr<instrukcja> blok);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

    protected:
        std::shared_ptr<wyrazenie> warunek;
        std::shared_ptr<instrukcja> blok;
    };

    class petla_wykonuj_dopoki : public petla_dopoki
    {
    public:
        petla_wykonuj_dopoki(std::shared_ptr<wyrazenie> warunek, std::shared_ptr<instrukcja> blok);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;
    };

    class czytanie : public instrukcja
    {
    public:
        czytanie(const std::string &nazwa);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

    private:
        std::string nazwa;
    };

    class pisanie : public instrukcja
    {
    public:
        pisanie(std::shared_ptr<wyrazenie> wyrazenie);
        void wykonaj() override;
        std::string zapis(int wciecie = 0) const override;

    private:
        std::shared_ptr<wyrazenie> expr;
    };

} // namespace obliczenia

#endif // INSTRUKCJA_HPP