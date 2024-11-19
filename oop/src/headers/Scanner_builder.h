#ifndef SCANNER_BUILDER_H
#define SCANNER_BUILDER_H

#include <memory>
#include "Interface_of_builders.h"
#include "Playground.h"
#include "Scanner.h"
#include "Command_coords.h"

class Scanner_builder: public Interface_of_builders{
private:
    Command_coords* command;

public:
    Scanner_builder(Command_coords* p_command);

    std::shared_ptr<Interface_of_abilities> make_ability();

    bool is_need_arguments();

    Name_of_builder get_name();

    ~Scanner_builder() = default;
};


#endif