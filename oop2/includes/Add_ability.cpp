#include "../headers/Add_ability.h"

Add_ability::Add_ability(Manager_of_abilities& p_manager):manager(p_manager){}

void Add_ability::execute(){
    std::vector<std::shared_ptr<Interface_of_builders>> vector_for_add_new_ability = {std::make_shared<Double_atack_builder>(), 
                                                                                        std::make_shared<Scanner_builder>(), 
                                                                                        std::make_shared<Shelling_builder>()}; 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vector_for_add_new_ability.size() - 1);
    
    int random_index = dis(gen);

    manager.push_ability(vector_for_add_new_ability[random_index]);
}