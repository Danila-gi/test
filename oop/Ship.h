#pragma once
#include <iostream>
#include "Enum_arguments.h"

using namespace std;

class Ship
{
private:
    int length;
    int* segments;
    Location location_of_ship;

public:
    Ship(int p_length, Location p_location_of_ship){
        if (p_length >= 1 && p_length <= 4)
            length = p_length;
        else
            length = 1;

        segments = new int[length];
        for (int i = 0; i < length; i++)
            segments[i] = 2;
        location_of_ship = p_location_of_ship;
    }

    Ship(int p_length): Ship(p_length, Horizontal){}

    Ship(){length = 0;}

    ~Ship(){
        delete[] segments;
    }

    void shoot_to_segment(int coordinate){
        segments[coordinate]--; 
    }

    Location get_location(){
        return location_of_ship;
    }

    int get_length(){
        return length;
    }

    int* get_segments(){
        return segments;
    }

    void print_statment_of_ship(){
        for (int i = 0; i < length; i++)
            cout << segments[i] << " ";
        cout << '\n';

    }
};