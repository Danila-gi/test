#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Playground.h"

int main(){
    Ship* s1 = new Ship(THREE, Vertical);
    Length_of_the_ship l[] = {THREE, THREE, ONE, TWO};
    Manager_of_ships m1 = Manager_of_ships(4, l);
    m1.get_arr_of_ships()[1]->shoot_to_segment(1);
    m1.print_ships();

    std::vector<Coords> c = {{2, 2}, {3, 4}, {0, 0}, {6, 4}};
    Playground p1 = Playground(8, 8);
    p1.set_manager(&m1);
    p1.set_coords(c);
    p1.get_ship(s1, {6, 2});
    p1.print_ground();
    p1.shoot({7, 6});
    p1.shoot({6, 6});
    p1.shoot({5, 6});
    p1.shoot({3, 2});
    p1.shoot({6, 0});

    m1.print_ships();
    std::cout<<"-------"<<std::endl;
    return 0;
}