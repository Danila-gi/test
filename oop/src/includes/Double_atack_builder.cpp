#include "../headers/Double_atack_builder.h"

std::shared_ptr<Interface_of_abilities> Double_atack_builder::make_ability(){
    auto p_builder = std::make_shared<Double_atack>();
    return p_builder;
}

bool Double_atack_builder::is_need_arguments(){return false;}

Name_of_builder Double_atack_builder::get_name(){return DOUBLE_ATACK;};