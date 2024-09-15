#pragma once
#include <iostream>
#include "Ship.h"
#include "Enum_arguments.h"
#include <vector>

class Manager_of_ships
{
private:
    int count = 0;
    std::vector<Ship*> ships;

public:
    Manager_of_ships(int ships_count, int* sizes){
        for (int i = 0; i < ships_count; i++){
            ships.push_back(new Ship(sizes[i]));
        }
        count = ships_count;
    }

    ~Manager_of_ships(){
    }

    Manager_of_ships() : Manager_of_ships(0, {}){}

    std::vector<Ship*> get_arr_of_ships(){
        return ships;
    }

    int get_count(){
        return count;
    }

    void add_ship(int length, Location location){
        ships.push_back(new Ship(length, location));
        count++;
    }

    void add_ship(Ship* ship){
        ships.push_back(ship);
        count++;
    }

    void remove_ship(int index){
        ships.erase(ships.begin() + index);
        count--;
    }

    void print_ships(){
        for (int i = 0; i < count; i++){
            std::cout << i + 1 << ":";
            (*ships[i]).print_statment_of_ship();
        }
    }
};
