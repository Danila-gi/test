#include "../headers/Scanner_builder.h"

std::shared_ptr<Interface_of_abilities> Scanner_builder::make_ability(Coords coords){
    auto p_builder = std::make_shared<Scanner>(coords);
    //std::cout<<"New scanner "<<p_builder.get()<<std::endl;
    return p_builder;
}

bool Scanner_builder::is_need_arguments(){return true;}