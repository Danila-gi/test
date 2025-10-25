#include <iostream>
#include <thread>
#include <vector>
#include "PipelineTest.h"
#include "CoarseGrainedLock.h"
#include "FineGrainedLock.h"

void testConcurrentDelete() {
    FineGrained* list = new FineGrained();
    
    for (int i = 0; i < 10; i++) {
        list->insert(i, i);
    }
    
    std::vector<std::thread> threads;
    
    threads.emplace_back([list](){
        for (int i = 0; i < 3; i++) {
            list->del(0);
        }
    });
    
    threads.emplace_back([list](){
        for (int i = 0; i < 3; i++) {
            int size = list->getSize();
            if (size > 0) {
                list->del(size - 1);
            }
        }
    });
    
    for (auto& t : threads){
        t.join();
    }
    
    list->printList();
    delete list;
}

void testConcurrentInsertFind() {
    FineGrained* listFine = new FineGrained();
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++){
        threads.emplace_back([listFine, i](){
            for (int j = 0; j < 3; j++) {
                listFine->insert(i * 100 + j, listFine->getSize() - 1);
            }
            std::cout << listFine->find(i) << std::endl;
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    listFine->printList();

    delete listFine;
}

void testConcurrentInsertDelete() {
    FineGrained* list = new FineGrained();
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 5; i++) {
        threads.emplace_back([list, i](){
            for (int j = 0; j < 10; j++) {
                list->insert(i * 100 + j, j);
                list->del(0);
            }
        });
    }
    
    for (auto& t : threads){
        t.join();
    }
    
    list->printList();
    delete list;
}