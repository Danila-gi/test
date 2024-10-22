#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include "Interface_of_abilities.h"
#include "Playground.h"

class Scanner: public Interface_of_abilities{
private:
    Coords coords;

public:
    Scanner();

    Scanner(Coords coords);

    bool perform_ability(Playground& playground);

    ~Scanner() = default;
};


#endif