#ifndef STACK_EXCEPTIONS_H
#define STACK_EXCEPTIONS_H
#include <exception>
#include <string>
class StackOverflow : public std::exception{
public:
    StackOverflow(): reason_("Stack Overflow"){}
    const char* what() const noexcept override
    {return reason_.c_str();}
private:
    const std::string reason_;
};
class StackUnderflow : public std::exception{
public:
    StackUnderflow() : reason_("Stack Underflow"){}
    const char* what() const noexcept override
    {return reason_.c_str();}
private:
    const std::string reason_;
};
#endif