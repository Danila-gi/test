#include "../headers/Double_atack.h"

Double_atack::Double_atack(Coords p_coords):coords(p_coords){}

Double_atack::Double_atack():Double_atack({0, 0}){}

void Double_atack::set_new_coords(Coords p_coords){
    coords = p_coords;
}

bool Double_atack::perform_ability(Playground& playground){
    for (size_t i = 0; i < 2; i++)
        playground.shoot(coords);
    return true;
}

Double_atack::~Double_atack(){}