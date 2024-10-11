#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>

enum Orientation{
    Horizontal,
    Vertical
};

enum Length_of_the_ship{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4
};

enum Statement_of_the_ship{
    INTACT = 2,
    DAMAGED = 1,
    DESTROYED = 0
};

class Ship
{
private:
    Length_of_the_ship length;
    std::vector<Statement_of_the_ship> segments;
    Orientation orientation_of_ship;

public:
    Ship(Length_of_the_ship p_length, Orientation p_orientation_of_ship);

    Ship(Length_of_the_ship p_length);

    Ship();

    void shoot_to_segment(int coordinate);

    Orientation get_orientation() const;

    void set_orientation(Orientation orientation);

    int get_length() const;

    Statement_of_the_ship get_segment_by_index(int index) const;

    void print_statement_of_ship();
};

#endif