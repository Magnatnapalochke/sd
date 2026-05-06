#ifndef QUEUE_VECTOR_H
#define QUEUE_VECTOR_H

#include "queue.h"
#include "queue_exceptions.h"

template<typename T>
class QueueVector : public Queue<T>{
public:
    QueueVector(size_t capacity = 4): capacity_(capacity),
    head_(0), tail_(0), count_(0){
        buffer_ = new T[capacity];
    }

    ~QueueVector(){
        delete[] buffer_;
    }

    void enQueue(const T& element) override{
        if(capacity_ == count_) resize();
        buffer_[tail_] = element;
        tail_ = (tail_ + 1) % capacity_;
        count_++;
    }

    T deQueue() override{
        if(isEmpty()){
            throw QueueOverflow();
        }

        T value = buffer_[head_];
        head_ = (head_ + 1) % capacity_ ;
        --count_;
        
        return value;
    }

    bool isEmpty()override{
        return tail_==head_;
    }

private:
    T* buffer_;
    size_t head_;
    size_t tail_;
    size_t capacity_;
    size_t count_;

    void resize(){
        size_t new_capacity = (capacity_ == 0)? 1 : capacity_ *=2;
        T* new_buffer = new T[new_capacity];
        for(size_t i = 0; i<count_; ++i){
            new_buffer[i] = buffer_[(head_+i)%capacity_];
        }

        delete[] buffer_;
        buffer_ = new_buffer;
        head_ = 0;
        tail_ = count_;
        capacity_ = new_capacity;
    }
};

#endif