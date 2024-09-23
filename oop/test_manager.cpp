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
    m.add_ship(&s1);

    s1.shoot_to_segment(1);
    m.get_arr_of_ships()[0]->shoot_to_segment(2);

    m.add_ship(&s2);
    m.add_ship(ONE, Vertical);
    m.add_ship(&s3);
    m.remove_ship(1);
    m.print_ships();

    for (int i = 0; i < m.get_count(); i++)
        std::cout<<m.get_arr_of_ships()[i]->get_length()<<":";
    std::cout<<std::endl;

    std::cout<<m.get_count()<<std::endl;

    return 0;
}
