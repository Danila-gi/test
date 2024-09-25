#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Playground.h"

int main(){
    Ship s1 = Ship(FOUR, Vertical);
    Ship s2 = Ship(TWO, Horizontal);
    Ship s3 = Ship(THREE, Vertical);

    Length_of_the_ship l[] = {THREE, TWO, TWO, ONE};

    Manager_of_ships m = Manager_of_ships(4, l);

    m.add_ship(static_cast<Length_of_the_ship>(s1.get_length()), s1.get_location());
    m.add_ship(static_cast<Length_of_the_ship>(s2.get_length()), s2.get_location());
    m.add_ship(ONE, Vertical);
    m.add_ship(static_cast<Length_of_the_ship>(s3.get_length()), s3.get_location());

    m.shoot_to_ship(0, 2);
    m.shoot_to_ship(5, 0);

    m.set_location_for_the_ship(0, Vertical);

    m.remove_ship(1);
    m.print_ships();

    for (int i = 0; i < m.get_count_of_ships(); i++)
        std::cout<<m.get_arr_of_ships()[i].get_length()<<":";
    std::cout<<std::endl;

    std::cout<<m.get_count_of_ships()<<std::endl;

    return 0;
}
