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