#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <iostream>
#include "Ship.h"
#include "Command_ability.h"
#include "ShipPlacmentException.h"
#include "AtackException.h"
#include <map>
#include <vector>

enum Statement_of_the_coord{
    UNKNOWN = 2,
    EMPTY = 1,
    SHIP = 0
};

typedef struct Coords{
    int x;
    int y;
}Coords;


class Playground{
private:
    int width;
    int height;
    int count_of_ships;
    Command_ability* command;
    Statement_of_the_coord** arr_of_ground;
    std::map<Ship*, std::vector<Coords>> coords_of_ship;

    using ShootFunc = void (Playground::*)(Coords coord, Ship* ship, int index);
    ShootFunc original_shoot;
    void shoot_with_double_damage(Coords coord, Ship* ship, int index);
    void shoot_with_one_damage(Coords coord, Ship* ship, int index);


    void put_new_ships(Ship* ship);
    bool check_ship(Ship* ship, Coords coord);
    bool check_point(Coords coord);
    void add_new_ability_for_skills();

public:
    Playground(int p_width, int p_heigth, Command_ability* p_command);

    Playground();

    ~Playground();

    void set_double_atack();

    void add_ship(Ship& ship, Coords coord);

    bool shoot(Coords coord);

    void print_ground();

    int get_ships_count() const;

    int get_width_of_playground() const;

    int get_height_of_playground() const;

    Statement_of_the_coord get_statment_of_coord(Coords coord) const;

    Playground(const Playground &obj);
    Playground(Playground &&obj);

    Playground& operator=(const Playground &obj);
    Playground& operator=(Playground &&obj);
};

#endif