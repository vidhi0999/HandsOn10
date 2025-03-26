#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct Node {
    int key;
    int value;
    Node* next;
    Node* prev;

    Node(int k, int v);
};

class DoublyLinkedList {

   

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    Node* head;
    Node* tail;
    int size;
    int getSize() const;
    void insertFront(int key, int value);
    bool remove(int key);
    Node* find(int key) const;
};

class HashTable {
private:
    DoublyLinkedList** table;
    int capacity;
    int size;

    int hashFunction(int key) const;
    void resize(int newCapacity);

public:
    HashTable(int initialCapacity);
    ~HashTable();

    void insert(int key, int value);
    int* get(int key) const;
    bool remove(int key);
    int getSize() const;
    int getCapacity() const;
};

#endif // HASH_TABLE_H