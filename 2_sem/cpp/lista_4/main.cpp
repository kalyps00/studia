#include "wielom.hpp"
#include <iostream>
#include <stdexcept>
#include <cassert>

// Funkcja testująca konstruktor domyślny
void test_konstruktor_domyslny()
{
    std::cout << "TEST: Konstruktor domyślny" << std::endl;
    Wielom w;
    std::cout << "Wielomian domyślny: " << w << std::endl;
    assert(w[0] == 1);
    std::cout << "Konstruktor domyślny działa poprawnie." << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

// Funkcja testująca konstruktor z tablicą współczynników
void test_konstruktor_tablica()
{
    std::cout << "TEST: Konstruktor z tablicą współczynników" << std::endl;
    double wsp[] = {1, 2, 3}; // Wielomian: 3x^2 + 2x + 1
    Wielom w(2, wsp);
    std::cout << "Wielomian utworzony z tablicy: " << w << std::endl;
    assert(w[0] == 1 && w[1] == 2 && w[2] == 3);
    std::cout << "Konstruktor z tablicą działa poprawnie." << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

// Funkcja testująca konstruktor z listą inicjalizacyjną
void test_konstruktor_lista()
{
    std::cout << "TEST: Konstruktor z listą inicjalizacyjną" << std::endl;
    Wielom w = {1, 2, 3}; // Wielomian: 3x^2 + 2x + 1
    std::cout << "Wielomian utworzony z listy inicjalizacyjnej: " << w << std::endl;
    assert(w[0] == 1 && w[1] == 2 && w[2] == 3);
    std::cout << "Konstruktor z listą inicjalizacyjną działa poprawnie." << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

// Funkcja testująca operatory arytmetyczne
void test_operatory_arytmetyczne()
{
    std::cout << "TEST: Operatory arytmetyczne" << std::endl;
    Wielom w1 = {1, 2}; // 2x + 1
    Wielom w2 = {3, 4}; // 4x + 3

    std::cout << "Wielomian 1: " << w1 << std::endl;
    std::cout << "Wielomian 2: " << w2 << std::endl;

    // Dodawanie
    Wielom suma = w1 + w2;
    std::cout << "Suma: " << suma << std::endl;
    assert(suma[0] == 4 && suma[1] == 6);

    // Odejmowanie
    Wielom roznica = w1 - w2;
    std::cout << "Różnica: " << roznica << std::endl;
    assert(roznica[0] == -2 && roznica[1] == -2);

    // Mnożenie wielomianów
    Wielom iloczyn = w1 * w2;
    std::cout << "Iloczyn: " << iloczyn << std::endl;
    assert(iloczyn[0] == 3 && iloczyn[1] == 10 && iloczyn[2] == 8);

    // Mnożenie przez stałą
    Wielom skalowany = w1 * 2;
    std::cout << "Mnożenie przez stałą (2): " << skalowany << std::endl;
    assert(skalowany[0] == 2 && skalowany[1] == 4);

    std::cout << "Operatory arytmetyczne działają poprawnie." << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

// Funkcja testująca operator wywołania (schemat Hornera)
void test_operator_wywolania()
{
    std::cout << "TEST: Operator wywołania (schemat Hornera)" << std::endl;
    Wielom w = {1, 2, 3}; // 3x^2 + 2x + 1
    std::cout << "Wielomian: " << w << std::endl;
    double wynik = w(2); // Obliczamy wartość dla x = 2
    std::cout << "Wartość wielomianu dla x = 2: " << wynik << std::endl;
    assert(wynik == 17); // 3*2^2 + 2*2 + 1 = 17
    std::cout << "Operator wywołania działa poprawnie." << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

// Funkcja testująca operatory strumieniowe
void test_operatory_strumieniowe()
{
    std::cout << "TEST: Operatory strumieniowe" << std::endl;
    Wielom w;
    std::cout << "Podaj stopień i współczynniki wielomianu (np. 2 1 2 3): ";
    try
    {
        std::cin >> w;
        std::cout << "Wczytany wielomian: " << w << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
}

// Funkcja testująca operatory []
void test_operatory_indeksowania()
{
    std::cout << "TEST: Operatory indeksowania []" << std::endl;

    // Test operatora const []
    const Wielom w_const = {1, 2, 3}; // Wielomian: 3x^2 + 2x + 1
    std::cout << "Wielomian (const): " << w_const << std::endl;
    assert(w_const[0] == 1);
    assert(w_const[1] == 2);
    assert(w_const[2] == 3);
    std::cout << "Operator const [] działa poprawnie." << std::endl;

    // Test operatora []
    Wielom w = {4, 5, 6}; // Wielomian: 6x^2 + 5x + 4
    std::cout << "Wielomian przed zmianą: " << w << std::endl;
    w[0] = 7; // Zmiana współczynnika wolnego
    w[1] = 8; // Zmiana współczynnika przy x
    w[2] = 9; // Zmiana współczynnika przy x^2
    std::cout << "Wielomian po zmianie: " << w << std::endl;
    assert(w[0] == 7);
    assert(w[1] == 8);
    assert(w[2] == 9);
    std::cout << "Operator [] działa poprawnie." << std::endl;

    // Test obsługi błędów
    try
    {
        double val = w_const[3]; // Indeks poza zakresem
        (void)val;               // Uniknięcie ostrzeżenia o nieużywanej zmiennej
        assert(false);           // Nie powinno dojść do tego miejsca
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Poprawnie zgłoszono wyjątek dla indeksu poza zakresem (const): " << e.what() << std::endl;
    }

    try
    {
        w[3] = 10;     // Indeks poza zakresem
        assert(false); // Nie powinno dojść do tego miejsca
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Poprawnie zgłoszono wyjątek dla indeksu poza zakresem: " << e.what() << std::endl;
    }

    std::cout << "--------------------------------------" << std::endl;
}

// Funkcja główna
int main()
{
    try
    {
        test_konstruktor_domyslny();
        test_konstruktor_tablica();
        test_konstruktor_lista();
        test_operatory_arytmetyczne();
        test_operator_wywolania();
        test_operatory_indeksowania();
        test_operatory_strumieniowe();
        std::cout << "Wszystkie testy zakończone sukcesem!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Nieoczekiwany błąd: " << e.what() << std::endl;
    }

    return 0;
}