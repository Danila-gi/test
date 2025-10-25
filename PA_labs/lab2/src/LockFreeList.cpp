#include "LockFreeList.h"

std::pair<NodeLockFree*, NodeLockFree*> LockFreeList::find_nodes(int index) {
    NodeLockFree* prev = nullptr;
    NodeLockFree* curr = head.load(std::memory_order_acquire);
    
    for (int i = 0; i < index && curr != nullptr; i++) {
        prev = curr;
        curr = curr->next.load(std::memory_order_acquire);
    }
    
    return {prev, curr};
}

void LockFreeList::insert(int value, int index) {
    if (index < 0 || index > size.load(std::memory_order_relaxed)) {
        return;
    }

    NodeLockFree* new_node = new NodeLockFree(value);
    
    if (index == 0) {
        new_node->next.store(head.load(std::memory_order_acquire), std::memory_order_release);
        
        NodeLockFree* expected = head.load(std::memory_order_acquire);
        while (!head.compare_exchange_weak(expected, new_node, 
                                            std::memory_order_release,
                                            std::memory_order_relaxed)) {
            new_node->next.store(expected, std::memory_order_release);
        }
    } else {
        while (true) {
            auto [prev, curr] = find_nodes(index);
            
            if (!prev) {
                delete new_node;
                continue;
            }
            
            new_node->next.store(curr, std::memory_order_release);
            
            NodeLockFree* expected = curr;
            if (prev->next.compare_exchange_weak(expected, new_node,
                                                std::memory_order_release,
                                                std::memory_order_relaxed)) {
                break;
            }
        }
    }
    
    size.fetch_add(1, std::memory_order_relaxed);
}

int LockFreeList::find(int index) {
    if (index < 0 || index >= size.load(std::memory_order_acquire)) {
        return -1;
    }

    auto [prev, curr] = find_nodes(index);
    
    if (curr) {
        return curr->value;
    }
    return -1;
}

void LockFreeList::del(int index) {
    if (index < 0 || index >= size.load(std::memory_order_acquire)) {
        return;
    }

    if (index == 0) {
        NodeLockFree* old_head = head.load(std::memory_order_acquire);
        while (old_head && 
                !head.compare_exchange_weak(old_head, 
                                            old_head->next.load(std::memory_order_acquire),
                                            std::memory_order_release,
                                            std::memory_order_relaxed)) {
        }
        
        if (old_head) {
            delete old_head;
            size.fetch_sub(1, std::memory_order_relaxed);
            return;
        }
    } else {
        while (true) {
            auto [prev, curr] = find_nodes(index);
            
            if (!prev || !curr) {
                return;
            }
            
            NodeLockFree* next_node = curr->next.load(std::memory_order_acquire);
            
            NodeLockFree* expected = curr;
            if (prev->next.compare_exchange_weak(expected, next_node,
                                                std::memory_order_release,
                                                std::memory_order_relaxed)) {
                delete curr;
                size.fetch_sub(1, std::memory_order_relaxed);
                return;
            }
        }
    }
    
    return;
}

int LockFreeList::getSize() {
    return size.load(std::memory_order_acquire);
}

void LockFreeList::printList() {
    NodeLockFree* current = head.load(std::memory_order_acquire);
    while (current != nullptr) {
        std::cout << current->value;
        if (current->next.load(std::memory_order_acquire) != nullptr) {
            std::cout << " ==> ";
        }
        current = current->next.load(std::memory_order_acquire);
    }
    std::cout << " ==> end" << std::endl;
}

LockFreeList::~LockFreeList(){
    NodeLockFree* current = head.load(std::memory_order_relaxed);
    while (current != nullptr) {
        NodeLockFree* next = current->next.load(std::memory_order_relaxed);
        delete current;
        current = next;
    }
}
