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

    std::vector<Length_of_the_ship> length_of_ships;
    std::vector<Coords> coords_of_ships;
    std::vector<Orientation> orientations_of_ships;
public:
    Enemy();
    ~Enemy();

    void set_arguments(int height, int width, std::vector<Length_of_the_ship> length_of_ships);
    void perform_shoot(Playground& enemy_playground, Coords coord);

    void put_ships();

    void clear_ships();

    Playground& get_playground();

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};

#endif