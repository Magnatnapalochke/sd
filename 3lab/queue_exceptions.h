#ifndef QUEUE_EXCEPTIONS_H
#define QUEUE_EXCEPTIONS_H

#include <exception>
#include <string>

class QueueOverflow : public std::exception{
public:
    QueueOverflow(): reason_("Queue Overflow"){}
    const char* what() const noexcept override
    {return reason_.c_str();}
private:
    const std::string reason_;
};

class QueueUnderflow : public std::exception{
public:
    QueueUnderflow() : reason_("Queue Underflow"){}
    const char* what() const noexcept override
    {return reason_.c_str();}
private:
    const std::string reason_;
};

class WrongQueueSize : public std::exception{
public:
    WrongQueueSize() : reason_("Wrong Queue Size"){}
    const char* what() const noexcept override
    {return reason_.c_str();}
private:
    const std::string reason_;
};

#endif