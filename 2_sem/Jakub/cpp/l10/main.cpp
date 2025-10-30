#include "wymierna.hpp"
#include <iostream>
#include <sstream>
#include <climits>


void test(bool condition, const std::string& message, int& testNumber) {
    std::cout << "Test " << testNumber++ << ": ";
    if (condition) {
        std::cout << "[OK] " << message << std::endl;
    } else {
        std::cout << "[False] " << message << std::endl;
    }
}


bool compareStream(const obliczenia::wymierna& w, const std::string& expected) {
    std::stringstream ss;
    ss << w;
    return (ss.str() == expected);
}

int main() {
    int testNumber = 1;
    try {
        // Test 1: Konstruktor domyslny (0/1)
        obliczenia::wymierna w1;
        test(w1.getLicznik() == 0 && w1.getMianownik() == 1, "Konstruktor domyslny", testNumber);

        // Test 2: Konstruktor z int (5/1)
        obliczenia::wymierna w2(5);
        test(w2.getLicznik() == 5 && w2.getMianownik() == 1, "Konstruktor z int", testNumber);

        // Test 3: Konstruktor z licznikiem i mianownikiem (uproszczenie 2/4)
        obliczenia::wymierna w3(2, 4);
        test(w3.getLicznik() == 1 && w3.getMianownik() == 2, "Upraszczanie ulamka", testNumber);

        // Test 4: Ujemny licznik (-3/7)
        obliczenia::wymierna w4(-3, 7);
        test(w4.getLicznik() == -3 && w4.getMianownik() == 7, "Ujemny licznik", testNumber);

        // Test 5: Ujemny mianownik (6/-9 -> -2/3)
        obliczenia::wymierna w5(6, -9);
        test(w5.getLicznik() == -2 && w5.getMianownik() == 3, "Ujemny mianownik", testNumber);

        // Test 6: Operator + (1/2 + (-2/3) = -1/6)
        obliczenia::wymierna sum = w3 + w5;
        test(sum.getLicznik() == -1 && sum.getMianownik() == 6, "Dodawanie", testNumber);

        // Test 7: Operator - (5 - 1/2 = 9/2)
        obliczenia::wymierna diff = w2 - w3;
        test(diff.getLicznik() == 9 && diff.getMianownik() == 2, "Odejmowanie", testNumber);

        // Test 8: Operator * (-3/7 * -2/3 = 2/7)
        obliczenia::wymierna prod = w4 * w5;
        test(prod.getLicznik() == 2 && prod.getMianownik() == 7, "Mnozenie", testNumber);

        // Test 9: Operator / (-2/3 / -3/7 = 14/9)
        obliczenia::wymierna quot = w5 / w4;
        test(quot.getLicznik() == 14 && quot.getMianownik() == 9, "Dzielenie", testNumber);

        // Test 10: Operator += (5 += 1/2 = 11/2)
        obliczenia::wymierna w6(5);
        w6 += w3;
        test(w6.getLicznik() == 11 && w6.getMianownik() == 2, "Operator +=", testNumber);

        // Test 11: Operator -= (5 -= 1/2 = 9/2)
        obliczenia::wymierna w7(5);
        w7 -= w3;
        test(w7.getLicznik() == 9 && w7.getMianownik() == 2, "Operator -=", testNumber);

        // Test 12: Operator *= (5 *= 1/2 = 5/2)
        obliczenia::wymierna w8(5);
        w8 *= w3;
        test(w8.getLicznik() == 5 && w8.getMianownik() == 2, "Operator *=", testNumber);

        // Test 13: Operator /= (5 /= 1/2 = 10/1)
        obliczenia::wymierna w9(5);
        w9 /= w3;
        test(w9.getLicznik() == 10 && w9.getMianownik() == 1, "Operator /=", testNumber);

        // Test 14: Operator - (negacja 1/2 -> -1/2)
        obliczenia::wymierna neg = -w3;
        test(neg.getLicznik() == -1 && neg.getMianownik() == 2, "Negacja", testNumber);

        // Test 15: Operator ! (odwrotnosc 1/2 -> 2/1)
        obliczenia::wymierna recip = !w3;
        test(recip.getLicznik() == 2 && recip.getMianownik() == 1, "Odwrotnosc", testNumber);

        // Test 16: Wyjatek przy konstruktorze (1/0)
        bool exceptionThrown = false;
        try {
            obliczenia::wymierna w10(1, 0);
        } catch (const obliczenia::dzielenie_przez_0& e) {
            exceptionThrown = true;
        }
        test(exceptionThrown, "Wyjatek: dzielenie przez zero w konstruktorze", testNumber);

        // Test 17: Wyjatek przy odwrotnosci zera
        exceptionThrown = false;
        try {
            obliczenia::wymierna zero(0, 1);
            obliczenia::wymierna inv = !zero;
        } catch (const obliczenia::dzielenie_przez_0& e) {
            exceptionThrown = true;
        }
        test(exceptionThrown, "Wyjatek: odwrotnosc zera", testNumber);

        // Test 18: Konwersja na double (1/2 -> 0.5)
        double d = static_cast<double>(w3);
        test(std::abs(d - 0.5) < 1e-9, "Konwersja na double", testNumber);

        // Test 19: Konwersja na int (3/2 -> 2)
        obliczenia::wymierna w11(3, 2);
        int i = static_cast<int>(w11);
        test(i == 2, "Konwersja na int (zaokraglenie)", testNumber);

        // Test 20: Operator << dla 0
        test(compareStream(w1, "0"), "Formatowanie: 0", testNumber);

        // Test 21: Operator << dla 1/2 (0.5)
        test(compareStream(w3, "0.5"), "Formatowanie: ulamek skonczony", testNumber);

        // Test 22: Operator << dla 1/3 (0.(3))
        obliczenia::wymierna w12(1, 3);
        test(compareStream(w12, "0.(3)"), "Formatowanie: ulamek okresowy", testNumber);

        // Test 23: Operator << dla -5/3 (-1.(6))
        obliczenia::wymierna w13(-5, 3);
        test(compareStream(w13, "-1.(6)"), "Formatowanie: ujemny ulamek okresowy", testNumber);

        // Test 24: Operator << dla liczby calkowitej (7/1 -> 7)
        obliczenia::wymierna w14(7, 1);
        test(compareStream(w14, "7"), "Formatowanie: liczba calkowita", testNumber);

        // Test 25: Wyjatek przy przepelnieniu (INT_MAX * 2)
        obliczenia::wymierna w15(INT_MAX, 1);
        obliczenia::wymierna w16(2, 1);
        exceptionThrown = false;
        try {
            obliczenia::wymierna w17 = w15 * w16;
        } catch (const obliczenia::przekroczenie_zakresu& e) {
            exceptionThrown = true;
        }
        test(exceptionThrown, "Wyjatek: przekroczenie zakresu", testNumber);

        // Test 26: Kopiowanie (konstruktor kopiujacy)
        obliczenia::wymierna w18(w3);
        test(w18.getLicznik() == 1 && w18.getMianownik() == 2, "Konstruktor kopiujacy", testNumber);

        // Test 27: Przypisanie kopiujace
        obliczenia::wymierna w19;
        w19 = w5;
        test(w19.getLicznik() == -2 && w19.getMianownik() == 3, "Operator przypisania", testNumber);

    } catch (const std::exception& e) {
        std::cerr << "Niespodziewany wyjatek: " << e.what() << std::endl;
    }

    return 0;
}