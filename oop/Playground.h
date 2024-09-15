#pragma once
#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Enum_arguments.h"

class Playground{
private:
    int width;
    int height;
    int** arr_of_ground;
    Manager_of_ships* list_of_ships;
    Coords* arr_of_coords;

public:
    Playground(int p_width, int p_heigth){
        height = p_heigth;
        width = p_width;
        arr_of_ground = new int*[height];
        for (int i = 0; i < height; i++){
            arr_of_ground[i] = new int[width];
            for (int j = 0; j < width; j++)
                arr_of_ground[i][j] = 2;
        }
        arr_of_coords = new Coords;
    }

    Playground(){}

    void get_ship(Ship* ship, Coords coord){
        list_of_ships->add_ship(ship);
        arr_of_coords = (Coords*)realloc(arr_of_coords, list_of_ships->get_count() * sizeof(Coords));
        arr_of_coords[list_of_ships->get_count() - 1] = coord;

        for (int i = 0; i<list_of_ships->get_count(); i++){
            if (ship->get_location() == Vertical){
                for (int j = coord.y; j < coord.y + ship->get_length(); j++)
                    arr_of_ground[j][coord.x] = 1;
            }
            else{
                for (int j = coord.x; j < coord.x + ship->get_length(); j++)
                    arr_of_ground[coord.y][j] = 1;
            }
        }
    }

    void print_ground(){
        for (int i = 0; i < height; i++){
            std::cout << "| ";
            for (int j = 0; j < width; j++)
                std::cout << arr_of_ground[i][j] << " ";
            std::cout << "|\n";
        }
    }
};
