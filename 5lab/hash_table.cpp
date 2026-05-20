#include "hash_table.h"
#include <cmath>
#include <stdexcept>
#include <iostream>


HashTable::HashTable(size_t size): size_(size), number_(0){
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

size_t HashTable::probe(size_t hash_value, size_t attemp)const{
    return (hash_value + (attemp*attemp)) % size_;
}

size_t HashTable::insert(double key){
    if((static_cast<double>(number_)/size_)>0.7) resize();
    size_t hash_value = hash(key);
    size_t deleted = size_;
    size_t i = 0;
    while(i<size_){
        size_t j = probe(hash_value, i);
        if(table_[j].status_ == OCCUPIED && table_[j].key_ == key){
            return j;
        }
        if(table_[j].status_ == DELETED){
            deleted = j;
        }
        if(table_[j].status_ == EMPTY){
            size_t pos = (deleted == size_)? j : deleted;
            table_[pos].key_ = key;
            table_[pos].status_ = OCCUPIED;
            ++number_;
            return pos;
        }
        ++i;
    }
    if (deleted != size_) {
        table_[deleted].key_ = key;
        table_[deleted].status_ = OCCUPIED;
        ++number_;
        return deleted;
    }

    throw std::overflow_error("Hash table overflow");
}

size_t HashTable::resize_insert(double key){
    size_t hash_value = hash(key);
    size_t deleted = size_;
    size_t i = 0;
    while(i<size_){
        size_t j = probe(hash_value, i);
        if(table_[j].status_ == OCCUPIED && table_[j].key_ == key){
            return j;
        }
        if(table_[j].status_ == DELETED){
            deleted = j;
        }
        if(table_[j].status_ == EMPTY){
            size_t pos = (deleted == size_)? j : deleted;
            table_[pos].key_ = key;
            table_[pos].status_ = OCCUPIED;
            ++number_;
            return pos;
        }
        ++i;
    }
    throw std::runtime_error("Resize error");
}

void HashTable::resize(){
    size_t oldSize = size_;
    Line* oldTable = table_;

    size_ *= 2;
    table_ = new Line[size_];
    number_ = 0;

    for (size_t i = 0; i<oldSize; ++i){
        if(oldTable[i].status_ == OCCUPIED){
            resize_insert(oldTable[i].key_);
        }
    }
    delete[] oldTable;
}

size_t HashTable::search(double key)const{
    size_t hash_value = hash(key);
    size_t i = 0;

    while(i<size_){
        size_t j = probe(hash_value, i);
        if(table_[j].status_ == EMPTY){
            return size_;
        }
        if(table_[j].status_ == OCCUPIED && table_[j].key_ == key){
            return j;
        }
        ++i;
    }
    return size_;
}

bool HashTable::remove(double key){
    size_t hash_value = hash(key);
    size_t i = 0;
    while(i<size_){
        size_t j = probe(hash_value, i);
        if(table_[j].status_ == EMPTY){
            return false;
        }
        if(table_[j].status_ == OCCUPIED && table_[j].key_ == key){
            table_[j].status_ = DELETED;
            --number_;
            return true;
        }
        ++i;
    }
    return false;
}

void HashTable::print()const{
    for(size_t i = 0; i< size_; ++i){
        if(table_[i].status_ ==OCCUPIED){
            std::cout<< "T["<< i << "] = " << table_[i].key_<<std::endl;
        }
    }
}