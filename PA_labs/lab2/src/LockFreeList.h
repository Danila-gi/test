#ifndef LOCK_FREE_H
#define LOCK_FREE_H

#include <iostream>
#include <mutex>
#include <atomic>
#include <optional>
#include "AbstractListLocked.h"

class NodeLockFree {
public:
    int value;
    std::atomic<NodeLockFree*> next;

    NodeLockFree(int value): value(value), next(nullptr) {}
};

class LockFreeList : public AbstractListLocked{
    std::atomic<NodeLockFree*> head {nullptr};
    std::atomic<int> size {0};

    std::pair<NodeLockFree*, NodeLockFree*> find_nodes(int index);

public:
    LockFreeList() = default;

    LockFreeList(const LockFreeList&) = delete;
    LockFreeList& operator=(const LockFreeList&) = delete;

    ~LockFreeList();

    void insert(int value, int index);

    int find(int index);
    void del(int index);

    int getSize();

    void printList();
};

#endif