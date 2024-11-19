#ifndef PAINT_H
#define PAINT_H

#include <iostream>
#include "Playground.h"
#include "Manager_of_abilities.h"

class Paint{
public:
    Paint() = default;

    void print_your_ground(Playground& p);
    void print_enemy_ground(Playground& p);

    void print_list_of_abilities(Manager_of_abilities& manager);
};

#endif