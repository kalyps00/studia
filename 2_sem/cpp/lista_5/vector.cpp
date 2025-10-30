#include "vector.hpp"
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