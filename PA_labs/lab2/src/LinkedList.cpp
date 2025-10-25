#include "LinkedList.h"

void LinkedList::insert(int value, int index){
    if (index < 0 || index > size){
        return;
    }

    Node* new_node = new Node(value);

    if (index == 0){
        new_node->next = head;
        head = new_node;
        size++;
        return;
    }

    int i = 1;
    Node* current = head;

    while (current->next){
        if (i == index){
            break;
        }
        i++;
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    size++;
}

int LinkedList::find(int index){
    if (index < 0 || index >= size){
        return -1;
    }

    int i = 0;
    Node* current = head;
    while (current){
        if (i == index){
            return current->value;
        }
        i++;
        current = current->next;
    }
    return -1;
}

void LinkedList::del(int index){
    if (index < 0 || index >= size){
        return;
    }

    if (index == 0){
        Node* to_delete = head; 
        head = head->next;
        delete to_delete;
        size--;
        return;
    }

    int i = 1;
    Node* current = head;
    while (current->next){
        if (index == i){
            Node* to_delete = current->next; 
            current->next = current->next->next;
            size--;
            delete to_delete;
            return;
        }
        i++;
        current = current->next;
    }
}

int LinkedList::getSize(){ return size; }

void LinkedList::printList(){
    if (!head){
        std::cout << "empty" << std::endl;
        return;
    }
    Node* current = head;
    while (current)
    {
        std::cout << current->value << " ==> ";
        current = current->next;
    }
    std::cout << "end" << std::endl;
    
}

LinkedList::~LinkedList(){
    Node* current = head;
    while (current)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}