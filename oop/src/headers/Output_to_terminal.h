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

    void print_command(char symbol, COMMAND command);

    void print_input_ships_infor();
    void print_coords_infor();
    void print_command_infor();
    void print_get_new_ability();
    void print_line();

    void print_ability_process(Name_of_builder builder);

    void print_atack_process(Coords coord, bool is_good_hit);

    void print_enemy_turn(Coords coord);

    void print_round(int number);

    void print_scanner(bool result);
};

#endif