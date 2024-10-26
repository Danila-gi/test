#ifndef ADD_ABILITY_H
#define ADD_ABILITY_H

#include "Command.h"
#include "Manager_of_abilities.h"

class Add_ability: public Command{
private:
    Manager_of_abilities& manager;

public:
    Add_ability(Manager_of_abilities& p_manager);

    void execute();
};

#endif