#ifndef SHELLING_BUILDER_H
#define SHELLING_BUILDER_H

#include <memory>
#include "Interface_of_builders.h"
#include "Playground.h"
#include "Shelling.h"

class Shelling_builder: public Interface_of_builders{
public:
    std::shared_ptr<Interface_of_abilities> make_ability(Coords coords = {0, 0}) override;

    bool is_need_arguments();

    ~Shelling_builder();
};


#endif