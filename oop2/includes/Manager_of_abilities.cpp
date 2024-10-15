#include "../headers/Manager_of_abilities.h"

Manager_of_abilities::Manager_of_abilities(){
    vector_of_abilities = {new Shelling_builder(), new Scanner_builder(), new Double_atack_builder()};

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vector_of_abilities.begin(), vector_of_abilities.end(), g);
}

Interface_of_builders* Manager_of_abilities::get_ability(){
    Interface_of_builders* builder = vector_of_abilities.back();
    vector_of_abilities.pop_back();
    return builder;
}