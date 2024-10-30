#include "../headers/Manager_of_abilities.h"

Manager_of_abilities::Manager_of_abilities(Command_coords* p_command):command(p_command)
{
    vector_of_abilities.push_back(std::make_shared<Shelling_builder>());
    vector_of_abilities.push_back(std::make_shared<Scanner_builder>(command));
    vector_of_abilities.push_back(std::make_shared<Double_atack_builder>());

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vector_of_abilities.begin(), vector_of_abilities.end(), g);

}

void Manager_of_abilities::push_ability(std::shared_ptr<Interface_of_builders> builder){
    std::cout<<"You get new ability!\n";
    vector_of_abilities.push_back(builder);
}

std::shared_ptr<Interface_of_builders> Manager_of_abilities::get_ability(){
    if (vector_of_abilities.size() == 0)
        throw NoAbilitiesException();
    auto builder = vector_of_abilities.back();
    vector_of_abilities.pop_back();
    return builder;
}

std::vector<std::shared_ptr<Interface_of_builders>> Manager_of_abilities::get_vector_of_three_abilities() const{
    std::vector<std::shared_ptr<Interface_of_builders>> vector_for_add_new_ability = {std::make_shared<Shelling_builder>(), 
                                                                                        std::make_shared<Scanner_builder>(command),  
                                                                                        std::make_shared<Double_atack_builder>()};
    return vector_for_add_new_ability;
}