#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include "Input_from_terminal.h"
#include "Output_to_terminal.h"
#include "Game.h"

template <typename PaintType, typename OutputType>
class Display{
private:
    OutputType* output;
    PaintType painter;

    std::map<std::string, std::function<void()>> commands_to_function;

public:
    Display();
    void execute_message(std::string command);

    void print_player_ground(Playground& playground);
    void print_enemy_ground(Playground& playground);
    void print_commands(std::map<char, COMMAND> commands_map);
    void print_builder(Name_of_builder builder);
    void print_player_shoot_result(bool flag, Coords coord);
    void print_enemy_turn(Coords coord);
    void print_round(int number_of_round);
    void print_scanner_result(bool result);
};

#endif