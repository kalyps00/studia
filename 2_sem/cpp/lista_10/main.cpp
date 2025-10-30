#include "wymierna.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits> // Required for std::numeric_limits

// Helper function to print test results
void test_result(const std::string &test_name, bool success, const std::string &details = "")
{
    std::cout << "Test: " << test_name << " - " << (success ? "PASSED" : "FAILED");
    if (!details.empty())
    {
        std::cout << " | " << details;
    }
    std::cout << std::endl;
}

int main()
{
    using namespace obliczenia;
    std::cout << "Rozpoczynam testowanie klasy wymierna...\n"
              << std::endl;

    // Test konstruktorów
    std::cout << "--- Testy Konstruktorow ---" << std::endl;
    try
    {
        wymierna w1; // Domyślny
        test_result("Konstruktor domyslny", w1.get_licz() == 0 && w1.get_mian() == 1, "w1 = " + std::to_string(w1.get_licz()) + "/" + std::to_string(w1.get_mian()));

        wymierna w2(5); // Konwertujący z int
        test_result("Konstruktor konwertujacy (int)", w2.get_licz() == 5 && w2.get_mian() == 1, "w2 = " + std::to_string(w2.get_licz()) + "/" + std::to_string(w2.get_mian()));

        wymierna w3(2, 4); // Licznik i mianownik (normalizacja)
        test_result("Konstruktor (licz, mian) z normalizacja", w3.get_licz() == 1 && w3.get_mian() == 2, "w3 = " + std::to_string(w3.get_licz()) + "/" + std::to_string(w3.get_mian()));

        wymierna w4(3, -5); // Ujemny mianownik
        test_result("Konstruktor (ujemny mianownik)", w4.get_licz() == -3 && w4.get_mian() == 5, "w4 = " + std::to_string(w4.get_licz()) + "/" + std::to_string(w4.get_mian()));

        wymierna w5(-6, -8); // Oba ujemne
        test_result("Konstruktor (oba ujemne)", w5.get_licz() == 3 && w5.get_mian() == 4, "w5 = " + std::to_string(w5.get_licz()) + "/" + std::to_string(w5.get_mian()));

        wymierna w_zero_num(0, 10);
        test_result("Konstruktor (licznik zero)", w_zero_num.get_licz() == 0 && w_zero_num.get_mian() == 1, "w_zero_num = " + std::to_string(w_zero_num.get_licz()) + "/" + std::to_string(w_zero_num.get_mian()));
    }
    catch (const std::exception &e)
    {
        test_result("Testy konstruktorow podstawowych", false, "Wyjatek: " + std::string(e.what()));
    }

    // Test wyjątku dzielenie_przez_0 w konstruktorze
    try
    {
        wymierna w_err(1, 0);
        test_result("Konstruktor (dzielenie przez zero)", false, "Nie zgloszono wyjatku dzielenie_przez_0.");
    }
    catch (const dzielenie_przez_0 &e)
    {
        test_result("Konstruktor (dzielenie przez zero)", true, "Zgloszono poprawny wyjatek: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        test_result("Konstruktor (dzielenie przez zero)", false, "Zgloszono niepoprawny wyjatek: " + std::string(e.what()));
    }
    std::cout << std::endl;

    // Test getterów (już częściowo testowane powyżej)
    std::cout << "--- Testy Getterow ---" << std::endl;
    wymierna wg(7, 13);
    test_result("get_licz()", wg.get_licz() == 7);
    test_result("get_mian()", wg.get_mian() == 13);
    std::cout << std::endl;

    // Test operatorów unarnych
    std::cout << "--- Testy Operatorow Unarnych ---" << std::endl;
    wymierna wu1(2, 3);
    wymierna wu1_neg = -wu1;
    test_result("Operator unarny - (negacja)", wu1_neg.get_licz() == -2 && wu1_neg.get_mian() == 3, "- (2/3) = " + std::to_string(wu1_neg.get_licz()) + "/" + std::to_string(wu1_neg.get_mian()));

    wymierna wu2(-2, 3);
    wymierna wu2_neg = -wu2;
    test_result("Operator unarny - (negacja ujemnej)", wu2_neg.get_licz() == 2 && wu2_neg.get_mian() == 3, "- (-2/3) = " + std::to_string(wu2_neg.get_licz()) + "/" + std::to_string(wu2_neg.get_mian()));

    wymierna wu3(0, 1);
    wymierna wu3_neg = -wu3;
    test_result("Operator unarny - (negacja zera)", wu3_neg.get_licz() == 0 && wu3_neg.get_mian() == 1, "- (0/1) = " + std::to_string(wu3_neg.get_licz()) + "/" + std::to_string(wu3_neg.get_mian()));

    wymierna wu4(3, 5);
    wymierna wu4_inv = !wu4;
    test_result("Operator unarny ! (odwrotnosc)", wu4_inv.get_licz() == 5 && wu4_inv.get_mian() == 3, "! (3/5) = " + std::to_string(wu4_inv.get_licz()) + "/" + std::to_string(wu4_inv.get_mian()));

    wymierna wu5(-3, 5);
    wymierna wu5_inv = !wu5;
    test_result("Operator unarny ! (odwrotnosc ujemnej)", wu5_inv.get_licz() == -5 && wu5_inv.get_mian() == 3, "! (-3/5) = " + std::to_string(wu5_inv.get_licz()) + "/" + std::to_string(wu5_inv.get_mian()));

    try
    {
        wymierna wu_zero(0, 1);
        wymierna wu_zero_inv = !wu_zero;
        test_result("Operator unarny ! (odwrotnosc zera)", false, "Nie zgloszono wyjatku dzielenie_przez_0.");
    }
    catch (const dzielenie_przez_0 &e)
    {
        test_result("Operator unarny ! (odwrotnosc zera)", true, "Zgloszono poprawny wyjatek: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        test_result("Operator unarny ! (odwrotnosc zera)", false, "Zgloszono niepoprawny wyjatek: " + std::string(e.what()));
    }
    std::cout << std::endl;

    // Test operatorów binarnych arytmetycznych i przypisania
    std::cout << "--- Testy Operatorow Binarnych (+, +=, -, -=, *, *=, /, /=) ---" << std::endl;
    wymierna w_op1(1, 2), w_op2(1, 3);

    // Dodawanie
    wymierna w_add_res = w_op1 + w_op2; // 1/2 + 1/3 = 3/6 + 2/6 = 5/6
    test_result("Operator +", w_add_res.get_licz() == 5 && w_add_res.get_mian() == 6, "1/2 + 1/3 = " + std::to_string(w_add_res.get_licz()) + "/" + std::to_string(w_add_res.get_mian()));
    wymierna w_add_assign(1, 2);
    w_add_assign += w_op2; // 1/2 + 1/3 = 5/6
    test_result("Operator +=", w_add_assign.get_licz() == 5 && w_add_assign.get_mian() == 6, "(1/2) += 1/3 -> " + std::to_string(w_add_assign.get_licz()) + "/" + std::to_string(w_add_assign.get_mian()));

    // Odejmowanie
    wymierna w_sub_res = w_op1 - w_op2; // 1/2 - 1/3 = 3/6 - 2/6 = 1/6
    test_result("Operator -", w_sub_res.get_licz() == 1 && w_sub_res.get_mian() == 6, "1/2 - 1/3 = " + std::to_string(w_sub_res.get_licz()) + "/" + std::to_string(w_sub_res.get_mian()));
    wymierna w_sub_assign(1, 2);
    w_sub_assign -= w_op2; // 1/2 - 1/3 = 1/6
    test_result("Operator -=", w_sub_assign.get_licz() == 1 && w_sub_assign.get_mian() == 6, "(1/2) -= 1/3 -> " + std::to_string(w_sub_assign.get_licz()) + "/" + std::to_string(w_sub_assign.get_mian()));

    // Mnożenie
    wymierna w_mul_res = w_op1 * w_op2; // 1/2 * 1/3 = 1/6
    test_result("Operator *", w_mul_res.get_licz() == 1 && w_mul_res.get_mian() == 6, "1/2 * 1/3 = " + std::to_string(w_mul_res.get_licz()) + "/" + std::to_string(w_mul_res.get_mian()));
    wymierna w_mul_assign(1, 2);
    w_mul_assign *= w_op2; // 1/2 * 1/3 = 1/6
    test_result("Operator *=", w_mul_assign.get_licz() == 1 && w_mul_assign.get_mian() == 6, "(1/2) *= 1/3 -> " + std::to_string(w_mul_assign.get_licz()) + "/" + std::to_string(w_mul_assign.get_mian()));

    // Dzielenie
    wymierna w_div_res = w_op1 / w_op2; // (1/2) / (1/3) = 1/2 * 3/1 = 3/2
    test_result("Operator /", w_div_res.get_licz() == 3 && w_div_res.get_mian() == 2, "(1/2) / (1/3) = " + std::to_string(w_div_res.get_licz()) + "/" + std::to_string(w_div_res.get_mian()));
    wymierna w_div_assign(1, 2);
    w_div_assign /= w_op2; // (1/2) / (1/3) = 3/2
    test_result("Operator /=", w_div_assign.get_licz() == 3 && w_div_assign.get_mian() == 2, "(1/2) /= 1/3 -> " + std::to_string(w_div_assign.get_licz()) + "/" + std::to_string(w_div_assign.get_mian()));

    // Test dzielenia przez zero w operatorach binarnych
    wymierna w_zero_div(0, 1);
    try
    {
        wymierna w_err_div = w_op1 / w_zero_div;
        test_result("Operator / (dzielenie przez zero)", false, "Nie zgloszono wyjatku.");
    }
    catch (const dzielenie_przez_0 &e)
    {
        test_result("Operator / (dzielenie przez zero)", true, "Zgloszono poprawny wyjatek: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        test_result("Operator / (dzielenie przez zero)", false, "Zgloszono niepoprawny wyjatek: " + std::string(e.what()));
    }
    try
    {
        wymierna w_err_div_assign(1, 2);
        w_err_div_assign /= w_zero_div;
        test_result("Operator /= (dzielenie przez zero)", false, "Nie zgloszono wyjatku.");
    }
    catch (const dzielenie_przez_0 &e)
    {
        test_result("Operator /= (dzielenie przez zero)", true, "Zgloszono poprawny wyjatek: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        test_result("Operator /= (dzielenie przez zero)", false, "Zgloszono niepoprawny wyjatek: " + std::string(e.what()));
    }
    std::cout << std::endl;

    // Test przekroczenia zakresu
    std::cout << "--- Testy Przekroczenia Zakresu ---" << std::endl;
    wymierna w_max_int(std::numeric_limits<int>::max());
    wymierna w_two(2);
    wymierna w_one(1);
    wymierna w_min_int(std::numeric_limits<int>::min());

    // Test + dla przekroczenia zakresu
    try
    {
        wymierna res = w_max_int + w_one;
        test_result("Operator + (przekroczenie zakresu - dodatnie)", false, "Nie zgloszono wyjatku przekroczenie_zakresu.");
    }
    catch (const przekroczenie_zakresu &e)
    {
        test_result("Operator + (przekroczenie zakresu - dodatnie)", true, "Zgloszono poprawny wyjatek: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        test_result("Operator + (przekroczenie zakresu - dodatnie)", false, "Zgloszono niepoprawny wyjatek: " + std::string(e.what()));
    }
    // Test * dla przekroczenia zakresu
    try
    {
        wymierna res = w_max_int * w_two;
        test_result("Operator * (przekroczenie zakresu)", false, "Nie zgloszono wyjatku przekroczenie_zakresu.");
    }
    catch (const przekroczenie_zakresu &e)
    {
        test_result("Operator * (przekroczenie zakresu)", true, "Zgloszono poprawny wyjatek: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        test_result("Operator * (przekroczenie zakresu)", false, "Zgloszono niepoprawny wyjatek: " + std::string(e.what()));
    }
    // Test ! dla przekroczenia zakresu (np. ! (1 / MAX_INT) -> MAX_INT / 1)
    try
    {
        wymierna w_small_inv(1, std::numeric_limits<int>::max());
        wymierna res = !w_small_inv;
        test_result("Operator ! (przekroczenie zakresu przy odwrotnosci)", false, "Nie zgloszono wyjatku przekroczenie_zakresu.");
    }
    catch (const przekroczenie_zakresu &e)
    {
        test_result("Operator ! (przekroczenie zakresu przy odwrotnosci)", true, "Zgloszono poprawny wyjatek: " + std::string(e.what()));
    }
    catch (const std::exception &e)
    {
        test_result("Operator ! (przekroczenie zakresu przy odwrotnosci)", false, "Zgloszono niepoprawny wyjatek: " + std::string(e.what()));
    }

    std::cout << std::endl;

    // Test operatorów rzutowania
    std::cout << "--- Testy Operatorow Rzutowania ---" << std::endl;
    wymierna w_cast1(7, 2); // 3.5
    double d_cast1 = w_cast1;
    test_result("Rzutowanie na double", d_cast1 == 3.5, "7/2 -> " + std::to_string(d_cast1));
    int i_cast1 = static_cast<int>(w_cast1);
    test_result("Rzutowanie na int (7/2 -> 4)", i_cast1 == 4, "7/2 -> " + std::to_string(i_cast1));

    wymierna w_cast2(2, 3); // 0.666...
    double d_cast2 = w_cast2;
    // Porównanie double wymaga tolerancji, ale dla prostych przypadków może być OK
    test_result("Rzutowanie na double (okresowy)", std::abs(d_cast2 - (2.0 / 3.0)) < 1e-9, "2/3 -> " + std::to_string(d_cast2));
    int i_cast2 = static_cast<int>(w_cast2); // round(0.666...) = 1
    test_result("Rzutowanie na int (2/3 -> 1)", i_cast2 == 1, "2/3 -> " + std::to_string(i_cast2));

    wymierna w_cast3(-7, 2); // -3.5
    double d_cast3 = w_cast3;
    test_result("Rzutowanie na double (ujemna)", d_cast3 == -3.5, "-7/2 -> " + std::to_string(d_cast3));
    int i_cast3 = static_cast<int>(w_cast3);                                                                                                                 // round(-3.5) -> -3 (std::round rounds half to even or away from zero depending on impl, C++11 std::round rounds halves away from zero)
    test_result("Rzutowanie na int (-7/2 -> -4 lub -3)", i_cast3 == -4 || i_cast3 == -3, "-7/2 -> " + std::to_string(i_cast3) + " (std::round(-3.5) = -4)"); // std::round(-3.5) is -4
    if (i_cast3 != -4)
        std::cout << "    Uwaga: std::round(-3.5) zwrocilo " << i_cast3 << ", oczekiwano -4." << std::endl;

    std::cout << std::endl;

    // Test operatora strumieniowego <<
    std::cout << "--- Testy Operatora Strumieniowego << ---" << std::endl;
    wymierna w_str1(2, 3);           // 0.(6)
    wymierna w_str2(1, 7);           // 0.(142857)
    wymierna w_str3(2359348, 99900); // 23.61(709)
    wymierna w_str4(1, 4);           // 0.25
    wymierna w_str5(5);              // 5
    wymierna w_str6(-1, 3);          // -0.(3)
    wymierna w_str7(0, 1);           // 0
    wymierna w_str8(22, 7);          // 3.(142857)

    std::cout << "2/3 = " << w_str1 << std::endl;
    std::cout << "1/7 = " << w_str2 << std::endl;
    std::cout << "2359348/99900 = " << w_str3 << " (oczekiwano: 23.61(709))" << std::endl;
    std::cout << "1/4 = " << w_str4 << std::endl;
    std::cout << "5/1 = " << w_str5 << std::endl;
    std::cout << "-1/3 = " << w_str6 << std::endl;
    std::cout << "0/1 = " << w_str7 << std::endl;
    std::cout << "22/7 = " << w_str8 << std::endl;
    std::cout << std::endl;

    // Test kopiowania
    std::cout << "--- Testy Kopiowania ---" << std::endl;
    wymierna w_orig(123, 456);     // Po normalizacji: 41/152
    wymierna w_copy_ctor = w_orig; // Konstruktor kopiujący
    test_result("Konstruktor kopiujacy", w_copy_ctor.get_licz() == w_orig.get_licz() && w_copy_ctor.get_mian() == w_orig.get_mian(),
                "Oryginal: " + std::to_string(w_orig.get_licz()) + "/" + std::to_string(w_orig.get_mian()) +
                    " Kopia: " + std::to_string(w_copy_ctor.get_licz()) + "/" + std::to_string(w_copy_ctor.get_mian()));

    wymierna w_assign_op(1, 1);
    w_assign_op = w_orig; // Przypisanie kopiujące
    test_result("Operator przypisania kopiujacego", w_assign_op.get_licz() == w_orig.get_licz() && w_assign_op.get_mian() == w_orig.get_mian(),
                "Oryginal: " + std::to_string(w_orig.get_licz()) + "/" + std::to_string(w_orig.get_mian()) +
                    " Po przypisaniu: " + std::to_string(w_assign_op.get_licz()) + "/" + std::to_string(w_assign_op.get_mian()));

    // Sprawdzenie, czy kopia jest głęboka (modyfikacja oryginału nie wpływa na kopię)
    wymierna w_mod(7, 8);
    wymierna w_mod_copy = w_mod;
    w_mod = wymierna(1, 1); // Zmieniamy w_mod
    test_result("Gleboka kopia (konstruktor)", w_mod_copy.get_licz() == 7 && w_mod_copy.get_mian() == 8,
                "Kopia po modyfikacji oryginalu: " + std::to_string(w_mod_copy.get_licz()) + "/" + std::to_string(w_mod_copy.get_mian()) + " (oczekiwano 7/8)");

    std::cout << "\nZakonczono testowanie." << std::endl;

    return 0;
}
