#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "Playground.h"
#include "Manager_of_abilities.h"
#include "Manager_of_ships.h"
#include "Add_ability.h"

class Enemy{
private:
    Playground* playground;
    Manager_of_ships* ships_manager;
public:
    Enemy();

    void perform_shoot(Playground& enemy_playground, Coords coord);

    void put_ships();

    Playground& get_playground();
};

#endif