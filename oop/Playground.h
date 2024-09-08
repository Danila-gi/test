#pragma once
#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Enum_arguments.h"

using namespace std;

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
    }

    Playground(){}

    void get_ships(Manager_of_ships* ships,Coords* coords){
        list_of_ships = ships;
        arr_of_coords = coords;
        Ship** lis = list_of_ships->get_arr_of_ships();
        for (int i = 0; i<list_of_ships->get_count(); i++){
            if (lis[i]->get_location() == Vertical){
                for (int j = coords[i].y; j < coords[i].y + lis[i]->get_length(); j++)
                    arr_of_ground[j][coords[i].x] = 1;
            }
            else{
                for (int j = coords[i].x; j < coords[i].x + lis[i]->get_length(); j++)
                    arr_of_ground[coords[i].y][j] = 1;
            }
        }
    }

    void print_ground(){
        for (int i = 0; i < height; i++){
            cout << "| ";
            for (int j = 0; j < width; j++)
                cout << arr_of_ground[i][j] << " ";
            cout << "|\n";
        }
    }
};