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
    try
    {
        FileWrapper file(filename, std::ios::in);

        std::set<char> assigned_keys;
        std::set<std::string> assigned_commands;

        char key;
        std::string value;

        while (file.read(key) && file.read(value))
        {
            if (assigned_keys.find(key) != assigned_keys.end()) {
                throw std::runtime_error("Duplicate key assignment: " + std::string(1, key));
            }

            if (assigned_commands.find(value) != assigned_commands.end()) {
                throw std::runtime_error("Duplicate command assignment: " + value);
            }

            if (string_commands.find(value) == string_commands.end()){
                throw std::runtime_error("Unknown command!");
            }

            commands_map[key] = string_commands[value];
            assigned_keys.insert(key);
            assigned_commands.insert(value);
        }
        //file.close();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        this->default_arguments();
    }
    
}

void Input_from_terminal::default_arguments(){
    std::vector<char> keys = {'1', '2', '3', '4', '5', '6'};
    std::vector<std::string> values = {"Atack", "Ability", "Save", "Load", "Exit", "Input_ships"};
    for (int i = 0; i < keys.size(); i++)
        commands_map[keys[i]] = string_commands[values[i]];
}

COMMAND Input_from_terminal::read_command(){
    char x;
    std::cin >> x;
    if (commands_map.find(x) == commands_map.end()){
        return NONE;
    }
    return commands_map[x];
}

Coords Input_from_terminal::read_coords(){
    int x, y;
    bool valid_input = false;

    while (!valid_input) {
        std::cin >> x >> y;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter numbers only." << std::endl;
        } else {
            valid_input = true;
        }
    }

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