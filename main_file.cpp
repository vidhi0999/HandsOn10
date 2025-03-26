#include "hash_table.h"
#include "hash_table.cpp"
#include <iostream>

int main() {
    HashTable ht;

    ht.insert(1, 100);
    ht.insert(5, 500);
    ht.insert(11, 1100); // Might collide with 1

    std::cout << "Size: " << ht.getSize() << ", Capacity: " << ht.getCapacity() << std::endl;

    int* value = ht.get(5);
    if (value) {
        std::cout << "Value for key 5: " << *value << std::endl;
    } else {
        std::cout << "Key 5 not found." << std::endl;
    }

    ht.remove(1);
    std::cout << "Size after removing 1: " << ht.getSize() << std::endl;

    value = ht.get(1);
    if (value) {
        std::cout << "Value for key 1: " << *value << std::endl;
    } else {
        std::cout << "Key 1 not found." << std::endl;
    }

    // You can add more test cases here to verify resizing, collisions, etc.

    return 0;
}