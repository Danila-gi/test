#ifndef INTERFACE_OF_ABILITIES_H
#define INTERFACE_OF_ABILITIES_H

#include <iostream>
#include "Playground.h"

class Interface_of_abilities{
public:
    virtual void perform_ability(Playground& playground) {};
    
    virtual void perform_ability(Playground& playground, Coords coords) {};

    virtual ~Interface_of_abilities() {};
};


#endif