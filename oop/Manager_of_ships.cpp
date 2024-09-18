#include "Manager_of_ships.h"

Manager_of_ships::Manager_of_ships(int ships_count, Length_of_the_ship* sizes){
    for (int i = 0; i < ships_count; i++){
        ships.push_back(new Ship(sizes[i]));
    }
    count = ships_count;
}

Manager_of_ships::~Manager_of_ships(){
}

Manager_of_ships::Manager_of_ships() : Manager_of_ships(0, {}){}

std::vector<Ship*> Manager_of_ships::get_arr_of_ships(){
    return ships;
}

int Manager_of_ships::get_count(){
    return count;
}

void Manager_of_ships::add_ship(Length_of_the_ship length, Location location){
    ships.push_back(new Ship(length, location));
    count++;
}

void Manager_of_ships::add_ship(Ship* ship){
    ships.push_back(ship);
    count++;
}

void Manager_of_ships::remove_ship(int index){
    ships.erase(ships.begin() + index);
    count--;
}

void Manager_of_ships::print_ships(){
    for (int i = 0; i < count; i++){
        std::cout << i + 1 << ":";
        (*ships[i]).print_statment_of_ship();
    }
}