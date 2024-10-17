#include "../headers/Manager_of_abilities.h"

Manager_of_abilities::Manager_of_abilities(){
    vector_of_abilities.push_back(std::make_shared<Shelling_builder>());
    vector_of_abilities.push_back(std::make_shared<Scanner_builder>());
    vector_of_abilities.push_back(std::make_shared<Double_atack_builder>());

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vector_of_abilities.begin(), vector_of_abilities.end(), g);
}

void Manager_of_abilities::add_ability(){
    std::vector<std::shared_ptr<Interface_of_builders>> test_vector;
    test_vector.push_back(std::make_shared<Shelling_builder>());
    test_vector.push_back(std::make_shared<Scanner_builder>());
    test_vector.push_back(std::make_shared<Double_atack_builder>());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, test_vector.size() - 1);
    
    int random_index = dis(gen);

    std::cout<<"You get new ability!\n";

    vector_of_abilities.push_back(test_vector[random_index]);
}

std::shared_ptr<Interface_of_builders> Manager_of_abilities::get_ability(){
    if (vector_of_abilities.size() == 0)
        throw NoAbilitiesException();
    auto builder = vector_of_abilities.back();
    vector_of_abilities.pop_back();
    return builder;
}