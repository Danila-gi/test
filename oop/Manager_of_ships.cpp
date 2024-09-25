#include "Manager_of_ships.h"

Manager_of_ships::Manager_of_ships(int ships_count, Length_of_the_ship sizes[]){
    for (int i = 0; i < ships_count; i++)
        ships.push_back(Ship(sizes[i]));
}

Manager_of_ships::Manager_of_ships() : Manager_of_ships(0, {}){}

std::vector<Ship> Manager_of_ships::get_arr_of_ships() const{
    return ships;
}

int Manager_of_ships::get_count_of_ships() const{
    return ships.size();
}

void Manager_of_ships::add_ship(Length_of_the_ship length, Location location){
    ships.push_back(Ship(length, location));
}

void Manager_of_ships::shoot_to_ship(int index_of_ship, int index_of_segment){
    if (index_of_ship >= 0 && index_of_ship < ships.size())
        ships[index_of_ship].shoot_to_segment(index_of_segment);
}

void Manager_of_ships::set_location_for_the_ship(int index_of_ship, Location location){
    if (index_of_ship >= 0 && index_of_ship < ships.size())
        ships[index_of_ship].set_location(location);
}

void Manager_of_ships::remove_ship(int index){
    if (index >= 0 && index < ships.size())
        ships.erase(ships.begin() + index);
}

void Manager_of_ships::print_ships(){
    for (int i = 0; i < ships.size(); i++){
        std::cout << i + 1 << ":";
        ships[i].print_statement_of_ship();
    }
}