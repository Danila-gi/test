#ifndef MANAGER_OF_ABILITIES_H
#define MANAGER_OF_ABILITIES_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Interface_of_abilities.h"
#include "Double_atack_builder.h"
#include "Shelling_builder.h"
#include "Scanner_builder.h"
#include "NoAbilitiesException.h"
#include "Command_ability.h"
#include "Command_coords.h"

class Manager_of_abilities{
private:
    std::vector<std::shared_ptr<Interface_of_builders>> vector_of_abilities;

    std::vector<std::shared_ptr<Interface_of_builders>> test_vector_for_getting_objects;

public:
    Manager_of_abilities(Command_coords* p_command);

    void push_ability(std::shared_ptr<Interface_of_builders> builder);

    std::shared_ptr<Interface_of_builders> get_ability();

    std::vector<std::shared_ptr<Interface_of_builders>> get_vector_of_three_abilities() const;
};

#endif