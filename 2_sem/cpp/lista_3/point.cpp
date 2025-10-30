#include "point.hpp"
Point::Point(double x, double y) : x(x), y(y) {};
Point::Point() : x(0.0), y(0.0) {};
double Point::get_x()
{
    return x;
}
double Point::get_y()
{
    return y;
}
void Point::set_x(double x)
{
    this->x = x;
}
void Point::set_y(double y)
{
    this->y = y;
}