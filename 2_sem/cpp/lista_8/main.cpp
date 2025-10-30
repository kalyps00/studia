#include "wyrazenie.hpp"
#include "operatory.hpp"
#include "instrukcja.hpp"
#include <iostream>
#include <memory>

using namespace std;

void test_wyrazenia()
{
    using namespace obliczenia;
    // Or individual using declarations:
    // using obliczenia::minus;
    // using obliczenia::abs;
    // using obliczenia::odejmowanie;
    // using obliczenia::zmienna;

    cout << "\n=== TEST WYRAŻEŃ ===\n"
         << endl;

    // Inicjalizacja zmiennych
    zmienna::dodaj("x", 5);
    zmienna::dodaj("y", 3);
    zmienna::dodaj("z", 10);

    // Test 1: 2 ^ (x / 3 - 1)
    shared_ptr<wyrazenie> test1 = make_shared<potega>(
        make_shared<liczba>(2),
        make_shared<odejmowanie>(
            make_shared<dzielenie>(
                make_shared<zmienna>("x"),
                make_shared<liczba>(3)),
            make_shared<liczba>(1)));

    cout << "Wyrażenie 1: " << test1->zapis() << endl;
    cout << "Wynik: " << test1->oblicz() << endl; // Powinno być 2^(5/3-1) = 2^(1-1) = 2^0 = 1

    // Test 2: (x + y) * (z - x)
    shared_ptr<wyrazenie> test2 = make_shared<mnozenie>(
        make_shared<dodawanie>(
            make_shared<zmienna>("x"),
            make_shared<zmienna>("y")),
        make_shared<odejmowanie>(
            make_shared<zmienna>("z"),
            make_shared<zmienna>("x")));

    cout << "\nWyrażenie 2: " << test2->zapis() << endl;
    cout << "Wynik: " << test2->oblicz() << endl; // Powinno być (5+3)*(10-5) = 8*5 = 40

    // Test 3: x > y && z % y == 1
    shared_ptr<wyrazenie> test3 = make_shared<mnozenie>( // Używamy mnożenia jako logiczny AND
        make_shared<wieksze>(
            make_shared<zmienna>("x"),
            make_shared<zmienna>("y")),
        make_shared<rowne>(
            make_shared<modulo>(
                make_shared<zmienna>("z"),
                make_shared<zmienna>("y")),
            make_shared<liczba>(1)));

    cout << "\nWyrażenie 3: " << test3->zapis() << endl;
    cout << "Wynik: " << test3->oblicz() << endl; // Powinno być (5>3)*(10%3==1) = 1*1 = 1

    // Test 4: -x + abs(y - z) + sgn(x - z)
    shared_ptr<wyrazenie> test4 = make_shared<dodawanie>(
        make_shared<dodawanie>(
            make_shared<obliczenia::minus>(make_shared<obliczenia::zmienna>("x")),
            make_shared<obliczenia::abs>(make_shared<obliczenia::odejmowanie>(
                make_shared<zmienna>("y"),
                make_shared<zmienna>("z")))),
        make_shared<sgn>(make_shared<odejmowanie>(
            make_shared<zmienna>("x"),
            make_shared<zmienna>("z"))));

    cout << "\nWyrażenie 4: " << test4->zapis() << endl;
    cout << "Wynik: " << test4->oblicz() << endl; // Powinno być -5 + abs(3-10) + sgn(5-10) = -5 + 7 + (-1) = 1

    // Test 5: 2 ^ 2 ^ 3 (potęgowanie jest prawostronnie łączne)
    shared_ptr<wyrazenie> test5 = make_shared<potega>(
        make_shared<liczba>(2),
        make_shared<potega>(
            make_shared<liczba>(2),
            make_shared<liczba>(3)));

    cout << "\nWyrażenie 5: " << test5->zapis() << endl;
    cout << "Wynik: " << test5->oblicz() << endl; // Powinno być 2^(2^3) = 2^8 = 256

    // Test 6: min(x*y, z/2)
    shared_ptr<wyrazenie> test6 = make_shared<minimum>(
        make_shared<mnozenie>(
            make_shared<zmienna>("x"),
            make_shared<zmienna>("y")),
        make_shared<dzielenie>(
            make_shared<zmienna>("z"),
            make_shared<liczba>(2)));

    cout << "\nWyrażenie 6: " << test6->zapis() << endl;
    cout << "Wynik: " << test6->oblicz() << endl; // Powinno być min(5*3, 10/2) = min(15, 5) = 5

    // Zmiana wartości zmiennych
    zmienna::zmien("x", 8);
    zmienna::zmien("y", 4);

    cout << "\nPo zmianie wartości zmiennych (x=8, y=4):" << endl;
    cout << "Wyrażenie 2: " << test2->zapis() << endl;
    cout << "Nowy wynik: " << test2->oblicz() << endl; // Powinno być (8+4)*(10-8) = 12*2 = 24
}

