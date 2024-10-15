#include "../headers/Shelling_builder.h"

std::shared_ptr<Interface_of_abilities> Shelling_builder::make_ability(Coords coords){
    return std::make_shared<Shelling>();
}

bool Shelling_builder::is_need_arguments(){return false;}

Shelling_builder::~Shelling_builder(){}