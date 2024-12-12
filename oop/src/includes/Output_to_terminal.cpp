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

void Output_to_terminal::print_command(char symbol, COMMAND command){
    std::cout << symbol << " - " << commands_to_string[command] << std::endl;
}

void Output_to_terminal::print_input_ships_infor(){
    std::cout << "Print sizes of ground and count of ships." << std::endl;
    std::cout << "Print after that some arguments for ship (count, lenght, coords, orientation(1-vert, 0-horiz))." << std::endl;
}

void Output_to_terminal::print_coords_infor(){
    std::cout << "Print coords:" << std::endl;
}

void Output_to_terminal::print_command_infor(){
    std::cout << "Print command:" << std::endl;
}

void Output_to_terminal::print_line(){
    std::cout<<"===================================="<<std::endl;
}

void Output_to_terminal::print_ability_process(Name_of_builder builder){
    std::cout << builder_to_string[builder] << " process..." << std::endl;
}

void Output_to_terminal::print_atack_process(Coords coord, bool is_good_hit){
    if (is_good_hit){
        std::cout<< "Good hit " << coord.x << ":" << coord.y << std::endl;
        return;
    }
    std::cout << "Miss " << coord.x << ":" << coord.y <<std::endl;
}

void Output_to_terminal::print_enemy_turn(Coords coord){
    std::cout << "Shoot to " << coord.x << ":" << coord.y <<std::endl;
}

void Output_to_terminal::print_round(int number){
    std::cout << "Round is " << number <<std::endl;
}

void Output_to_terminal::print_scanner(bool result){
    if (result){
        std::cout << "Ship is exist here" << std::endl;
        return;
    }
    std::cout << "Ship isn't exist here" << std::endl; 
}

void Output_to_terminal::print_get_new_ability(){
    std::cout << "Nice, you have destroyed ship" << std::endl;
    std::cout << "You get new ability!" << std::endl;
}