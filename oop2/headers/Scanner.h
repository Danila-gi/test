#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include "Interface_of_abilities.h"

class Scanner: public Interface_of_abilities{
public:
    void perform_ability(Playground& playground) override;

    void perform_ability(Playground& playground, Coords coords) override;
};


#endif