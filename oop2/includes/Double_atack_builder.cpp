#include "../headers/Double_atack_builder.h"

std::shared_ptr<Interface_of_abilities> Double_atack_builder::make_ability(Coords coords){
    auto p_builder = std::make_shared<Double_atack>(coords);
    return p_builder;
}

bool Double_atack_builder::is_need_arguments(){return true;}