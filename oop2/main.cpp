#include <iostream>
#include "headers/Ship.h"
#include "headers/Manager_of_ships.h"
#include "headers/Playground.h"
#include "headers/Double_atack.h"
#include "headers/Scanner.h"
#include "headers/Shelling.h"

int main(){
    std::vector<Length_of_the_ship> l = {THREE, THREE, ONE, TWO, TWO, THREE, FOUR, ONE};
    Manager_of_ships m1 = Manager_of_ships(8, l);
    m1.get_ship(4).set_orientation(Vertical);
    m1.get_ship(5).set_orientation(Vertical);
    m1.get_ship(6).set_orientation(Vertical);
    m1.get_ship(7).set_orientation(Vertical);

    std::vector<Coords> c = {{2, 2}, {3, 4}, {0, 0}, {6, 1}, {2, 6}, {7, 4}, {0, 4}, {4, 0}};
    Playground p1 = Playground(8, 8);

    for (int i = 0; i < m1.get_count_of_ships(); i++)
        p1.add_ship(m1.get_ship(i), c[i]);

    p1.shoot({6, 1});
    p1.shoot({3, 2});
    p1.shoot({7, 6});
    p1.shoot({0, 0});
    p1.shoot({0, 0});
    p1.shoot({0, 7});
    p1.shoot({6, 4});
    p1.shoot({3, 1});

    p1.print_ground();
    m1.print_ships();
    std::cout<<"-------"<<std::endl;

    Double_atack da;
    da.perform_ability(p1, {7, 1});

    Shelling sh;
    sh.perform_ability(p1);
    m1.print_ships();

    Scanner sc;
    sc.perform_ability(p1, {0, 6});
    return 0;
}