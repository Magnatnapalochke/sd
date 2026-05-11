#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class List {
private:
    struct Node {
        T data_;
        Node* next_;
        Node* prev_;
        
        Node(const T& value) : data_(value), next_(nullptr), prev_(nullptr) {}
    };
    
    Node* head_;
    Node* tail_;
    size_t size_;
    
public:
    List() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        Node* current = other.head_;
        while (current) {
            push_back(current->data_);
            current = current->next_;
        }
    }
    
    ~List() {
        clear();
    }
    
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node* current = other.head_;
            while (current) {
                push_back(current->data_);
                current = current->next_;
            }
        }
        return *this;
    }
    
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head_) {
            head_ = tail_ = newNode;
        } else {
            tail_->next_ = newNode;
            newNode->prev_ = tail_;
            tail_ = newNode;
        }
        size_++;
    }
    
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (!head_) {
            head_ = tail_ = newNode;
        } else {
            newNode->next_ = head_;
            head_->prev_ = newNode;
            head_ = newNode;
        }
        size_++;
    }
    
    void pop_back() {
        if (tail_) {
            Node* toDelete = tail_;
            tail_ = tail_->prev_;
            if (tail_) {
                tail_->next_ = nullptr;
            } else {
                head_ = nullptr;
            }
            delete toDelete;
            size_--;
        }
    }
    
    void pop_front() {
        if (head_) {
            Node* toDelete = head_;
            head_ = head_->next_;
            if (head_) {
                head_->prev_ = nullptr;
            } else {
                tail_ = nullptr;
            }
            delete toDelete;
            size_--;
        }
    }
    
    void remove(const T& value) {
        Node* current = head_;
        while (current) {
            if (current->data_ == value) {
                if (current->prev_) {
                    current->prev_->next_ = current->next_;
                } else {
                    head_ = current->next_;
                }
                
                if (current->next_) {
                    current->next_->prev_ = current->prev_;
                } else {
                    tail_ = current->prev_;
                }
                
                Node* toDelete = current;
                current = current->next_;
                delete toDelete;
                size_--;
            } else {
                current = current->next_;
            }
        }
    }
    
    void clear() {
        while (head_) {
            Node* toDelete = head_;
            head_ = head_->next_;
            delete toDelete;
        }
        tail_ = nullptr;
        size_ = 0;
    }
    
    bool contains(const T& value) const {
        Node* current = head_;
        while (current) {
            if (current->data_ == value) {
                return true;
            }
            current = current->next_;
        }
        return false;
    }
    
    T& front() {
        if (!head_) throw std::runtime_error("List is empty");
        return head_->data_;
    }
    
    const T& front() const {
        if (!head_) throw std::runtime_error("List is empty");
        return head_->data_;
    }
    
    T& back() {
        if (!tail_) throw std::runtime_error("List is empty");
        return tail_->data_;
    }
    
    const T& back() const {
        if (!tail_) throw std::runtime_error("List is empty");
        return tail_->data_;
    }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    T get(size_t index) const {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head_;
        for (size_t i = 0; i < index; i++) {
            current = current->next_;
        }
        return current->data_;
    }
};

#endif