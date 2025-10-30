#ifndef COLORNAM_HPP
#define COLORNAM_HPP
#include "color.hpp"
class ColorNamed : virtual public Color
{
private:
    std::string name;

public:
    ColorNamed();
    ColorNamed(std::string name, unsigned short red, unsigned short green, unsigned short blue);
    std::string get_name() const;
    void set_name(std::string name);
};
#endif