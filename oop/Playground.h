#pragma once
#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Enum_arguments.h"

class Playground{
private:
    int width;
    int height;
    Statment_of_the_coord** arr_of_ground;
    Manager_of_ships* list_of_ships;
    Coords* arr_of_coords;

public:
    Playground(int p_width, int p_heigth);

    Playground();

    void set_manager(Manager_of_ships* manager);

    void set_coords(Coords* coords);

    void get_ship(Ship* ship, Coords coord);

    void put_new_ships(Ship* ship, Coords coord);

    void print_ground();
};