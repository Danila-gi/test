#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Playground.h"

int main(){
    Ship* s1 = new Ship(TWO, Vertical);
    Length_of_the_ship l[] = {THREE, THREE, ONE, TWO};
    Manager_of_ships m1 = Manager_of_ships(4, l);
    m1.add_ship(s1);
    s1->shoot_to_segment(1);
    m1.get_arr_of_ships()[1]->shoot_to_segment(1);
    m1.print_ships();

    Coords c[] = {{2, 2}, {3, 4}, {1, 1}, {5, 5}, {7, 1}};
    Playground p1 = Playground(8, 8);
    p1.set_coords(c);
    p1.set_manager(&m1);
    p1.print_ground();
    return 0;
}