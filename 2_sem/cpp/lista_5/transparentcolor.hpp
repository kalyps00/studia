#ifndef TRANSPARENTCOLOR_HPP
#define TRANSPARENTCOLOR_HPP
#include "color.hpp"
class Transparentcolor : virtual public Color
{
private:
    unsigned short alpha;

public:
    Transparentcolor();
    Transparentcolor(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha);
    unsigned short get_alpha() const;
    void set_alpha(unsigned short alpha);
};
#endif