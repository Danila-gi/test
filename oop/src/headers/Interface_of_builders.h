#ifndef INTERFACE_OF_BUILDERS_H
#define INTERFACE_OF_BUILDERS_H

#include <iostream>
#include <memory>
#include "Playground.h"
#include "Interface_of_abilities.h"
#include "Names_of_abilities.h"

class Interface_of_builders{
public:
    virtual std::shared_ptr<Interface_of_abilities> make_ability() = 0;

    virtual bool is_need_arguments() = 0;

    virtual Name_of_builder get_name() = 0;

    virtual ~Interface_of_builders() = 0;
};

#endif