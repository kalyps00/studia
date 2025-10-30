#include "transparentcolor.hpp"
#include <stdexcept>

Transparentcolor::Transparentcolor() : Color(), alpha(255) {};
Transparentcolor::Transparentcolor(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha) : Color(red, green, blue)
{
    if (alpha < 0 || alpha > 255)
        throw std::out_of_range("Alpha must be between 0-255");
    this->alpha = alpha;
}
unsigned short Transparentcolor::get_alpha() const
{
    return alpha;
}
void Transparentcolor::set_alpha(unsigned short alpha)
{
    if (alpha < 0 || alpha > 255)
        throw std::out_of_range("Alpha must be between 0-255");
    this->alpha = alpha;
}
