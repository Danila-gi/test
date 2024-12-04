#include "../headers/Output_to_terminal.h"

Output_to_terminal::Output_to_terminal(){
    commands_to_string[ATACK] = "Atack";
    commands_to_string[ABILITY] = "Ability";
    commands_to_string[SAVE] = "Save";
    commands_to_string[LOAD] = "Load";
    commands_to_string[EXIT] = "Exit";
    commands_to_string[INPUT_SHIPS] = "Input_ships";

    builder_to_string[DOUBLE_ATACK] = "Double_atack";
    builder_to_string[SHELLING] = "Shelling";
    builder_to_string[SCANNER] = "Scanner";
}

void Output_to_terminal::print_playground(Paint painter, bool is_for_player, Playground& playground){
    if (is_for_player){
        painter.print_your_ground(playground);
        return;
    }
    painter.print_enemy_ground(playground);
}

void Output_to_terminal::print_commands(std::map<char, COMMAND> commands_map){
    std::cout << "Start new game" << std::endl;
    std::cout << "You have some commands in this game." << std::endl;
    std::string name_command;
    for (const auto& pair: commands_map){
        std::cout << pair.first << " - " << commands_to_string[pair.second] << std::endl;
    }
}

void Output_to_terminal::print_input_ships_infor(){
    std::cout << "Print some arguments for ship:" << std::endl;
}

void Output_to_terminal::print_ability_process(std::shared_ptr<Interface_of_builders> builder){
    std::cout << builder_to_string[builder->get_name()] << " process..." << std::endl;
}

void Output_to_terminal::print_atack_process(Coords coord, bool is_good_hit, int damage){
    if (is_good_hit){
        if (damage == 1){
            std::cout<< "good hit " << coord.x << ":" << coord.y << std::endl;
            return;
        }
        std::cout<< "good " << damage << "-force hit " << coord.x << ":" << coord.y << std::endl;
        return;
    }
    std::cout << "miss " << coord.x << ":" << coord.y <<std::endl;
}

void Output_to_terminal::print_get_new_ability(){
    std::cout << "Nice, you have destroyed ship" << std::endl;
    std::cout << "You get new ability!" << std::endl;
}