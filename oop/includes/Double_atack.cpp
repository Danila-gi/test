#include "../headers/Double_atack.h"

bool Double_atack::perform_ability(Playground& playground){
    std::cout<<"Double atack process...\n";
    playground.set_multiple_attack(2);
    return true;
}