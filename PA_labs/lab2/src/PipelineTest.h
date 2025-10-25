#ifndef PIPELINE_H
#define PIPELINE_H

#include "AbstractListLocked.h"
#include "NodeMutex.h"
#include <thread>
#include <iostream>
#include <random>

enum Operation : int{
    INSERT,
    DELETE,
    FIND
};

class PipelineTest {
    int readersCount;
    int writersCount;
    AbstractListLocked* mList;

public:
    PipelineTest(AbstractListLocked* list, int readersCount, int writersCount, int sizeList);
    void thread(Operation operation);
    void runTest();
};

#endif