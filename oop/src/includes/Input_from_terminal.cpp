#include "../headers/Input_from_terminal.h"

Input_from_terminal::Input_from_terminal(){
    string_commands["Atack"] = ATACK;
    string_commands["Ability"] = ABILITY;
    string_commands["Save"] = SAVE;
    string_commands["Load"] = LOAD;
    string_commands["Exit"] = EXIT;
    string_commands["Input_ships"] = INPUT_SHIPS;
}

void Input_from_terminal::load_commands(const std::string& filename){
    std::ifstream file(filename);

    char key;
    std::string value;

    while (file >> key >> value)
    {
        commands_map[key] = string_commands[value];
    }
    file.close();
    
}

COMMAND Input_from_terminal::read_command(){
    char x;
    std::cin >> x;
    return commands_map[x];
}

Coords Input_from_terminal::read_coords(){
    int x, y;
    std::cin >> x >> y;
    return Coords{x, y};
}

void Input_from_terminal::read_ships(std::vector<Length_of_the_ship>& length_of_ships, std::vector<Coords>& coords_of_ships, std::vector<Orientation>& orientations_of_ships){
    length_of_ships = {FOUR, THREE, THREE, TWO, TWO, TWO, ONE, ONE, ONE, ONE};
    coords_of_ships = {{2, 2}, {3, 4}, {0, 0}, {6, 0}, {1, 6}, {7, 4}, {0, 4}, {4, 0}, {9, 0}, {7, 7}};
    orientations_of_ships = {Horizontal, Vertical, Vertical, Horizontal, Vertical, Horizontal, Vertical, Vertical, Horizontal, Horizontal};
}

std::map<char, COMMAND> Input_from_terminal::get_map_of_commands() const{
    return commands_map;
}