void test_instrukcje()
{
    cout << "\n=== TEST INSTRUKCJI ===\n"
         << endl;

    // Test różnych typów instrukcji
    cout << "Prosty test deklaracji i przypisania:" << endl;

    auto deklaracja_a = make_shared<deklaracja>("a");
    auto przypisanie_a = make_shared<przypisanie>("a", make_shared<liczba>(10));

    cout << deklaracja_a->zapis() << endl;
    deklaracja_a->wykonaj();

    cout << przypisanie_a->zapis() << endl;
    przypisanie_a->wykonaj();

    cout << "Wartość a po przypisaniu: " << zmienna::znajdz("a") << endl;

    // Test pętli
    cout << "\nTest pętli while:" << endl;

    auto deklaracja_i = make_shared<deklaracja>("i");
    auto przypisanie_i = make_shared<przypisanie>("i", make_shared<liczba>(1));

    auto warunek_petli = make_shared<mniejszeRowne>(
        make_shared<zmienna>("i"),
        make_shared<liczba>(5));

    auto blok_petli = make_shared<blok>(initializer_list<shared_ptr<instrukcja>>{
        make_shared<pisanie>(make_shared<zmienna>("i")),
        make_shared<przypisanie>("i", make_shared<dodawanie>(
                                          make_shared<zmienna>("i"),
                                          make_shared<liczba>(1)))});

    auto petla = make_shared<petla_dopoki>(warunek_petli, blok_petli);

    cout << deklaracja_i->zapis() << endl;
    deklaracja_i->wykonaj();

    cout << przypisanie_i->zapis() << endl;
    przypisanie_i->wykonaj();

    cout << petla->zapis() << endl;
    cout << "Wykonanie pętli:" << endl;
    petla->wykonaj();

    // Test programu sprawdzającego pierwszość
    cout << "\nProgram sprawdzający pierwszość liczby:" << endl;

    // Tworzymy program zgodnie z przykładem z zadania
    auto program_pierwszosc = make_shared<blok>(initializer_list<shared_ptr<instrukcja>>{
        make_shared<deklaracja>("n"),
        make_shared<czytanie>("n"),
        make_shared<instrukcja_warunkowa_else>(
            make_shared<mniejsze>(
                make_shared<zmienna>("n"),
                make_shared<liczba>(2)),
            make_shared<pisanie>(make_shared<liczba>(0)), // nie jest liczbą pierwszą
            make_shared<blok>(initializer_list<shared_ptr<instrukcja>>{
                make_shared<deklaracja>("p"),
                make_shared<przypisanie>("p", make_shared<liczba>(2)),
                make_shared<deklaracja>("wyn"),
                make_shared<petla_dopoki>(
                    make_shared<mniejszeRowne>(
                        make_shared<mnozenie>(
                            make_shared<zmienna>("p"),
                            make_shared<zmienna>("p")),
                        make_shared<zmienna>("n")),
                    make_shared<blok>(initializer_list<shared_ptr<instrukcja>>{
                        make_shared<instrukcja_warunkowa>(
                            make_shared<rowne>(
                                make_shared<modulo>(
                                    make_shared<zmienna>("n"),
                                    make_shared<zmienna>("p")),
                                make_shared<liczba>(0)),
                            make_shared<blok>(initializer_list<shared_ptr<instrukcja>>{
                                make_shared<przypisanie>("wyn", make_shared<zmienna>("p")),
                                make_shared<przypisanie>("p", make_shared<zmienna>("n"))})),
                        make_shared<przypisanie>("p", make_shared<dodawanie>(
                                                          make_shared<zmienna>("p"),
                                                          make_shared<liczba>(1)))})),
                make_shared<instrukcja_warunkowa_else>(
                    make_shared<wieksze>(
                        make_shared<zmienna>("wyn"),
                        make_shared<liczba>(0)),
                    make_shared<pisanie>(make_shared<liczba>(0)), // nie jest liczbą pierwszą
                    make_shared<pisanie>(make_shared<liczba>(1))  // jest liczbą pierwszą
                    )}))});

    cout << "Kod programu sprawdzającego pierwszość:" << endl;
    cout << program_pierwszosc->zapis() << endl;

    cout << "\nWykonanie programu dla różnych wartości:" << endl;
    cout << "Uwaga: Program poprosi o wprowadzenie wartości dla zmiennej n." << endl;
    cout << "Przetestuj różne wartości, np. 1 (nie jest pierwsza), 7 (jest pierwsza), 15 (nie jest pierwsza)." << endl;

    program_pierwszosc->wykonaj();
}

int main()
{
    try
    {
        test_wyrazenia();
        test_instrukcje();

        // Sprzątanie - usuwamy wszystkie zmienne
        vector<string> zmienne_do_usuniecia;
        for (const auto &zm : {"x", "y", "z", "a", "i", "n", "p", "wyn"})
        {
            if (zmienna::istnieje(zm))
            {
                zmienne_do_usuniecia.push_back(zm);
            }
        }

        for (const auto &zm : zmienne_do_usuniecia)
        {
            zmienna::usun(zm);
        }
    }
    catch (const exception &e)
    {
        cerr << "Błąd: " << e.what() << endl;
        return 1;
    }

    return 0;
}