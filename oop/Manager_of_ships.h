#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "Ship.h"
#include "Enum_arguments.h"
#include <vector>

class Manager_of_ships
{
private:
    std::vector<Ship> ships;

public:
    Manager_of_ships(int ships_count, Length_of_the_ship sizes[]);

    Manager_of_ships();

    Ship& get_ship(int index);

    int get_count_of_ships() const;

    void add_ship(Length_of_the_ship length, Location location);

    void set_location_for_the_ship(int index_of_ship, Location location);

    void remove_ship(int index);

    void print_ships();
};

#endif