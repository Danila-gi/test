#include "../headers/Double_atack.h"

void Double_atack::perform_ability(Playground& playground){
    throw "Incorrect arguments";
}

void Double_atack::perform_ability(Playground& playground, Coords coord){
    for (size_t i = 0; i < 2; i++)
        playground.shoot(coord);
}