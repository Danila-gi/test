#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Playground.h"

int main(){
    Ship s = Ship(FOUR, Vertical);
    s.set_location(Horizontal);
    std::cout<<s.get_length()<<std::endl;
    std::cout<<s.get_location()<<std::endl;
    s.shoot_to_segment(2);
    s.shoot_to_segment(2);
    s.shoot_to_segment(2);
    s.shoot_to_segment(0);
    for (int i = 0; i < s.get_length(); i++)
        std::cout<<s.get_segments()[i]<<"-";
    std::cout<<std::endl;

    s.print_statment_of_ship();

    return 0;
}
