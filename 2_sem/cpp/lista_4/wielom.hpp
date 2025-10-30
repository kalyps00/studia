#ifndef WIELOM_HPP
#define WIELOM_HPP

#include <initializer_list>
#include <iostream>
#include <stdexcept>

class Wielom
{
private:
    int stopien;
    double *wspolczynniki;

public:
    Wielom();
    Wielom(int st, const double wsp[]);
    Wielom(std::initializer_list<double> wsp);
    Wielom(const Wielom &w);
    Wielom(Wielom &&w);
    ~Wielom();

    Wielom &operator=(const Wielom &w);
    Wielom &operator=(Wielom &&w);

    double operator[](int i) const;
    double &operator[](int i);
    double operator()(double x) const;

    // Operatory arytmetyczne
    friend Wielom operator+(const Wielom &u, const Wielom &v);
    friend Wielom operator-(const Wielom &u, const Wielom &v);
    friend Wielom operator*(const Wielom &u, const Wielom &v);
    friend Wielom operator*(const Wielom &u, double c);

    // Operatory przypisania połączone z arytmetycznymi
    Wielom &operator+=(const Wielom &v);
    Wielom &operator-=(const Wielom &v);
    Wielom &operator*=(const Wielom &v);
    Wielom &operator*=(double c);

    // Operatory strumieniowe
    friend std::istream &operator>>(std::istream &we, Wielom &w);
    friend std::ostream &operator<<(std::ostream &wy, const Wielom &w);
};

#endif