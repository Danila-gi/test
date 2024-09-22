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
    list_of_ships = new Manager_of_ships;
}

Playground::Playground(){}

Playground::~Playground(){
    for(int i = 0; i < height; ++i)
        delete[] arr_of_ground[i];
    delete[] arr_of_ground;
    delete list_of_ships;
}

bool Playground::check_point(Coords coord){
    int X = coord.x;
    int Y = coord.y;
    if (X < 0 || Y < 0 || X >= width || Y >= height)
        return false;
    int count_of_good_points = 0;
    for (int i = X - 1; i <= X + 1; i++){
        for (int j = Y - 1; j <= Y + 1; j++){
            if (i < 0 || i >= width || j < 0 || j >= height)
                count_of_good_points++;
            else{
                if (arr_of_ground[j][i] != SHIP)
                    count_of_good_points++;
            }
        }
    }
    return count_of_good_points == 9;
    
}

void Playground::set_manager_with_coords(Manager_of_ships* manager, std::vector<Coords> coords){
    for (int i = 0; i < manager->get_count(); i++){
        bool flag = true;
        std::vector<Coords> mas_of_coords;
        Ship* ship = manager->get_arr_of_ships()[i];
        if (ship->get_location() == Horizontal){
            for (int j = 0; j < ship->get_length(); j++){
                if (check_point(coords[i]))
                    mas_of_coords.push_back({coords[i].x + j, coords[i].y});
                else{
                    flag = false;
                    break;
                }
            }
        }
        else{
            for (int j = 0; j < ship->get_length(); j++){
                if (check_point(coords[i]))
                    mas_of_coords.push_back({coords[i].x, coords[i].y + j});
                else{
                    flag = false;
                    break;
                }
            }
        }

        if (flag){
            list_of_ships->add_ship(ship);
            coords_of_ship[ship] = mas_of_coords;
            this->put_new_ships(ship);
        }
    }
}

void Playground::get_ship(Ship* ship, Coords coord, Location location){
    std::vector<Coords> mas_of_coords;
    bool flag = true;
    ship->set_location(location);
    if (ship->get_location() == Horizontal){
        for (int j = 0; j < ship->get_length(); j++){
            if (check_point({coord.x + j, coord.y}))
                mas_of_coords.push_back({coord.x + j, coord.y});
            else{
                flag = false;
                break;
            }
        }
    }
    else{
        for (int j = 0; j < ship->get_length(); j++){
            if (check_point({coord.x, coord.y + j}))
                mas_of_coords.push_back({coord.x, coord.y + j});
            else{
                flag = false;
                break;
            }
        }
    }

    if (flag){
        list_of_ships->add_ship(ship);
        coords_of_ship[ship] = mas_of_coords;

        this->put_new_ships(ship);
    }
}

Manager_of_ships* Playground::return_manager(){
    return list_of_ships;
}

void Playground::put_new_ships(Ship* ship){
    for (Coords j: coords_of_ship[ship])
        arr_of_ground[j.y][j.x] = SHIP;
}

void Playground::shoot(Coords coord){
    int index;
    if (arr_of_ground[coord.y][coord.x] == SHIP){
        for (const auto& [ship, coords] : coords_of_ship){
            index = 0;
            for (Coords c: coords_of_ship[ship]){
                if (c.x == coord.x && c.y == coord.y){
                    ship->shoot_to_segment(index);
                    std::cout << "popal epta" << std::endl;
                    index = -1;
                    break;
                }
                index++;
            }
            if (index == -1)
                break;
        }
    }
    else
        std::cout << "sosi huy loh" << std::endl;
}

void Playground::print_ground(){
    for (int i = 0; i < height; i++){
        std::cout << "| ";
        for (int j = 0; j < width; j++)
            std::cout << arr_of_ground[i][j] << " ";
        std::cout << "|\n";
    }
}