#include <cassert>
#include <iostream>
#include "Queue.hpp"

void test_push()
{
    std::cout << "TEST: Push - queue with capacity 3" << std::endl;
    Queue q(3);
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3(5, 6);
    std::cout << "Adding p1 (1,2), p2 (3,4), p3 (5,6)" << std::endl;
    q.push(p1);
    q.push(p2);
    q.push(p3);
    std::cout << "Current queue length: " << q.length() << std::endl;
    assert(q.length() == 3);
    std::cout << "Front element of the queue: (" << q.front().get_x() << ", " << q.front().get_y() << ")" << std::endl;
    assert(q.front().get_x() == p1.get_x() && q.front().get_y() == p1.get_y());

    std::cout << "Attempting to add an element to a full queue:" << std::endl;
    try
    {
        Point p4(7, 8);
        q.push(p4);
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }
    std::cout << "test_push passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void test_pop()
{
    std::cout << "TEST: Pop - queue with capacity 3" << std::endl;
    Queue q(3);
    Point p1(1, 2);
    Point p2(3, 4);
    std::cout << "Adding p1 (1,2) and p2 (3,4)" << std::endl;
    q.push(p1);
    q.push(p2);
    std::cout << "Removing the first element (p1)" << std::endl;
    q.pop();
    std::cout << "Current queue length: " << q.length() << std::endl;
    assert(q.length() == 1);
    std::cout << "New front element of the queue: (" << q.front().get_x() << ", " << q.front().get_y() << ")" << std::endl;
    assert(q.front().get_x() == p2.get_x() && q.front().get_y() == p2.get_y());

    std::cout << "Attempting to pop an element from an empty queue:" << std::endl;
    q.pop(); // Remove the last element
    try
    {
        q.pop();
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }
    std::cout << "test_pop passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void test_front()
{
    std::cout << "TEST: Front - queue with capacity 3" << std::endl;
    Queue q(3);
    Point p1(1, 2);
    std::cout << "Adding p1 (1,2) to the queue" << std::endl;
    q.push(p1);
    std::cout << "Retrieving the front element: (" << q.front().get_x() << ", " << q.front().get_y() << ")" << std::endl;
    assert(q.front().get_x() == p1.get_x() && q.front().get_y() == p1.get_y());

    std::cout << "Removing element and attempting to retrieve front() from an empty queue:" << std::endl;
    q.pop();
    try
    {
        q.front();
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }
    std::cout << "test_front passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void test_length()
{
    std::cout << "TEST: Length - queue with capacity 3" << std::endl;
    Queue q(3);
    std::cout << "Initial queue length: " << q.length() << std::endl;
    assert(q.length() == 0);
    Point p1(1, 2);
    std::cout << "Adding p1 (1,2)" << std::endl;
    q.push(p1);
    std::cout << "Queue length after adding an element: " << q.length() << std::endl;
    assert(q.length() == 1);
    std::cout << "test_length passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void test_constructor()
{
    std::cout << "TEST: Constructor - queue with capacity 3" << std::endl;
    Queue q(3);
    std::cout << "Initial queue length: " << q.length() << std::endl;
    assert(q.length() == 0);
    std::cout << "Queue capacity: " << q.q_capacity() << std::endl;
    assert(q.q_capacity() == 3);

    std::cout << "Attempting to create a queue with invalid capacity (0):" << std::endl;
    try
    {
        Queue q_invalid(0);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }
    std::cout << "test_constructor passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void test_copy_constructor()
{
    std::cout << "TEST: Copy Constructor - queue with capacity 3" << std::endl;
    Queue q1(3);
    Point p1(1, 2);
    std::cout << "Adding p1 (1,2) to original queue (q1)" << std::endl;
    q1.push(p1);
    std::cout << "Creating a copy of the queue (q2) using the copy constructor" << std::endl;
    Queue q2(q1);
    std::cout << "Copied queue length: " << q2.length() << std::endl;
    assert(q2.length() == 1);
    std::cout << "Front element in q2: (" << q2.front().get_x() << ", " << q2.front().get_y() << ")" << std::endl;
    assert(q2.front().get_x() == p1.get_x() && q2.front().get_y() == p1.get_y());
    std::cout << "test_copy_constructor passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}
void test_move_constructor()
{
    std::cout << "TEST: Move Constructor - queue with capacity 3" << std::endl;
    Queue q1(3);
    Point p1(1, 2);
    std::cout << "Adding p1 (1,2) to queue q1" << std::endl;
    q1.push(p1);
    std::cout << "Moving contents of q1 to a new queue q2" << std::endl;
    Queue q2(std::move(q1));
    std::cout << "Queue q2 length: " << q2.length() << std::endl;
    assert(q2.length() == 1);
    std::cout << "Front element of q2: (" << q2.front().get_x() << ", " << q2.front().get_y() << ")" << std::endl;
    assert(q2.front().get_x() == p1.get_x() && q2.front().get_y() == p1.get_y());
    std::cout << "Queue q1 should be empty after move. q1 length: " << q1.length() << std::endl;
    assert(q1.length() == 0);
    q2.push(Point(3, 2));
    q2.pop();
    std::cout << "q2: " << q2.front().get_x() << ", " << q2.front().get_y() << ' ';
    try
    {
        std::cout << "q1: " << q1.front().get_x() << ", " << q1.front().get_y() << '\n';
    }
    catch (std::out_of_range &e)
    {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }
    std::cout << "test_move_constructor passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void test_assignment_operator()
{
    std::cout << "TEST: Copy Assignment Operator - queue with capacity 3" << std::endl;
    Queue q1(3);
    Point p1(1, 2);
    std::cout << "Adding p1 (1,2) to queue q1" << std::endl;
    q1.push(p1);
    Queue q2;
    std::cout << "Assigning contents of q1 to q2" << std::endl;
    q2 = q1;
    std::cout << "Queue q2 length: " << q2.length() << std::endl;
    assert(q2.length() == 1);
    std::cout << "Front element of q2: (" << q2.front().get_x() << ", " << q2.front().get_y() << ")" << std::endl;
    assert(q2.front().get_x() == p1.get_x() && q2.front().get_y() == p1.get_y());
    std::cout << "test_assignment_operator passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void test_move_assignment_operator()
{
    std::cout << "TEST: Move Assignment Operator - queue with capacity 3" << std::endl;
    Queue q1(3);
    Point p1(1, 2);
    std::cout << "Adding p1 (1,2) to queue q1" << std::endl;
    q1.push(p1);
    Queue q2;
    std::cout << "Performing move assignment: q2 = std::move(q1)" << std::endl;
    q2 = std::move(q1);
    std::cout << "Queue q2 length: " << q2.length() << std::endl;
    assert(q2.length() == 1);
    std::cout << "Front element of q2: (" << q2.front().get_x() << ", " << q2.front().get_y() << ")" << std::endl;
    assert(q2.front().get_x() == p1.get_x() && q2.front().get_y() == p1.get_y());
    std::cout << "After move, queue q1 should be empty. q1 length: " << q1.length() << std::endl;
    assert(q1.length() == 0);
    std::cout << "test_move_assignment_operator passed" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}
int main()
{
    std::cout << "Starting tests for Queue class" << std::endl;
    test_push();
    test_pop();
    test_front();
    test_length();
    test_constructor();
    test_copy_constructor();
    test_move_constructor();
    test_assignment_operator();
    test_move_assignment_operator();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
