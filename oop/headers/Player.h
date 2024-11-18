#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Playground.h"
#include "Manager_of_abilities.h"
#include "Manager_of_ships.h"
#include "Get_coords.h"
#include "Add_ability.h"

class Player{
private:
    Get_coords* get_cor;
    Ability_maker* maker;
    Add_ability* add_abil;

    Playground* playground;
    Manager_of_abilities* ability_manager;
    Manager_of_ships* ships_manager;
    Coords coords_for_scanner;
public:
    Player();

    void perform_shoot(Playground& enemy_playground, Coords coord);

    void use_ability(Playground& enemy_playground);

    Playground& get_playground();

    void put_ships();
};

#endif