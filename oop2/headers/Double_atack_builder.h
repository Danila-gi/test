#ifndef DOUBLE_ATACK_BUILDER_H
#define DOUBLE_ATACK_BUILDER_H

#include <memory>
#include "Interface_of_builders.h"
#include "Playground.h"
#include "Double_atack.h"

class Double_atack_builder: public Interface_of_builders{
public:
    std::shared_ptr<Interface_of_abilities> make_ability(Coords coords = {0, 0}) override;

    bool is_need_arguments();

    ~Double_atack_builder();
};


#endif