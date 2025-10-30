#ifndef TRANS_NAMED_COLOR_HPP
#define TRANS_NAMED_COLOR_HPP
#include "colornamed.hpp"
#include "transparentcolor.hpp"

class ColorTransparentNamed : public ColorNamed, public Transparentcolor
{
public:
    ColorTransparentNamed();
    ColorTransparentNamed(std::string name, unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha);
};
#endif