#include "CoarseGrainedLock.h"

CoarseGrained::CoarseGrained(){
    list = new LinkedList();
}

void CoarseGrained::insert(int value, int index){
    std::lock_guard<std::mutex> guard(mutex);
    list->insert(value, index);
}

int CoarseGrained::find(int index){
    std::lock_guard<std::mutex> guard(mutex);
    int num = list->find(index);
    return num;
}

void CoarseGrained::del(int index){
    std::lock_guard<std::mutex> guard(mutex);
    list->del(index);
}

void CoarseGrained::printList(){
    std::lock_guard<std::mutex> guard(mutex);
    list->printList();
}

int CoarseGrained::getSize() {
    std::lock_guard<std::mutex> guard(mutex);
    return list->getSize();
}

CoarseGrained::~CoarseGrained(){
    delete list;
}