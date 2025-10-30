#ifndef PIXEL_HPP
#define PIXEL_HPP
#include <iostream>

class Pixel
{
private:
    int x;
    int y;

public:
    static const int Max_X;
    static const int Max_Y;
    Pixel();
    Pixel(int x, int y);
    int get_x() const;
    int get_y() const;
    void set_x(int x);
    void set_y(int y);
    int left_border_distance();
    int right_border_distance();
    int top_border_distance();
    int bottom_border_distance();
    static int distance_between_pixels(Pixel *p1, Pixel *p2);
    static int distance_between_pixels(Pixel &p1, Pixel &p2);
};
#endif