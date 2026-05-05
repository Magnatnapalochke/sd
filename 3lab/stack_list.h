#ifndef STACK_LIST_H
#define STACK_LIST_H
#include "stack.h"
#include "stack_exceptions.h"
#include <stdexcept>




template <typename T>
class StackList : public Stack<T>{
private:
    struct Node {
        T data_;
        Node* next_;
        Node(const T& value) 
        : data_(value), next_(nullptr){}
    };
    Node* head_;
public:
    StackList(): head_(nullptr){}
    StackList(const StackList&) = delete;
    StackList& operator=(StackList&) = delete;
    ~StackList() override{
        while (head_){
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }
    void push(const T& e) override{
        Node* temp = new Node(e);
        temp->next_ = head_;
        head_ = temp;
    }
    T top()const{
        return head_->data_;
    }
    T pop() override{
        if(!head_){
            throw StackUnderflow();
        }
        Node* temp = head_;
        head_ = head_->next_;
        T element = temp->data_;
        delete temp;
        return element;
    }

    bool isEmpty()override{
        return head_ == nullptr;
    }
};

#endif