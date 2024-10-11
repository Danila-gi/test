#include "../headers/Ship.h"

Ship::Ship(Length_of_the_ship p_length, Orientation p_orientation_of_ship)
:orientation_of_ship(p_orientation_of_ship)
{
    if (p_length >= ONE && p_length <= FOUR)
        length = p_length;
    else
        length = ONE;

    for (int i = 0; i < length; i++)
        segments.push_back(INTACT);
}

Ship::Ship(Length_of_the_ship p_length): Ship(p_length, Horizontal){}

Ship::Ship(): Ship(ONE){}

void Ship::shoot_to_segment(int coordinate){
    if (segments[coordinate] != DESTROYED && coordinate >= 0 && coordinate < length)
        segments[coordinate] = static_cast<Statement_of_the_ship>(static_cast<int>(segments[coordinate]) - 1); 
}

Orientation Ship::get_orientation() const{
    return orientation_of_ship;
}

void Ship::set_orientation(Orientation orientation){
    orientation_of_ship = orientation;
}

int Ship::get_length() const{
    return length;
}

Statement_of_the_ship Ship::get_segment_by_index(int index) const{
    if (index >= 0 && index < this->get_length())
        return segments[index];
    return segments[0];
}

void Ship::print_statement_of_ship(){
    for (int i = 0; i < length; i++)
        std::cout << segments[i] << " ";
    std::cout << "| Orientation=" << orientation_of_ship<<std::endl;
}
