#include "FineGrainedLock.h"

void FineGrained::insert(int value, int index){
    if (index < 0 || index > size){
        return;
    }

    NodeMutex* new_node = new NodeMutex(value);

    if (index == 0){
        std::lock_guard<std::mutex> head_lock(head_mutex);
        new_node->next = head;
        head = new_node;
        size++;
        return;
    }

    std::unique_lock<std::mutex> head_lock(head_mutex);

    int i = 1;
    NodeMutex* current = head;
    current->mutex.lock();
    head_lock.unlock();
    if (current->next){
        current->next->mutex.lock();
    }

    while (current->next){
        if (i == index){
            break;
        }
        i++;
        current->mutex.unlock();
        current = current->next;
        if (current->next){
            current->next->mutex.lock();
        }
    }

    new_node->next = current->next;
    current->next = new_node;

    current->mutex.unlock();
    if (new_node->next){
        new_node->next->mutex.unlock();
    }
    size++;
}

int FineGrained::find(int index){
    if (index < 0 || index >= size){
        return -1;
    }

    int i = 0;

    std::unique_lock<std::mutex> head_lock(head_mutex);
    NodeMutex* current = head;
    current->mutex.lock();
    head_lock.unlock();

    while (current){
        if (i == index){
            current->mutex.unlock();
            return current->value;
        }
        i++;
        if (current->next){
            current->next->mutex.lock();
        }
        current->mutex.unlock();
        current = current->next;
    }
    current->mutex.unlock();
    return -1;
}

void FineGrained::del(int index){
    if (index < 0 || index >= size){
        return;
    }
    if (index == 0){
        std::lock_guard<std::mutex> head_lock(head_mutex);
        NodeMutex* to_delete = head; 
        head = head->next;
        delete to_delete;
        size--;
        return;
    }

    std::unique_lock<std::mutex> head_lock(head_mutex);

    int i = 1;
    NodeMutex* current = head;
    current->mutex.lock();
    head_lock.unlock();

    if (current->next){
        current->next->mutex.lock();
    }
    while (current->next){
        if (index == i){
            NodeMutex* to_delete = current->next;
            if (current->next->next){
                current->next->next->mutex.lock();
            }
            current->mutex.unlock(); 
            current->next = current->next->next;
            if (current->next){
                current->next->mutex.unlock();
            } 
            size--;
            to_delete->mutex.unlock();
            delete to_delete;
            return;
        }
        i++;
        current->mutex.unlock();
        current = current->next;
        if (current->next){
            current->next->mutex.lock();
        }
    }
    current->mutex.unlock();
}

int FineGrained::getSize(){ return size; }

void FineGrained::printList(){
    std::unique_lock<std::mutex> head_lock(head_mutex);
    if (!head){
        std::cout << "empty" << std::endl;
        return;
    }
    NodeMutex* current = head;
    current->mutex.lock();
    head_lock.unlock();
    while (current)
    {
        std::cout << current->value << " ==> ";
        if (current->next){
            current->next->mutex.lock();
        }
        current->mutex.unlock();
        current = current->next;
    }
    std::cout << "end" << std::endl;
    
}