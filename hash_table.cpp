#include "hash_table.h"
#include <cmath> // For floor
#include <iostream> // For potential debugging output

Node::Node(int k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

int DoublyLinkedList::getSize() const {
    return size;
}

void DoublyLinkedList::insertFront(int key, int value) {
    Node* newNode = new Node(key, value);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

bool DoublyLinkedList::remove(int key) {
    Node* current = head;
    while (current) {
        if (current->key == key) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

Node* DoublyLinkedList::find(int key) const {
    Node* current = head;
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

HashTable::HashTable(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
    table = new DoublyLinkedList*[capacity]();
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < capacity; ++i) {
        if (table[i]) {
            delete table[i]; // Destructor of DoublyLinkedList will clean up nodes
        }
    }
    delete[] table;
}

int HashTable::hashFunction(int key) const {
    double A = 0.6180339887; // Golden ratio
    double val = key * A;
    val = val - floor(val);
    return floor(val * capacity);
}

void HashTable::resize(int newCapacity) {
    DoublyLinkedList** newTable = new DoublyLinkedList*[newCapacity]();
    int oldCapacity = capacity;
    capacity = newCapacity;

    for (int i = 0; i < oldCapacity; ++i) {
        DoublyLinkedList* list = table[i];
        Node* current = list ? list->head : nullptr;
        while (current) {
            Node* next = current->next;
            int newIndex = hashFunction(current->key);
            if (!newTable[newIndex]) {
                newTable[newIndex] = new DoublyLinkedList();
            }
            newTable[newIndex]->insertFront(current->key, current->value);
            current = next;
        }
        if (list) {
            delete list;
        }
    }
    delete[] table;
    table = newTable;
}

void HashTable::insert(int key, int value) {
    int index = hashFunction(key);
    if (!table[index]) {
        table[index] = new DoublyLinkedList();
    }
    table[index]->insertFront(key, value);
    size++;

    if (static_cast<double>(size) / capacity > 1.0) {
        resize(capacity * 2);
    }
}

int* HashTable::get(int key) const {
    int index = hashFunction(key);
    if (table[index]) {
        Node* node = table[index]->find(key);
        if (node) {
            return &node->value;
        }
    }
    return nullptr; // Key not found
}

bool HashTable::remove(int key) {
    int index = hashFunction(key);
    if (table[index] && table[index]->remove(key)) {
        size--;
        if (capacity > 10 && static_cast<double>(size) / capacity < 0.25) {
            resize(capacity / 2);
        }
        return true;
    }
    return false;
}

int HashTable::getSize() const {
    return size;
}

int HashTable::getCapacity() const {
    return capacity;
}