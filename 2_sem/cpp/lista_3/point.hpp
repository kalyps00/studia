#ifndef PUNKT_H
#define PUNKT_H
class Point
{
private:
    double x, y;

public:
    Point();
    Point(double x1, double y1);
    double get_x(), get_y();
    void set_x(double x), set_y(double y);
};
#endif