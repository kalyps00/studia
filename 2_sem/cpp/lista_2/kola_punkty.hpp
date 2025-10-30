
class Line
{
private:
    double A, B, C;

public:
    Line(double a, double b, double c);
    double get_A(), get_B(), get_C();
    void set_A(double a), set_B(double b), set_C(double c);
};
class Vector
{
private:
    double dx, dy;

public:
    Vector();
    Vector(double dx1, double dy1);
    double get_dx(), get_dy();
    void set_dx(double dx), set_dy(double dy);
};
class Point
{
private:
    double x, y;

public:
    Point();
    Point(double x1, double y1);
    double get_x(), get_y();
    void set_x(double x), set_y(double y);
    void translate(Vector v);
    void rotate(double angle, Point center = Point(0, 0));
    void central_symmetry(Point center);
    void axial_symmetry(Line axis);
};
class Circle
{
private:
    Point midle;
    double radius;

public:
    Circle();
    Circle(Point middle, double radius);
    Point get_middle();
    double get_radius();
    void set_middle(Point mid), set_radius(double rad);
    double circumference();
    double area();
    bool is_inside(Point p);
    void translate(Vector v);
    void rotate(double angle, Point center = Point(0, 0));
    void central_symmetry(Point center);
    void axial_symmetry(Line axis);
};
double distance(Point a, Point b);
bool is_inside(Circle a, Circle b);
bool disjoint(Circle a, Circle b);