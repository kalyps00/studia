#ifndef COLORPIXEL_HPP
#define COLORPIXEL_HPP
#include "pixel.hpp"
#include "color.hpp"
#include "vector.hpp"

class ColorPixel : public Pixel, private Color
{
public:
    ColorPixel();
    ColorPixel(int x, int y, unsigned short red, unsigned short green, unsigned short blue);
    void move_pixel(Vector v);
};
#endif