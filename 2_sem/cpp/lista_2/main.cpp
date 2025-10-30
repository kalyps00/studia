#include "kola_punkty.hpp"
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        // Testowanie klasy Punkt
        Point p1(1, 2);
        Point p2(3, 4);
        Vector v(1, 1);

        std::cout << "Początkowe punkty:" << std::endl;
        std::cout << "p1: (" << p1.get_x() << ", " << p1.get_y() << ")" << std::endl;
        std::cout << "p2: (" << p2.get_x() << ", " << p2.get_y() << ")" << std::endl;

        p1.translate(v);
        std::cout << "Po przesunięciu p1 o wektor (1, 1):" << std::endl;
        std::cout << "p1: (" << p1.get_x() << ", " << p1.get_y() << ")" << std::endl;

        p1.rotate(90, p2);
        std::cout << "Po obrocie p1 o 90 stopni wokół p2:" << std::endl;
        std::cout << "p1: (" << p1.get_x() << ", " << p1.get_y() << ")" << std::endl;

        p1.central_symmetry(p2);
        std::cout << "Po symetrii środkowej p1 względem p2:" << std::endl;
        std::cout << "p1: (" << p1.get_x() << ", " << p1.get_y() << ")" << std::endl;

        Line axis(1, -1, 0);
        p1.axial_symmetry(axis);
        std::cout << "Po symetrii osiowej p1 względem prostej x = y:" << std::endl;
        std::cout << "p1: (" << p1.get_x() << ", " << p1.get_y() << ")" << std::endl;

        // Testowanie klasy Kolo
        Circle c1(p1, 5);
        Circle c2(p2, 3);

        std::cout << "Początkowe koła:" << std::endl;
        std::cout << "c1: środek (" << c1.get_middle().get_x() << ", " << c1.get_middle().get_y() << "), promień " << c1.get_radius() << std::endl;
        std::cout << "c2: środek (" << c2.get_middle().get_x() << ", " << c2.get_middle().get_y() << "), promień " << c2.get_radius() << std::endl;

        c1.translate(v);
        std::cout << "Po przesunięciu c1 o wektor (1, 1):" << std::endl;
        std::cout << "c1: środek (" << c1.get_middle().get_x() << ", " << c1.get_middle().get_y() << "), promień " << c1.get_radius() << std::endl;

        c1.rotate(90, p2);
        std::cout << "Po obrocie c1 o 90 stopni wokół p2:" << std::endl;
        std::cout << "c1: środek (" << c1.get_middle().get_x() << ", " << c1.get_middle().get_y() << "), promień " << c1.get_radius() << std::endl;

        c1.central_symmetry(p2);
        std::cout << "Po symetrii środkowej c1 względem p2:" << std::endl;
        std::cout << "c1: środek (" << c1.get_middle().get_x() << ", " << c1.get_middle().get_y() << "), promień " << c1.get_radius() << std::endl;

        c1.axial_symmetry(axis);
        std::cout << "Po symetrii osiowej c1 względem prostej x = y:" << std::endl;
        std::cout << "c1: środek (" << c1.get_middle().get_x() << ", " << c1.get_middle().get_y() << "), promień " << c1.get_radius() << std::endl;

        // Testowanie funkcji globalnych
        std::cout << "Odległość między p1 a p2: " << distance(p1, p2) << std::endl;
        std::cout << "Czy k2 zawiera się w k1: " << (is_inside(c1, c2) ? "Tak" : "Nie") << std::endl;
        std::cout << "Czy k1 i k2 są rozłączne: " << (disjoint(c1, c2) ? "Tak" : "Nie") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }
    try
    {
        Line invalidLine(0, 0, 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd przy tworzeniu prostej: " << e.what() << std::endl;
    }
    try
    {
        Circle invalidCircle(Point(0, 0), 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Błąd przy tworzeniu koła: " << e.what() << std::endl;
    }

    return 0;
}
