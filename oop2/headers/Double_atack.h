#ifndef DOUBLE_ATACK_H
#define DOUBLE_ATACK_H

#include "Interface_of_abilities.h"
#include "Playground.h"

class Double_atack: public Interface_of_abilities{
public:
    Double_atack() = default;

    bool perform_ability(Playground& playground);

    ~Double_atack() = default;
};


#endif