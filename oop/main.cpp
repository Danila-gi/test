#include <iostream>
#include "Ship.h"
#include "Manager_of_ships.h"
#include "Playground.h"

using namespace std;

int main(){
    int l[] = {2, 4};
    Coords c[] = {
        {2, 3},
        {4, 7},
        {0, 5},
    };

    Manager_of_ships m = Manager_of_ships(2, l);

    Playground p = Playground(10, 10);
    m.add_ship(4, Vertical);
    p.get_ships(&m, c);
    p.print_ground();
    return 0;
}