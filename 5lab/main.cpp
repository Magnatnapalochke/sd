#include "hash_table.h"
#include <iostream>
#include <cassert>
#include <cmath>



void testBasicOperations() {
    HashTable ht(5);
    
    size_t idx1 = ht.insert(10.5);
    size_t idx2 = ht.insert(20.7);
    size_t idx3 = ht.insert(30.9);
    
    assert(ht.search(10.5) == idx1);
    assert(ht.search(20.7) == idx2);
    assert(ht.search(30.9) == idx3);
    assert(ht.search(99.9) == 5);
    
    std::cout << "Insert and search: OK" << std::endl;
}

void testDuplicateHandling() {

    HashTable ht(10);
    
    size_t first = ht.insert(42.0);
    size_t second = ht.insert(42.0);
    
    assert(first == second);
    std::cout << "Duplicate prevention: OK" << std::endl;
}

void testRemoveAndSearch() {

    HashTable ht(10);
    
    ht.insert(1.1);
    ht.insert(2.2);
    ht.insert(3.3);
    
    assert(ht.remove(2.2) == true);
    assert(ht.search(2.2) == 10);
    assert(ht.search(1.1) != 10);
    assert(ht.search(3.3) != 10);
    assert(ht.remove(9.9) == false);
    
    std::cout << "Remove and search: OK" << std::endl;
}

void testCollisionHandling() {

    HashTable ht(7);
    
    ht.insert(5.0);
    ht.insert(12.0);
    ht.insert(19.0);
    ht.insert(26.0);
    
    assert(ht.search(5.0) != 7);
    assert(ht.search(12.0) != 7);
    assert(ht.search(19.0) != 7);
    assert(ht.search(26.0) != 7);
    
    ht.print();
    std::cout << "Collision handling: OK" << std::endl;
}

void testResize() {

    HashTable ht(4);
    
    for (int i = 0; i < 50; i++) {
        ht.insert(i * 1.5);
    }
    
    for (int i = 0; i < 50; i++) {
        assert(ht.search(i * 1.5) != 4);
    }
    
    std::cout << "Resize: OK" << std::endl;
}

void testDeleteThenInsert() {

    HashTable ht(10);
    
    ht.insert(100);
    ht.insert(200);
    ht.insert(300);
    
    ht.remove(200);
    size_t newIdx = ht.insert(400);
    
    assert(ht.search(100) != 10);
    assert(ht.search(300) != 10);
    assert(ht.search(400) != 10);
    assert(ht.search(200) == 10);
    
    std::cout << "Delete then insert: OK" << std::endl;
}

void testSearchAfterDelete() {
    HashTable ht(10);
    
    ht.insert(5.0);
    ht.insert(15.0);
    ht.insert(25.0);
    
    ht.remove(15.0);
    
    assert(ht.search(25.0) != 10);
    std::cout << "Probe chain integrity: OK" << std::endl;
}

void testLargeNumberOfElements() {
    HashTable ht(100);
    
    for (int i = 0; i < 500; i++) {
        ht.insert(i * 0.5);
    }
    int found = 0;
    for (int i = 0; i < 500; i++) {
        if (ht.search(i * 0.5) != 100) {
            found++;
        }
    }
    
    assert(found == 500);
    std::cout << "Large data set (500 elements): OK" << std::endl;
}

int main() {

    
    try {
        testBasicOperations();
        testDuplicateHandling();
        testRemoveAndSearch();
        testCollisionHandling();
        testResize();
        testDeleteThenInsert();
        testSearchAfterDelete();
        testLargeNumberOfElements();
        
        std::cout << "Hash table implementation is correct!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "\nERROR: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}