#ifndef SHELLING_H
#define SHELLING_H

#include "Interface_of_abilities.h"
#include "Playground.h"
#include <iostream>
#include <ctime>

class Shelling: public Interface_of_abilities{
public:
    bool perform_ability(Playground& playground);

    ~Shelling();
};


#endif