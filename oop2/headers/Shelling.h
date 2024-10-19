#ifndef SHELLING_H
#define SHELLING_H

#include "Interface_of_abilities.h"
#include "Playground.h"
#include <iostream>
#include <ctime>
#include <random>

class Shelling: public Interface_of_abilities{
private:
    std::mt19937 generator;
public:
    Shelling();

    bool perform_ability(Playground& playground);
};


#endif