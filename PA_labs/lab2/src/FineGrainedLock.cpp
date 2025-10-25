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

        NodeMutex* next_node = current->next;
        if (next_node->next){
            next_node->next->mutex.lock(); 
        }

        current->mutex.unlock();
        current = next_node;
    }

    new_node->next = current->next;
    current->next = new_node;

    if (new_node->next){
        new_node->next->mutex.unlock();
    }
    current->mutex.unlock();
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
            int val= current->value;
            current->mutex.unlock();
            return val;
        }
        i++;
        if (current->next){
            current->next->mutex.lock();
        }
        current->mutex.unlock();
        current = current->next;
    }
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
            if (to_delete->next){
                to_delete->next->mutex.lock();
            }
            current->next = to_delete->next;
            if (current->next){
                current->next->mutex.unlock();
            } 
            to_delete->mutex.unlock();
            current->mutex.unlock(); 
            size--;
            delete to_delete;
            return;
        }
        i++;
        NodeMutex* next_node = current->next;
        if (next_node->next){
            next_node->next->mutex.lock(); 
        }

        current->mutex.unlock();
        current = next_node;
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