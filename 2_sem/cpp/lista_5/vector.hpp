#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

class Vector
{
private:
    double dx, dy;
    friend class Colorpixel;

public:
    Vector();
    Vector(double dx1, double dy1);
    double get_dx(), get_dy();
    void set_dx(double dx), set_dy(double dy);
};
#endif