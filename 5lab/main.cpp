#include "hash_table.h"
#include <iostream>
#include <cassert>

void testAll() {
    HashTable ht(5);
    
    // Test insert and search
    size_t i1 = ht.insert(10);
    size_t i2 = ht.insert(20);
    assert(ht.search(10) == i1);
    assert(ht.search(20) == i2);
    assert(ht.search(30) == 5);  // not found
    
    // Test duplicate
    size_t i3 = ht.insert(10);
    assert(i1 == i3);
    
    // Test remove
    ht.remove(10);
    assert(ht.search(10) == 5);  // not found
    assert(ht.search(20) != 5);  // still there
    
    // Test resize
    for (int i = 0; i < 20; i++) {
        ht.insert(i * 3.14);
    }
    
    // Verify all inserted
    for (int i = 0; i < 20; i++) {
        assert(ht.search(i * 3.14) != 5);
    }
    
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testAll();
    return 0;
}