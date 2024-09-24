#pragma once
#include <iostream>
#include "Enum_arguments.h"

class Ship
{
private:
    Length_of_the_ship length;
    Statement_of_the_ship* segments;
    Location location_of_ship;

public:
    Ship(Length_of_the_ship p_length, Location p_location_of_ship);

    Ship(Length_of_the_ship p_length);

    Ship();

    ~Ship();

    void shoot_to_segment(int coordinate);

    Location get_location();

    void set_location(Location location);

    int get_length();

    Statement_of_the_ship* get_segments();

    void print_statement_of_ship();
};