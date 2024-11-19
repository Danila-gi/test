#include "../headers/Add_ability.h"

Add_ability::Add_ability(Manager_of_abilities& p_manager):manager(p_manager){}

void Add_ability::add_ability(){
    std::vector<Name_of_builder> builders = {DOUBLE_ATACK, SCANNER, SHELLING};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, builders.size() - 1);
    
    int random_index = dis(gen);

    manager.push_ability(builders[random_index]);
}