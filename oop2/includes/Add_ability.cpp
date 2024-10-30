#include "../headers/Add_ability.h"

Add_ability::Add_ability(Manager_of_abilities& p_manager):manager(p_manager){}

void Add_ability::add_ability(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, manager.get_vector_of_three_abilities().size() - 1);
    
    int random_index = dis(gen);

    manager.push_ability(manager.get_vector_of_three_abilities()[random_index]);
}