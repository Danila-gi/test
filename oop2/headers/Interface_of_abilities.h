#ifndef INTERFACE_OF_ABILITIES_H
#define INTERFACE_OF_ABILITIES_H

#include <iostream>
#include "Playground.h"

class Interface_of_abilities{
public:
    virtual bool perform_ability(Playground& playground) = 0;
    
    virtual ~Interface_of_abilities() = 0;
};


#endif