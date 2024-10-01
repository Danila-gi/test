#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Playground.h"

int main(){
    Length_of_the_ship l[] = {THREE, THREE, ONE, TWO};
    Manager_of_ships m_empty = Manager_of_ships();
    Manager_of_ships m1 = Manager_of_ships(4, l);
    m1.add_ship(TWO, Vertical);
    m1.set_location_for_the_ship(3, Vertical);

    std::vector<Coords> c = {{2, 2}, {3, 4}, {0, 0}, {6, 1}, {2, 6}};
    Playground p1 = Playground(8, 8, m1, c);
    p1.add_ship(THREE, Vertical, {7, 4});
    p1.add_ship(FOUR, Vertical, {0, 4});

    p1.shoot({6, 1});
    p1.shoot({3, 2});
    p1.shoot({7, 6});
    p1.shoot({0, 0});
    p1.shoot({0, 0});
    p1.shoot({0, 7});
    p1.shoot({6, 4});

    p1.print_ground();

    p1.return_manager().print_ships();
    std::cout<<"-------"<<std::endl;
    m1.print_ships();

    return 0;
}