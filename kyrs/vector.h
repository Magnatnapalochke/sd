#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class Vector{
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize(){
        size_t new_capacity = (capacity_ == 0)? 1 : (capacity_ *2);
        T* new_data = new T[new_capacity];
        for(size_t i = 0; i<size_; ++i){
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
public:
    Vector(): data_(nullptr), capacity_(0), size_(0){}

    Vector(size_t count, const T& value = T()) 
    : data_(new T[count]), capacity_(count), size_(count) {
        for (size_t i = 0; i < count; ++i) {
            data_[i] = value;
        }
    }
    
    Vector(const Vector& other) 
        : data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    ~Vector() {
        delete[] data_;
    }
    
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    T& operator[](size_t index) {
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        return data_[index];
    }
    
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = value;
    }
    
    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }
    
    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }
    
    void clear() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
    
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

};


#endif