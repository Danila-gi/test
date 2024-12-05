#include <iostream>
#include "headers/Ship.h"
#include "headers/Manager_of_ships.h"
#include "headers/Playground.h"
#include "headers/Double_atack.h"
#include "headers/Scanner.h"
#include "headers/Shelling.h"
#include "headers/Double_atack_builder.h"
#include "headers/Scanner_builder.h"
#include "headers/Shelling_builder.h"
#include "headers/Manager_of_abilities.h"
#include "headers/Add_ability.h"
#include "headers/Get_coords.h"
#include "headers/Ability_maker.h"
#include "headers/Paint.h"
#include "headers/Game.h"
#include "headers/FileWrapper.h"
#include "headers/Game_controller.h"
#include "headers/Input_from_terminal.h"
#include "headers/Output_to_terminal.h"

int main(){
    Game* game = new Game();
    auto game_control = Game_controller<Input_from_terminal, Output_to_terminal, Paint>(game);
    game_control.play();

    delete game;

    return 0;
}