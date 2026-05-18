#include "hash_table.h"
#include <cmath>


HashTable::HashTable(size_t size): size_(size){
    table_ = new Line[size_];
}

HashTable::~HashTable(){
    delete[] table_;
}

size_t HashTable::hash(const double key)const{
    const double a = 0.6180339887498949;

    double intPart;
    double fracPart = std::modf(key*a, &intPart);

    if(fracPart<0) fracPart+=1.0;

    return static_cast<size_t>(std::floor(fracPart*size_));
}

size_t HashTable::probe(size_t hash_value, size_t attemp){
    return (hash_value + attemp*attemp) & size_;
}

size_t HashTable::insert(double key){
    size_t hash_value = hash(key);
    size_t i = 0;
    while(i<size_){
        size_t j = probe(hash_value, i);
        if(table_[j].status_ != OCCUPIED){
            table_[j].key_ = key;
            return j;
        }
        ++i;
    }
}