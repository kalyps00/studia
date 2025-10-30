#ifndef QUEUE_H
#define QUEUE_H
#include "point.hpp"
#include <initializer_list>
#include <stdexcept>

class Queue
{
private:
    int capacity, num_of_elements = 0, first = 0;
    Point *arr;

public:
    // constructors
    Queue(int capacity);
    Queue();
    Queue(std::initializer_list<Point>);
    Queue(Queue &que);
    Queue(Queue &&que);
    ~Queue();
    // overloading operators
    Queue &operator=(Queue &other);
    Queue &operator=(Queue &&ther);
    // metods
    void push(const Point &point);
    void pop();
    Point front();
    int length();
    int q_capacity();
};
#endif
