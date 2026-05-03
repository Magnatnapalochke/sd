#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <cstddef>

struct Record{
    double key_;
    double data_;
};

class HashTable{
public:
    HashTable(size_t  size);
    ~HashTable();
    HashTable(const HashTable& other) = delete;
    HashTable(HashTable&& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;
    HashTable&& operator=(HashTable&& other) = delete;
private:
    enum Status{EMPTY, OCCUPIED, DELETED};
    struct Line{
        Record* record_;
        Status status_;
    };
    size_t size_;
    Line table_;
    size_t number_;
};

#endif