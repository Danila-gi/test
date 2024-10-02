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
    Playground p1 = Playground(8, 8);

    for (int i = 0; i < m1.get_count_of_ships(); i++)
        p1.add_ship(m1.get_ship(i), c[i]);

    m1.add_ship(THREE, Vertical);
    m1.add_ship(FOUR, Vertical);
    p1.add_ship(m1.get_ship(m1.get_count_of_ships() - 2), {7, 4});
    p1.add_ship(m1.get_ship(m1.get_count_of_ships() - 1), {0, 4});

    m1.add_ship(ONE, Vertical);
    p1.add_ship(m1.get_ship(m1.get_count_of_ships() - 1), {4, 0});

    p1.shoot({6, 1});
    p1.shoot({3, 2});
    p1.shoot({7, 6});
    p1.shoot({0, 0});
    p1.shoot({0, 0});
    p1.shoot({0, 7});
    p1.shoot({6, 4});
    p1.shoot({3, 1});

    p1.print_ground();

    std::cout<<"-------"<<std::endl;
    m1.print_ships();

    return 0;
}