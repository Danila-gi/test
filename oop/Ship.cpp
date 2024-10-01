#include "Ship.h"

Ship::Ship(Length_of_the_ship p_length, Location p_location_of_ship)
:location_of_ship(p_location_of_ship)
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

Location Ship::get_location() const{
    return location_of_ship;
}

void Ship::set_location(Location location){
    location_of_ship = location;
}

int Ship::get_length() const{
    return length;
}

std::vector<Statement_of_the_ship> Ship::get_segments() const{
    return segments;
}

//bool Ship::operator<(const std::reference_wrapper<Ship> &other) const
//{ return this->get_length() < other.get().get_length(); }

void Ship::print_statement_of_ship(){
    for (int i = 0; i < length; i++)
        std::cout << segments[i] << " ";
    std::cout << "| Location=" << location_of_ship<<std::endl;

}



/*namespace std
{
    
    bool operator<(const std::reference_wrapper<Ship>& a, const std::reference_wrapper<Ship>& b)
    {
        return a.get().get_length() < b.get().get_length();
    }

}*/
