#pragma once
#include <iostream>
#include "Ship.h"
#include "Enum_arguments.h"
#include <vector>

class Manager_of_ships
{
private:
    int count = 0;
    std::vector<Ship*> ships;

public:
    Manager_of_ships(int ships_count, Length_of_the_ship* sizes);

    ~Manager_of_ships();

    Manager_of_ships();

    std::vector<Ship*> get_arr_of_ships();

    int get_count();

    void add_ship(Length_of_the_ship length, Location location);

    void add_ship(Ship* ship);

    void remove_ship(int index);

    void print_ships();
};