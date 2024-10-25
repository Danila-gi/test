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
#include "Command.h"

class Manager_of_abilities: public Command{
private:
    std::vector<std::shared_ptr<Interface_of_builders>> vector_of_abilities;
    std::vector<std::shared_ptr<Interface_of_builders>> vector_for_add_new_ability;

public:
    Manager_of_abilities();

    void add_ability();

    std::shared_ptr<Interface_of_builders> get_ability();
};

#endif