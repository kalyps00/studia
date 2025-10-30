#include "Queue.hpp"
// metods
void Queue::push(const Point &point)
{
    if (num_of_elements == capacity)
    {
        throw std::out_of_range("Queue is full");
    }
    int index = (first + num_of_elements) % capacity;
    arr[index] = point;
    num_of_elements++;
}
void Queue::pop()
{
    if (num_of_elements <= 0)
    {
        throw std::out_of_range("Queue is empty");
    }
    first = (first + 1) % capacity;
    num_of_elements--;
}
Point Queue::front()
{
    if (num_of_elements <= 0)
    {
        throw std::out_of_range("Queue is empty");
    }
    return arr[first];
}
int Queue::length()
{
    return num_of_elements;
}
int Queue::q_capacity()
{
    return capacity;
}
// constructors
Queue::Queue(int capacity) : capacity(capacity), first(0), num_of_elements(0)
{
    if (capacity <= 0)
    {
        throw std::invalid_argument("Cannot initialize queue with non-positive cpacity");
    }
    arr = new Point[capacity];
};
Queue::Queue() : Queue(1) {};
Queue::Queue(std::initializer_list<Point> list) : Queue(list.size())
{
    if (list.size() == 0)
        throw std::invalid_argument("Cannot initialize queue without elements");

    for (const auto x : list)
    {
        push(x);
    }
};
Queue::Queue(Queue &other)
{
    capacity = other.capacity;
    num_of_elements = other.num_of_elements;
    first = other.first;
    arr = new Point[capacity];
    for (int i = 0; i < num_of_elements; i++)
    {
        arr[(first + i) % capacity] = other.arr[(other.first + i) % other.capacity];
    }
};
Queue::Queue(Queue &&other)
{
    capacity = other.capacity;
    num_of_elements = other.num_of_elements;
    first = other.first;
    arr = other.arr;

    other.arr = nullptr;
    other.capacity = 0;
    other.num_of_elements = 0;
    other.first = 0;
};
Queue::~Queue()
{
    delete[] arr;
};
Queue &Queue::operator=(Queue &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete arr;
    capacity = other.capacity;
    num_of_elements = other.num_of_elements;
    first = other.first;
    arr = new Point[capacity];
    for (int i = 0; i < num_of_elements; i++)
    {
        arr[(first + i) % capacity] = other.arr[(other.first + i) % other.capacity];
    }
    return *this;
};
Queue &Queue::operator=(Queue &&other)
{
    if (this == &other)
    {
        return *this;
    }
    delete arr;
    capacity = other.capacity;
    num_of_elements = other.num_of_elements;
    first = other.first;
    arr = other.arr;

    other.arr = nullptr;
    other.capacity = 0;
    other.num_of_elements = 0;
    other.first = 0;
    return *this;
};
