#ifndef A_MAKER_H
#define A_MAKER_H

#include "Command_coords.h"
#include "Interface_of_builders.h"
#include "Double_atack_builder.h"
#include "Scanner_builder.h"
#include "Shelling_builder.h"
#include <iostream>

enum Name_of_builder{
    DoubleAtack,
    Scanner,
    Shelling
};

class Ability_maker{
private:
    Command_coords* command;

    std::map<Name_of_builder, std::shared_ptr<Interface_of_builders>> list_of_builders;

public:
    Ability_maker(Command_coords* command);

    std::shared_ptr<Interface_of_builders> get_builder(Name_of_builder name);
};


#endif