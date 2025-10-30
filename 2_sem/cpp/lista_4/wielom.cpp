#include "wielom.hpp"
#include <stdexcept>
#include <algorithm>
Wielom::Wielom() : stopien(0)
{
    wspolczynniki = new double[stopien + 1];
    wspolczynniki[0] = 1;
};
Wielom::Wielom(int st, const double wsp[]) : stopien(st)
{
    if (stopien < 0)
        throw std::invalid_argument("Stopień wielomianu nie może być ujemny");
    wspolczynniki = new double[stopien + 1];
    if (stopien > 0 && wsp[stopien] == 0)
    {
        delete[] wspolczynniki;
        throw std::invalid_argument("Wielomian nie jest poprawnie określony - współczynnik przy najwyższej potędze musi być różny od zera");
    }
    for (int i = 0; i <= stopien; i++)
    {
        wspolczynniki[i] = wsp[i];
    }
};
Wielom::Wielom(std::initializer_list<double> wsp) : stopien(wsp.size() - 1)
{
    if (stopien < 0)
        throw std::invalid_argument("Stopień wielomianu nie może być ujemny");

    wspolczynniki = new double[stopien + 1];

    int i = 0;
    for (auto it = wsp.begin(); it != wsp.end(); ++it)
    {
        wspolczynniki[i++] = *it;
    }

    if (wspolczynniki[stopien] == 0 && stopien != 0)
    {
        delete[] wspolczynniki;
        throw std::invalid_argument("Współczynnik wiodący musi być różny od zera");
    }
}
Wielom::Wielom(const Wielom &w) : stopien(w.stopien)
{
    wspolczynniki = new double[stopien + 1];
    for (int i = 0; i <= stopien; i++)
    {
        wspolczynniki[i] = w.wspolczynniki[i];
    }
};
Wielom::Wielom(Wielom &&w)
{
    this->stopien = w.stopien;
    wspolczynniki = w.wspolczynniki;
    w.wspolczynniki = nullptr;
    w.stopien = 0;
};
Wielom::~Wielom()
{
    delete[] wspolczynniki;
};
Wielom &Wielom::operator=(const Wielom &w)
{
    if (this == &w)
        return *this;
    delete[] wspolczynniki;
    this->stopien = w.stopien;
    wspolczynniki = new double[stopien + 1];
    for (int i = 0; i <= stopien; i++)
    {
        wspolczynniki[i] = w.wspolczynniki[i];
    }
    return *this;
};
Wielom &Wielom::operator=(Wielom &&w)
{
    if (this == &w)
        return *this;
    delete[] wspolczynniki;
    this->stopien = w.stopien;
    wspolczynniki = w.wspolczynniki;
    w.wspolczynniki = nullptr;
    return *this;
};
double Wielom::operator[](int i) const
{
    if (i < 0 || i > stopien)
        throw std::out_of_range("nieprawidłowy indeks");
    return wspolczynniki[i];
};
double &Wielom::operator[](int i)
{
    if (i < 0 || i > stopien)
        throw std::out_of_range("nieprawidłowy indeks");
    if (i == stopien && wspolczynniki[i] == 0 && stopien != 0)
        throw std::invalid_argument("Wspolczynnik wiodacy musi byc rozny od zera");
    return wspolczynniki[i];
};
double Wielom::operator()(double x) const
{
    if (stopien == 0)
    {
        return wspolczynniki[0];
    }
    double wynik = wspolczynniki[stopien];
    for (int i = stopien - 1; i >= 0; --i)
    {
        wynik = wynik * x + wspolczynniki[i];
    }
    return wynik;
};
Wielom operator+(const Wielom &u, const Wielom &v)
{
    int max_st = std::max(u.stopien, v.stopien);
    double *wsp = new double[max_st + 1]();
    for (int i = 0; i <= v.stopien; i++)
        wsp[i] += v[i];
    for (int i = 0; i <= u.stopien; i++)
        wsp[i] += u[i];
    while (max_st > 0 && wsp[max_st] == 0)
        max_st--;
    Wielom wynik = Wielom(max_st, wsp);
    delete[] wsp;
    return wynik;
};
Wielom operator-(const Wielom &u, const Wielom &v)
{
    int max_st = std::max(u.stopien, v.stopien);
    double *wsp = new double[max_st + 1]();
    for (int i = 0; i <= u.stopien; i++)
        wsp[i] = u[i];

    for (int i = 0; i <= v.stopien; i++)
        wsp[i] -= v[i];

    while (max_st > 0 && wsp[max_st] == 0)
        max_st--;
    Wielom wynik = Wielom(max_st, wsp);
    delete[] wsp;
    return wynik;
}

Wielom operator*(const Wielom &u, const Wielom &v)
{
    int max_st = u.stopien + v.stopien;
    double *wsp = new double[max_st + 1]();
    for (int i = 0; i <= u.stopien; i++)
    {
        for (int j = 0; j <= v.stopien; j++)
        {
            wsp[i + j] += u[i] * v[j];
        }
    }
    while (max_st > 0 && wsp[max_st] == 0)
        max_st--;
    Wielom wynik = Wielom(max_st, wsp);
    delete[] wsp;
    return wynik;
}
Wielom operator*(const Wielom &u, double c)
{
    int max_st = u.stopien;
    double *wsp = new double[max_st + 1]();
    for (int i = 0; i <= u.stopien; i++)
    {
        wsp[i] = u[i] * c;
    }
    while (max_st > 0 && wsp[max_st] == 0)
        max_st--;
    Wielom wynik = Wielom(max_st, wsp);
    delete[] wsp;
    return wynik;
};
Wielom &Wielom::operator+=(const Wielom &v)
{
    *this = *this + v;
    return *this;
}
Wielom &Wielom::operator-=(const Wielom &v)
{
    *this = *this - v;
    return *this;
}
Wielom &Wielom::operator*=(double c)
{
    *this = *this * c;
    return *this;
}
Wielom &Wielom::operator*=(const Wielom &v)
{
    *this = *this * v;
    return *this;
}
std::istream &operator>>(std::istream &we, Wielom &w)
{
    int st;
    we >> st;
    if (st < 0)
        throw std::invalid_argument("Stopień wielomianu nie może być ujemny");
    double *wsp = new double[st + 1];
    for (int i = 0; i <= st; i++)
    {
        we >> wsp[i];
    }
    w = Wielom(st, wsp);
    delete[] wsp;
    return we;
}
std::ostream &operator<<(std::ostream &wy, const Wielom &w)
{
    for (int i = w.stopien; i >= 0; i--)
    {
        if (i == 0)
            wy << w[i];
        else
            wy << w[i] << "x^" << i << " + ";
    }
    return wy;
}