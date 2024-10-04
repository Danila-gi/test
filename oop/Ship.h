#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "Enum_arguments_for_ship.h"
#include <vector>

class Ship
{
private:
    Length_of_the_ship length;
    std::vector<Statement_of_the_ship> segments;
    Location location_of_ship;

public:
    Ship(Length_of_the_ship p_length, Location p_location_of_ship);

    Ship(Length_of_the_ship p_length);

    Ship();

    void shoot_to_segment(int coordinate);

    Location get_location() const;

    void set_location(Location location);

    int get_length() const;

    std::vector<Statement_of_the_ship> get_segments() const;

    void print_statement_of_ship();
};

#endif