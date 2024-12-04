#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include "Input_from_terminal.h"
#include "Output_to_terminal.h"
#include "Game.h"

template <typename InputType, typename OutputType>
class Game_controller{
private:
    Game* game;

    InputType* input;
    OutputType* output;

public:
    Game_controller(Game* game);
    void play();
    
};

#endif