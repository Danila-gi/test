#include "PipelineTest.h"

PipelineTest::PipelineTest(AbstractListLocked* list, int readersCount, int writersCount, int sizeList):readersCount(readersCount), writersCount(writersCount){
    mList = list;
    for (int i = 0; i < sizeList; i++){
        mList->insert(i, i);
    }
}

void PipelineTest::thread(Operation operation){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, mList->getSize() - 1);
    int index = distrib(gen);

    if (operation == FIND){
        mList->find(index);
    }
    else if (operation == DELETE){
        mList->del(index);
    }
    else if (operation == INSERT){
        mList->insert(999, index);
    }
}

void PipelineTest::runTest(){
    std::vector<std::thread> writers;
    std::vector<std::thread> readers;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < writersCount; i++){
        if (i < writersCount / 2){
            writers.emplace_back(&PipelineTest::thread, this, INSERT);
        }
        else {
            writers.emplace_back(&PipelineTest::thread, this, DELETE);
        }
    }

    for (int i = 0; i < readersCount; i++){
        readers.emplace_back(&PipelineTest::thread, this, FIND);
    }

    for (auto& th: writers){
        th.join();
    }
    for (auto& th: readers){
        th.join();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "Results for " << writersCount << " writers and " << readersCount << " readers:" << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
}