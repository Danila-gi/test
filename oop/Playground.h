#pragma once
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
    Statment_of_the_coord** arr_of_ground;
    Manager_of_ships* list_of_ships;
    std::map<Ship*, std::vector<Coords>>coords_of_ship;

public:
    Playground(int p_width, int p_heigth);

    Playground();

    ~Playground();

    bool check_point(Coords coord);

    void set_manager_with_coords(Manager_of_ships* manager, std::vector<Coords> coords);

    void get_ship(Ship* ship, Coords coord, Location location);

    Manager_of_ships* return_manager();

    void put_new_ships(Ship* ship);

    void shoot(Coords coord);

    void print_ground();
};