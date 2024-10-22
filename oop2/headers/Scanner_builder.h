#ifndef SCANNER_BUILDER_H
#define SCANNER_BUILDER_H

#include <memory>
#include "Interface_of_builders.h"
#include "Playground.h"
#include "Scanner.h"

class Scanner_builder: public Interface_of_builders{
public:
    std::shared_ptr<Interface_of_abilities> make_ability(Coords coords = {0, 0});

    bool is_need_arguments();

    ~Scanner_builder() = default;
};


#endif