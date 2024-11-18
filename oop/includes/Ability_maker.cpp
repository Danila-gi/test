#include "../headers/Ability_maker.h"

Ability_maker::Ability_maker(Command_coords* command):command(command)
{
    list_of_builders[DoubleAtack] = std::make_shared<Double_atack_builder>();
    list_of_builders[Scanner] = std::make_shared<Scanner_builder>(command);
    list_of_builders[Shelling] = std::make_shared<Shelling_builder>();
}

std::shared_ptr<Interface_of_builders> Ability_maker::get_builder(Name_of_builder name){
    return list_of_builders[name];
}