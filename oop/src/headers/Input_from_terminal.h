#ifndef TREMINAL_INPUT_H
#define TREMINAL_INPUT_H

#include <iostream>
#include <map>
#include "Commands.h"
#include "FileWrapper.h"
#include "Playground.h"

class Input_from_terminal{
private:
    std::map<char, COMMAND> commands_map;
    std::map<std::string, COMMAND> string_commands;

public:
    Input_from_terminal();

    void load_commands(const std::string& filename);
    COMMAND read_command();
    Coords read_coords();
    void read_ships(std::vector<Length_of_the_ship>& length_of_ships, std::vector<Coords>& coords_of_ships, std::vector<Orientation>& orientations_of_ships);
    std::map<char, COMMAND> get_map_of_commands() const;
};

#endif