#ifndef MANAGER_OF_ABILITIES_H
#define MANAGER_OF_ABILITIES_H

#include <iostream>
#include <vector>
#include "Interface_of_abilities.h"

class Manager_of_abilities{
private:
    std::vector<Interface_of_abilities> vector_of_abilities;

public:
    Manager_of_abilities();

    void add_ability(Interface_of_abilities ability);

    void perform_ability();

};

#endif