#include <iostream>
#include <vector>
#include <string>
#include <cmath>
std::vector<int64_t> rozklad(int64_t n)
{
    std::vector<int64_t> ans;
    if (n == -1 || n == 1 || n == 0)
    {
        ans.push_back(n);
        return ans;
    }
    if (n < -1)
    {
        ans.push_back(-1);
        n *= -1;
    }
    int sqt = sqrt(n);
    for (int i = 2; i <= sqt; i++)
    {
        while (n % i == 0)
        {
            ans.push_back(i);
            n /= i;
        }
    }
    if (ans.size() <= 1)
        ans.push_back(n);
    return ans;
}
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Jako argument wywołania należy podać conajmnije 1 liczbe ktorej rozklad chcemy pozanc";
    }
    for (int i = 1; i < argc; i++)
    {
        int64_t num;
        try // zrobione tak bo chcialem zby dziallo dalej jak 1 argumnt jest tylko niprawidlowy
        {
            num = std::stoll(argv[i]);
        }
        catch (std::invalid_argument)
        {
            std::cerr << "Nieprawidłowy argument: " << argv[i] << '\n';
            continue;
        }
        catch (std::out_of_range)
        {
            std::cerr << "Za długa liczba: " << argv[i] << '\n';
            continue;
        }
        std::vector<int64_t> czynniki = rozklad(num);
        std::cout << num << " = " << czynniki[0];
        for (int j = 1; j < czynniki.size(); j++)
        {
            std::cout << "*" << czynniki[j];
        }
        std::cout << "\n";
    }
    return 0;
}
