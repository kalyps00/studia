#include "color.hpp"
#include <stdexcept>
#include <algorithm>
Color::Color() : red(0), green(0), blue(0) {};
Color::Color(unsigned short red, unsigned short green, unsigned short blue)
{
    if (red < 0 || red > 255)
        throw std::out_of_range("Red must be between 0-255");
    if (green < 0 || green > 255)
        throw std::out_of_range("Green must be between 0-255");
    if (blue < 0 || blue > 255)
        throw std::out_of_range("Blue must be between 0-255");
    this->red = red;
    this->green = green;
    this->blue = blue;
}
unsigned short Color::get_red() const
{
    return red;
}
unsigned short Color::get_green() const
{
    return green;
}
unsigned short Color::get_blue() const
{
    return blue;
}
void Color::set_red(unsigned short red)
{
    if (red < 0 || red > 255)
        throw std::out_of_range("Red must be between 0-255");
    this->red = red;
}
void Color::set_green(unsigned short green)
{
    if (green < 0 || green > 255)
        throw std::out_of_range("Green must be between 0-255");
    this->green = green;
}
void Color::set_blue(unsigned short blue)
{
    if (blue < 0 || blue > 255)
        throw std::out_of_range("Blue must be between 0-255");
    this->blue = blue;
}
void Color::darken(int percentage)
{
    if (percentage < 0 || percentage > 100)
        throw std::out_of_range("Percentage must be between 0-100");
    red = std::max(0, red - (red * percentage) / 100);
    green = std::max(0, green - (green * percentage) / 100);
    blue = std::max(0, blue - (blue * percentage) / 100);
}
void Color::lighten(int percentage)
{
    if (percentage < 0 || percentage > 100)
        throw std::out_of_range("Percentage must be between 0-100");
    red = std::min(255, red + (red * percentage) / 100);
    green = std::min(255, green + (green * percentage) / 100);
    blue = std::min(255, blue + (blue * percentage) / 100);
}
Color Color::mix(const Color &c1, const Color &c2)
{
    unsigned short red = (c1.red + c2.red) / 2;
    unsigned short green = (c1.green + c2.green) / 2;
    unsigned short blue = (c1.blue + c2.blue) / 2;
    return Color(red, green, blue);
}
