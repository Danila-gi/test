#include "../headers/Game_controller.h"

template <typename InputType, typename OutputType>
Game_controller<InputType, OutputType>::Game_controller(Game* game):game(game){
    input = new InputType();
    output = new OutputType();
}

template <typename InputType, typename OutputType>
void Game_controller<InputType, OutputType>::play(){
    game->start_new_game();
    output.print_commands();
    bool flag = true;
    while (flag)
    {
        COMMAND command = input.read_command();
        if (command == )
    }
    
}