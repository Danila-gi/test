#include "../headers/Shelling_builder.h"

std::shared_ptr<Interface_of_abilities> Shelling_builder::make_ability(Coords coords){
    auto p_builder = std::make_shared<Shelling>();
    //std::cout<<"New shelling "<<p_builder.get()<<std::endl;
    return p_builder;
}

bool Shelling_builder::is_need_arguments(){return false;}

Shelling_builder::~Shelling_builder(){}