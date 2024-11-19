#ifndef ADD_ABILITY_H
#define ADD_ABILITY_H

#include "Command_ability.h"
#include "Manager_of_abilities.h"
#include "Ability_maker.h"

class Add_ability: public Command_ability{
private:
    Manager_of_abilities& manager;

public:
    Add_ability(Manager_of_abilities& p_manager);

    void add_ability();
};

#endif