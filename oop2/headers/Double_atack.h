#ifndef DOUBLE_ATACK_H
#define DOUBLE_ATACK_H

#include "Interface_of_abilities.h"

class Double_atack: public Interface_of_abilities{
public:
    void perform_ability(Playground& playground) override;

    void perform_ability(Playground& playground, Coords coords) override;
};


#endif