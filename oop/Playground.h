#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Enum_arguments.h"
#include <map>
#include <vector>

class Playground{
private:
    int width;
    int height;
    Statement_of_the_coord** arr_of_ground;
    std::map<Ship*, std::vector<Coords>>coords_of_ship;

    void put_new_ships(Ship* ship);
    bool check_ship(Ship* ship, Coords coord);

public:
    Playground(int p_width, int p_heigth);

    Playground();

    ~Playground();

    bool check_point(Coords coord);

    void add_ship(Ship* ship, Coords coord);

    void shoot(Coords coord);

    void print_ground();

    Playground(const Playground &obj);
    Playground(Playground &&obj);

    Playground& operator=(const Playground &obj);
    Playground& operator=(Playground &&obj);
};

#endif