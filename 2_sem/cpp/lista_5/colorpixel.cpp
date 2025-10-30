#include "colorpixel.hpp"
#include "vector.hpp"
ColorPixel::ColorPixel() : Pixel(), Color() {};
ColorPixel::ColorPixel(int x, int y, unsigned short red, unsigned short green, unsigned short blue) : Pixel(x, y), Color(red, green, blue) {};
void ColorPixel::move_pixel(Vector v)
{
    int new_x = get_x() + v.get_dx();
    int new_y = get_y() + v.get_dy();
    if (new_x > Max_X || new_y > Max_Y)
        throw std::out_of_range("Pixel is out of screen(1920x1080)");
    set_x(new_x);
    set_y(new_y);
}