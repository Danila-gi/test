#include "Ship.h"

Ship::Ship(Length_of_the_ship p_length, Location p_location_of_ship){
    if (p_length >= ONE && p_length <= FOUR)
        length = p_length;
    else
        length = ONE;

    segments = new Statment_of_the_ship[length];
    for (int i = 0; i < length; i++)
        segments[i] = INTACT;
    location_of_ship = p_location_of_ship;
}

Ship::Ship(Length_of_the_ship p_length): Ship(p_length, Horizontal){}

Ship::Ship(): Ship(ONE){}

Ship::~Ship(){
    delete[] segments;
}

void Ship::shoot_to_segment(int coordinate){
    if (segments[coordinate] != DESTROYED)
        segments[coordinate] = static_cast<Statment_of_the_ship>(static_cast<int>(segments[coordinate]) - 1); 
}

Location Ship::get_location(){
    return location_of_ship;
}

void Ship::set_location(Location location){
    location_of_ship = location;
}

int Ship::get_length(){
    return length;
}

Statment_of_the_ship* Ship::get_segments(){
    return segments;
}

void Ship::print_statment_of_ship(){
    for (int i = 0; i < length; i++)
        std::cout << segments[i] << " ";
    std::cout << "| Location=" << location_of_ship<<std::endl;

}