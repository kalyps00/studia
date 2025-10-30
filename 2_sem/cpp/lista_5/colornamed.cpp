#include "colornamed.hpp"
#include <stdexcept>

ColorNamed::ColorNamed() : Color(), name("") {};

ColorNamed::ColorNamed(std::string name, unsigned short red, unsigned short green, unsigned short blue) : Color(red, green, blue)
{
    if (name.empty())
        throw std::invalid_argument("Name cannot be empty");
    this->name = name;
};
std::string ColorNamed::get_name() const
{
    return name;
}
void ColorNamed::set_name(std::string name)
{
    for (char c : name)
    {
        if (!std::islower(c))
        {
            throw std::invalid_argument("Name must contain only lowercase letters");
        }
    }
    this->name = name;
}