#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class ExceptionSolitare : public std::logic_error
{
public:
    explicit ExceptionSolitare(const std::string &message) : std::logic_error(message) {}
};

class InvalidMoveFormatException : public ExceptionSolitare
{
public:
    explicit InvalidMoveFormatException(const std::string &message = "Invalid move format")
        : ExceptionSolitare(message) {}
};

class EmptyFieldException : public ExceptionSolitare
{
public:
    explicit EmptyFieldException(const std::string &message = "Cannot select an empty field")
        : ExceptionSolitare(message) {}
};

class OccupiedFieldException : public ExceptionSolitare
{
public:
    explicit OccupiedFieldException(const std::string &message = "Target field is already occupied")
        : ExceptionSolitare(message) {}
};

class NoMiddlePieceException : public ExceptionSolitare
{
public:
    explicit NoMiddlePieceException(const std::string &message = "No piece to jump over")
        : ExceptionSolitare(message) {}
};

class OutOfBoardException : public ExceptionSolitare
{
public:
    explicit OutOfBoardException(const std::string &message = "Move outside the board")
        : ExceptionSolitare(message) {}
};

class GameOverException : public ExceptionSolitare
{
public:
    explicit GameOverException(const std::string &message = "Game is over")
        : ExceptionSolitare(message) {}
};

#endif // EXCEPTIONS_HPP
