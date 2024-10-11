#ifndef SHELLING_H
#define SHELLING_H

#include "Interface_of_abilities.h"
#include <iostream>
#include <ctime>

class Shelling: public Interface_of_abilities{
public:
    void perform_ability(Playground& playground) override;

    void perform_ability(Playground& playground, Coords coord) override;
};


#endif