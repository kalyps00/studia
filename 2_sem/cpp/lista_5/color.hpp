#ifndef COLOR_HPP
#define COLOR_HPP
#include <stdexcept>
#include <algorithm>
#include <iostream>
class Color
{
private:
    unsigned short red;
    unsigned short green;
    unsigned short blue;

public:
    Color();
    Color(unsigned short red, unsigned short green, unsigned short blue);
    unsigned short get_red() const;
    unsigned short get_green() const;
    unsigned short get_blue() const;
    void set_red(unsigned short red);
    void set_green(unsigned short green);
    void set_blue(unsigned short blue);
    void darken(int percentage);
    void lighten(int percentage);
    static Color mix(const Color &c1, const Color &c2);
};
#endif