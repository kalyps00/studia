#include "kola_punkty.hpp"
#include <cmath>
#include <stdexcept>
// prosta
Line::Line(double a, double b, double c) : A(a), B(b), C(c)
{
    if (a == 0 && b == 0)
        throw std::invalid_argument("nie prosta");
};
double Line::get_A()
{
    return A;
}
double Line::get_B()
{
    return B;
}
double Line::get_C()
{
    return C;
}
void Line::set_A(double a)
{
    if (a == 0 && B == 0)
        throw std::invalid_argument("nie prosta");
    A = a;
}
void Line::set_B(double b)
{
    if (A == 0 && b == 0)
        throw std::invalid_argument("nie prosta");
    B = b;
}
void Line::set_C(double c)
{
    C = c;
}
// wektor
Vector::Vector(double dx1, double dy1) : dx(dx1), dy(dy1) {};
Vector::Vector() : dx(0), dy(0) {};
double Vector::get_dx()
{
    return dx;
}
double Vector::get_dy()
{
    return dy;
}
void Vector::set_dx(double dx1)
{
    dx = dx1;
}
void Vector::set_dy(double dy1)
{
    dy = dy1;
}

// point
Point::Point(double x1, double y1) : x(x1), y(y1) {};
Point::Point() : x(0), y(0) {};
double Point::get_x()
{
    return x;
}
double Point::get_y()
{
    return y;
}
void Point::set_x(double x1)
{
    x = x1;
}
void Point::set_y(double y1)
{
    y = y1;
}

void Point::translate(Vector v)
{
    x += v.get_dx();
    y += v.get_dy();
}

void Point::rotate(double angle, Point center)
{
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);
    double newX = cosA * (x - center.get_x()) - sinA * (y - center.get_y()) + center.get_x();
    double newY = sinA * (x - center.get_x()) + cosA * (y - center.get_y()) + center.get_y();
    x = newX;
    y = newY;
}

void Point::central_symmetry(Point center)
{
    x = 2 * center.get_x() - x;
    y = 2 * center.get_y() - y;
}

void Point::axial_symmetry(Line axis)
{
    double a = axis.get_A();
    double b = axis.get_B();
    double c = axis.get_C();
    double d = (a * x + b * y + c) / (a * a + b * b);
    x = x - 2 * a * d;
    y = y - 2 * b * d;
}

// circlex
Circle::Circle(Point middle, double rad) : midle(middle), radius(rad)
{
    if (radius <= 0)
        throw std::invalid_argument("Promień powinien być dodatni");
};
Circle::Circle() : midle(Point(0, 0)), radius(1) {};
Point Circle::get_middle()
{
    return midle;
}
double Circle::get_radius()
{
    return radius;
}
void Circle::set_middle(Point middle)
{
    midle = middle;
}
void Circle::set_radius(double rad)
{
    if (rad <= 0)
        throw std::invalid_argument("Promień powinien być dodatni");
    radius = rad;
}
double Circle::circumference()
{
    return 2 * M_PI * radius;
}
double Circle::area()
{
    return M_PI * pow(radius, 2);
}
bool Circle::is_inside(Point p)
{
    return distance(midle, p) <= radius;
}
void Circle::translate(Vector v)
{
    midle.translate(v);
}
void Circle::rotate(double angle, Point center)
{
    midle.rotate(angle, center);
}
void Circle::central_symmetry(Point center)
{
    midle.central_symmetry(center);
}
void Circle::axial_symmetry(Line axis)
{
    midle.axial_symmetry(axis);
}

// global functions
double distance(Point a, Point b)
{
    return sqrt(pow(a.get_x() - b.get_x(), 2) + pow(a.get_y() - b.get_y(), 2));
}
bool is_inside(Circle a, Circle b)
{
    return distance(a.get_middle(), b.get_middle()) + a.get_radius() <= b.get_radius();
}
bool disjoint(Circle a, Circle b)
{
    return distance(a.get_middle(), b.get_middle()) > a.get_radius() + b.get_radius();
}
