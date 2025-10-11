#ifndef ABSTRACT_LIST_LOCKED_H
#define ABSTRACT_LIST_LOCKED_H

class AbstractListLocked{
public:
    virtual void insert(int value, int index) = 0;
    virtual int getSize() = 0;
    virtual void del(int index) = 0;
    virtual int find(int index) = 0;
};

#endif