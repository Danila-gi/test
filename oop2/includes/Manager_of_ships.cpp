#include "../headers/Manager_of_ships.h"

Manager_of_ships::Manager_of_ships(int ships_count, std::vector<Length_of_the_ship> sizes){
    for (int i = 0; i < ships_count && i < sizes.size(); i++){
        Ship* ship = new Ship(sizes[i]);
        ships.push_back(ship);
    }
}

Manager_of_ships::Manager_of_ships() : Manager_of_ships(0, {}){}

Manager_of_ships::~Manager_of_ships(){
    for (int i = 0; i < ships.size(); i++)
        delete ships[i];
}

Ship& Manager_of_ships::get_ship(int index){
    if (index >= 0 && index < this->get_count_of_ships())
        return *ships[index];
    return *ships[0];
}

int Manager_of_ships::get_count_of_ships() const{
    return ships.size();
}

void Manager_of_ships::remove_ship(int index){
    if (index >= 0 && index < ships.size())
        ships.erase(ships.begin() + index);
}

void Manager_of_ships::print_ships(){
    for (int i = 0; i < ships.size(); i++){
        std::cout << i + 1 << ":";
        (*ships[i]).print_statement_of_ship();
    }
}