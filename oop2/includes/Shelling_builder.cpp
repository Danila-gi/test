#include "../headers/Scanner_builder.h"

std::shared_ptr<Interface_of_abilities> Scanner_builder::make_ability(Coords coords){
    return std::make_shared<Scanner>(coords);
}

bool Scanner_builder::is_need_arguments(){return true;}

Scanner_builder::~Scanner_builder(){}