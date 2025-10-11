#ifndef LINKED_LIST_LOCKED_H
#define LINKED_LIST_LOCKED_H

#include <iostream>

class Node{
public:
    int value;
    Node* next;

    Node(int value): value(value), next(nullptr){};
};

class LinkedList{
    Node* head {nullptr};
    int size {0};

public:
    void insert(int value, int index);

    int find(int index);

    void del(int index);

    int getSize();

    void printList();

    ~LinkedList();
};

#endif