#include <iostream>
#include <thread>
#include <vector>
#include "PipelineTest.h"
#include "CoarseGrainedLock.h"
#include "FineGrainedLock.h"
#include "LockFreeList.h"
#include "tests.cpp"

int main(){
    
    
    for (int i = 0; i <= 10; i++){
        for (int j = 0; j < 3; j++){
            FineGrained* listFine = new FineGrained();
            PipelineTest testFine(listFine, i * 10, (10 - i) * 10, 3000);
            std::cout << "For Fine:" << std::endl;
            testFine.runTest();
            
            delete listFine;
            std::this_thread::sleep_for(std::chrono::seconds(3));

            CoarseGrained* listCoarse = new CoarseGrained();
            PipelineTest testCoarse(listCoarse, i * 10, (10 - i) * 10, 3000);
            std::cout << "For Coarse:" << std::endl;
            testCoarse.runTest();
            
            delete listCoarse;
            std::this_thread::sleep_for(std::chrono::seconds(3));


            LockFreeList* listLockFree = new LockFreeList();
            PipelineTest testLockFree(listLockFree, i * 10, (10 - i) * 10, 3000);
            std::cout << "For LockFree:" << std::endl;
            testLockFree.runTest();
            
            delete listLockFree;
            std::this_thread::sleep_for(std::chrono::seconds(3));

            std::cout << "================" << std::endl;
        }
    }





    //---------Tests---------//
    /*LockFreeList* list = new LockFreeList();
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 5; i++) {
        threads.emplace_back([list, i](){
            for (int j = 0; j < 10; j++) {
                list->insert(i * 100 + j, 0);
                list->del(0);
            }
        });
    }
    
    for (auto& t : threads){
        t.join();
    }
    
    list->printList();
    delete list;*/


    return 0;
}