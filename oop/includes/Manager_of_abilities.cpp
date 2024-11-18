#include "../headers/Manager_of_abilities.h"

Manager_of_abilities::Manager_of_abilities(Ability_maker& maker):maker(maker)
{
    vector_of_abilities.push_back(maker.get_builder(DoubleAtack));
    vector_of_abilities.push_back(maker.get_builder(Scanner));
    vector_of_abilities.push_back(maker.get_builder(Shelling));

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vector_of_abilities.begin(), vector_of_abilities.end(), g);

}

void Manager_of_abilities::push_ability(Name_of_builder builder){
    std::cout<<"You get new ability!\n";
    vector_of_abilities.push_back(maker.get_builder(builder));
}

std::shared_ptr<Interface_of_builders> Manager_of_abilities::get_ability(){
    if (vector_of_abilities.size() == 0)
        throw NoAbilitiesException();
    auto builder = vector_of_abilities.back();
    vector_of_abilities.pop_back();
    return builder;
}