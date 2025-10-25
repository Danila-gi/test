#ifndef FINE_LIST_LOCKED_H
#define FINE_LIST_LOCKED_H

#include <iostream>
#include <mutex>
#include <atomic>
#include "AbstractListLocked.h"
#include "NodeMutex.h"

class FineGrained : public AbstractListLocked{
    NodeMutex* head {nullptr};
    std::mutex head_mutex;
    std::atomic<int> size {0};

public:
    void insert(int value, int index);

    int find(int index);
    void del(int index);

    int getSize();

    void printList();
};

#endif