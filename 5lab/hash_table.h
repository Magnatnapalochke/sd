#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <cstddef>

class HashTable{
public:
    HashTable(size_t  size);
    ~HashTable();
    HashTable(const HashTable& other) = delete;
    HashTable(HashTable&& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;
    HashTable&& operator=(HashTable&& other) = delete;

    size_t insert(double key);
    void resize();    size_t search(double key)const;
    bool remove(double key);
    void print()const;
private:
    enum Status{EMPTY, OCCUPIED, DELETED};
    struct Line{
        double key_;
        double data_;
        Status status_;
        Line():key_(0.0), data_(0.0), status_(EMPTY) {};
        Line(const double& key, double data): key_(key), 
        data_(data), status_(OCCUPIED){};
    };
    size_t size_;
    Line* table_ = nullptr;
    size_t number_;

    size_t resize_insert(double key);
    size_t hash(const double key)const;
    size_t probe(size_t hash_value, size_t attemp)const;

};

#endif