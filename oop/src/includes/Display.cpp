#include "../headers/Display.h"

template <typename PaintType, typename OutputType>
Display<PaintType, OutputType>::Display(){
    output = new OutputType();
    painter = Paint();

    commands_to_function["input_ships"] = [&](){output->print_input_ships_infor();};
    commands_to_function["new_ability"] = [&](){output->print_get_new_ability();};
    commands_to_function["input_coords"] = [&](){output->print_coords_infor();};
    commands_to_function["input_command"] = [&](){output->print_command_infor();};
    commands_to_function["line"] = [&](){output->print_line();};
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::execute_message(std::string command){
    commands_to_function[command]();
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_builder(Name_of_builder builder){
    output->print_ability_process(builder);
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_scanner_result(bool result){
    output->print_scanner(result);
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_player_shoot_result(bool flag, Coords coord){
    output->print_atack_process(coord, flag);
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_enemy_turn(Coords coord){
    output->print_enemy_turn(coord);
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_commands(std::map<char, COMMAND> commands_map){
    for (const auto& pair: commands_map){
        output->print_command(pair.first, pair.second);
    }
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_player_ground(Playground& playground){
    painter.print_your_ground(playground);
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_enemy_ground(Playground& playground){
    painter.print_enemy_ground(playground);
}

template <typename PaintType, typename OutputType>
void Display<PaintType, OutputType>::print_round(int number){
    output->print_round(number);
}

template class Display<Paint, Output_to_terminal>;