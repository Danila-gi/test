#ifndef COARSE_LIST_LOCKED_H
#define COARSE_LIST_LOCKED_H

#include <thread>
#include <mutex>
#include "LinkedList.h"
#include "AbstractListLocked.h"

class CoarseGrained : public AbstractListLocked{
private:
    LinkedList* list {nullptr};
    std::mutex mutex;

public:
    CoarseGrained();

    void insert(int value, int index);

    int find(int index);

    void del(int index);
    void printList();

    int getSize();

    ~CoarseGrained();
};

#endif