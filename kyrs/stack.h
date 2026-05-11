#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include <stdexcept>

template <typename T>
class Stack {
private:
    Vector<T> data_;
    
public:
    Stack() {}
    
    void push(const T& value) {
        data_.push_back(value);
    }
    
    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        data_.pop_back();
    }
    
    T& top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data_[data_.size() - 1];
    }
    
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data_[data_.size() - 1];
    }
    
    bool empty() const {
        return data_.empty();
    }
    
    size_t size() const {
        return data_.size();
    }
    
    void clear() {
        data_.clear();
    }
};

#endif 