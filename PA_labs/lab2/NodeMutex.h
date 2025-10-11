#ifndef NODEMUTEX_H
#define NODEMUTEX_H

#include <mutex>


class NodeMutex{
public:
    int value;
    NodeMutex* next;
    std::mutex mutex;

    NodeMutex(int value): value(value), next(nullptr){};
};

#endif