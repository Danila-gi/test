#ifndef DOUBLE_ATACK_H
#define DOUBLE_ATACK_H

#include "Interface_of_abilities.h"
#include "Playground.h"

class Double_atack: public Interface_of_abilities{
private:
    Coords coords;

public:
    Double_atack();

    Double_atack(Coords coords);

    bool perform_ability(Playground& playground);
};


#endif