#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Playground.h"

int main(){
    Ship* s1 = new Ship(THREE, Vertical);
    Length_of_the_ship l[] = {THREE, THREE, ONE, TWO};
    Manager_of_ships m1 = Manager_of_ships(4, l);
    m1.add_ship(TWO, Horizontal);
    m1.print_ships();

    std::vector<Coords> c = {{2, 2}, {3, 4}, {0, 0}, {6, 2}, {0, 7}};
    Playground p1 = Playground(8, 8);
    p1.set_manager_with_coords(&m1, c);
    p1.get_ship(s1, {7, 4});
    p1.print_ground();
    p1.shoot({2, 2});
    p1.shoot({6, 6});
    p1.shoot({7, 6});
    p1.shoot({0, 0});
    p1.shoot({0, 7});

    p1.return_manager()->print_ships();
    std::cout<<"-------"<<std::endl;
    m1.print_ships();
    Playground P = std::move(p1);
    P.print_ground();
    return 0;
}