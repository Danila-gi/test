#include "../headers/Manager_of_abilities.h"

Manager_of_abilities::Manager_of_abilities(Ability_maker& maker):maker(maker)
{
    vector_of_abilities.push_back(maker.get_builder(DOUBLE_ATACK));
    vector_of_abilities.push_back(maker.get_builder(SCANNER));
    vector_of_abilities.push_back(maker.get_builder(SHELLING));

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vector_of_abilities.begin(), vector_of_abilities.end(), g);
}

void Manager_of_abilities::push_ability(Name_of_builder builder){
    //std::cout<<"You get new ability!\n";
    vector_of_abilities.push_back(maker.get_builder(builder));
}

std::shared_ptr<Interface_of_builders> Manager_of_abilities::get_ability(){
    if (vector_of_abilities.size() == 0)
        throw NoAbilitiesException();
    auto builder = vector_of_abilities.back();
    vector_of_abilities.pop_back();
    return builder;
}

std::vector<Name_of_builder> Manager_of_abilities::get_names_of_abilies() const{
    std::vector<Name_of_builder> temp_vector;
    for (int i = 0; i < vector_of_abilities.size(); i++)
        temp_vector.push_back(vector_of_abilities[i]->get_name());
    return temp_vector;
}

void Manager_of_abilities::clear_manager(){vector_of_abilities.clear();}