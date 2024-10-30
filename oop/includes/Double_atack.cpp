#include "../headers/Double_atack.h"

bool Double_atack::perform_ability(Playground& playground){
    std::cout<<"Double atack process...\n";
    playground.set_double_atack();
    return true;
}