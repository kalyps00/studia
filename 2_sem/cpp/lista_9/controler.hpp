#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include "model.hpp"
#include "view.hpp"
class Controller
{
    Model &model;
    View &view;

public:
    Controller(Model &m, View &v);
    void processCommand(const std::string &command);
    void run();
};

#endif // CONTROLLER_HPP
