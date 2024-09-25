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
    Manager_of_ships& list_of_ships;
    std::map<int, std::vector<Coords>>coords_of_ship;

    void put_new_ships(int index);
    bool check_ship(Ship ship, int index, Coords coord);

public:
    Playground(int p_width, int p_heigth, Manager_of_ships& manager, std::vector<Coords> coords);

    Playground();

    ~Playground();

    bool check_point(Coords coord);

    void add_ship(Length_of_the_ship length, Location location, Coords coord);

    Manager_of_ships return_manager() const;

    void shoot(Coords coord);

    void print_ground();

    Playground(const Playground &obj);
    Playground(Playground &&obj);

    Playground& operator=(const Playground &obj);
    Playground& operator=(Playground &&obj);
};

#endif