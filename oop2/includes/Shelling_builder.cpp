#include "../headers/Shelling_builder.h"

std::shared_ptr<Interface_of_abilities> Shelling_builder::make_ability(Coords coords){
    auto p_builder = std::make_shared<Shelling>();
    return p_builder;
}

bool Shelling_builder::is_need_arguments(){return false;}