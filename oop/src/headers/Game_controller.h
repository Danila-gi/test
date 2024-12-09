#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include "Input_from_terminal.h"
#include "Output_to_terminal.h"
#include "Game.h"
#include "Display.h"

template <typename InputType, typename OutputType, typename PaintType>
class Game_controller{
private:
    Game* game;

    InputType* input;
    //OutputType* output;
    Display<PaintType, OutputType> display;

public:
    Game_controller(Game* game);
    ~Game_controller();
    void play();
    void start_init();
};

#endif