#pragma once
#include <iostream>
#include "Ship.h"
#include "Enum_arguments.h"
#include <vector>

class Manager_of_ships
{
private:
    int count = 0;
    Ship** ships;

public:
    Manager_of_ships(int ships_count, int* sizes){
        ships = new Ship*[ships_count];
        for (int i = 0; i < ships_count; i++){
            ships[i] = new Ship(sizes[i]);
        }
        count = ships_count;
    }

    ~Manager_of_ships(){
        delete[] ships;
    }

    Manager_of_ships() : Manager_of_ships(0, {}){}

    Ship** get_arr_of_ships(){
        return ships;
    }

    int get_count(){
        return count;
    }

    void add_ship(int length, Location location){
        ships = (Ship**)realloc(ships, (++count) * sizeof(Ship*));
        ships[count - 1] = new Ship(length, location);
    }

    void add_ship(Ship* ship){
        ships = (Ship**)realloc(ships, (++count) * sizeof(Ship*));
        ships[count - 1] = ship;
    }

    void remove_ship(int index){

    }

    void print_ships(){
        for (int i = 0; i < count; i++){
            std::cout << i + 1 << ":";
            (*ships[i]).print_statment_of_ship();
        }
    }
};
