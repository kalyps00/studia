#include "colortransparentnamed.hpp"

ColorTransparentNamed::ColorTransparentNamed() : Color(), ColorNamed(), Transparentcolor() {}

ColorTransparentNamed::ColorTransparentNamed(std::string name, unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha)
    : Color(red, green, blue), ColorNamed(name, red, green, blue), Transparentcolor(red, green, blue, alpha) {}
