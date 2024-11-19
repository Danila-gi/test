#ifndef COMMAND_C_H
#define COMMAND_C_H

#include "Playground.h"

class Command_coords{
public:
    virtual Coords get_coords() = 0;
};

#endif