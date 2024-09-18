#include "Playground.h"

Playground::Playground(int p_width, int p_heigth){
    height = p_heigth;
    width = p_width;
    arr_of_ground = new Statment_of_the_coord*[height];
    for (int i = 0; i < height; i++){
        arr_of_ground[i] = new Statment_of_the_coord[width];
        for (int j = 0; j < width; j++)
            arr_of_ground[i][j] = EMPTY;
    }
    arr_of_coords = new Coords;
    list_of_ships = new Manager_of_ships;
}

Playground::Playground(){}

void Playground::set_manager(Manager_of_ships* manager){
    list_of_ships = manager;
    //list_of_ships->get_arr_of_ships()[1]->print_statment_of_ship();
    for (int i = 0; i < list_of_ships->get_count(); i++)
        this->put_new_ships(list_of_ships->get_arr_of_ships()[i], arr_of_coords[i]);
}

void Playground::set_coords(Coords* coords){
    arr_of_coords = coords;
}

void Playground::get_ship(Ship* ship, Coords coord){
    list_of_ships->add_ship(ship);
    arr_of_coords = (Coords*)realloc(arr_of_coords, list_of_ships->get_count() * sizeof(Coords));
    arr_of_coords[list_of_ships->get_count() - 1] = coord;

    this->put_new_ships(ship, coord);
}

void Playground::put_new_ships(Ship* ship, Coords coord){
    //ship->print_statment_of_ship();
    for (int i = 0; i<list_of_ships->get_count(); i++){
        if (ship->get_location() == Vertical){
            for (int j = coord.y; j < coord.y + ship->get_length(); j++)
                arr_of_ground[j][coord.x] = SHIP;
        }
        else{
            for (int j = coord.x; j < coord.x + ship->get_length(); j++)
                arr_of_ground[coord.y][j] = SHIP;
        }
    }
}

void Playground::print_ground(){
    for (int i = 0; i < height; i++){
        std::cout << "| ";
        for (int j = 0; j < width; j++)
            std::cout << arr_of_ground[i][j] << " ";
        std::cout << "|\n";
    }
}