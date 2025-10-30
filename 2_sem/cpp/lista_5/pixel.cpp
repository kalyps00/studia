#include "pixel.hpp"
#include <stdexcept>
#include <cmath>
const int Pixel::Max_X = 1920;
const int Pixel::Max_Y = 1080;

Pixel::Pixel() : x(1), y(1) {};
Pixel::Pixel(int x, int y)
{
    if (x > Max_X || y > Max_Y)
        throw std::out_of_range("Pixel is out of screen(1920x1080)");
    this->x = x;
    this->y = y;
};
int Pixel::get_x() const
{
    return x;
}
int Pixel::get_y() const
{
    return y;
}
void Pixel::set_x(int x)
{
    if (x < 0 || x >= Max_X)
        throw std::out_of_range("Pixel is out of screen (1920x1080)");
    this->x = x;
}
void Pixel::set_y(int y)
{
    if (y < 0 || y >= Max_Y)
        throw std::out_of_range("Pixel is out of screen (1920x1080)");
    this->y = y;
}
int Pixel::left_border_distance()
{
    return x;
}

int Pixel::bottom_border_distance()
{
    return y;
}
int Pixel::right_border_distance()
{
    return Max_X - x;
}
int Pixel::top_border_distance()
{
    return Max_Y - y;
}
int Pixel::distance_between_pixels(Pixel &p1, Pixel &p2)
{
    return (int)std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
int Pixel::distance_between_pixels(Pixel *p1, Pixel *p2)
{
    if (!p1 || !p2)
        throw std::invalid_argument("Null pointer passed to distance_between_pixels");
    return std::sqrt(std::pow(p1->get_x() - p2->get_x(), 2) + std::pow(p1->get_y() - p2->get_y(), 2));
}
