#ifndef OUTPUT_TERMINAL_H
#define OUTPUT_TERMINAL_H

#include <iostream>
#include <map>
#include "Commands.h"
#include "Paint.h"
#include "Playground.h"

class Output_to_terminal{
private:
    std::map<COMMAND, std::string> commands_to_string;

    std::map<Name_of_builder, std::string> builder_to_string;
public:
    Output_to_terminal();

    void print_playground(Paint painter, bool is_for_player, Playground& playground);

    void print_commands(std::map<char, COMMAND> commands_map);

    void print_input_ships_infor();

    void print_ability_process(std::shared_ptr<Interface_of_builders> builder);

    void print_atack_process(Coords coord, bool is_good_hit, int damage=1);

    void print_get_new_ability();
};

#endif