#ifndef GET_COORDS_H
#define GET_COORDS_H

#include "Command_coords.h"
#include "Playground.h"

class Get_coords: public Command_coords{
private:
    Coords& coords;

public:
    Get_coords(Coords& p_coords);

    Coords get_coords();
};

#endif