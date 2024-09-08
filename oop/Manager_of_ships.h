#pragma once
#include <iostream>
#include "Ship.h"
#include "Enum_arguments.h"

using namespace std;

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
        for (int i = 0; i < count; i++)
            delete ships[i];
        delete[] ships;
    }

    Manager_of_ships(){}

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

    void print_ships(){
        for (int i = 0; i < count; i++){
            cout << i + 1 << ":";
            (*ships[i]).print_statment_of_ship();
        }
    }
};