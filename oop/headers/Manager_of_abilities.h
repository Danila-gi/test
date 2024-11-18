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
#include "Ability_maker.h"

class Manager_of_abilities{
private:
    std::vector<std::shared_ptr<Interface_of_builders>> vector_of_abilities;

    Ability_maker& maker;

public:
    Manager_of_abilities() = default;
    Manager_of_abilities(Ability_maker& maker);

    void push_ability(Name_of_builder builder);

    std::shared_ptr<Interface_of_builders> get_ability();
};

#endif