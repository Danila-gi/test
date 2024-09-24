#include "Playground.h"
#include <map>
#include <vector>
#include <memory>

Playground::Playground(int p_width, int p_heigth)
{
    if (p_heigth <= 0 || p_width <= 0)
        exit(0);
    height = p_heigth;
    width = p_width;
    arr_of_ground = new Statement_of_the_coord*[height];
    for (int i = 0; i < height; i++){
        arr_of_ground[i] = new Statement_of_the_coord[width];
        for (int j = 0; j < width; j++)
            arr_of_ground[i][j] = EMPTY;
    }
    list_of_ships = new Manager_of_ships;
}

Playground::~Playground(){
    for(int i = 0; i < height; i++)
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

void Playground::check_ship(Ship ship, int index, Coords coord){
    std::vector<Coords> mas_of_coords;
    bool flag = true;
    if (ship.get_location() == Horizontal){
        for (int j = 0; j < ship.get_length(); j++){
            if (check_point({coord.x + j, coord.y}))
                mas_of_coords.push_back({coord.x + j, coord.y});
            else{
                flag = false;
                break;
            }
        }
    }
    else{
        for (int j = 0; j < ship.get_length(); j++){
            if (check_point({coord.x, coord.y + j}))
                mas_of_coords.push_back({coord.x, coord.y + j});
            else{
                flag = false;
                break;
            }
        }
    }

    if (flag){
        //list_of_ships->add_ship(static_cast<Length_of_the_ship>(ship.get_length()), ship.get_location());
        coords_of_ship[index] = mas_of_coords;

        this->put_new_ships(index);
    }
    else{
        list_of_ships->remove_ship(index);
    }
}

void Playground::set_manager_with_coords(Manager_of_ships* manager, std::vector<Coords> coords){
    list_of_ships = manager;
    for (int i = 0; i < list_of_ships->get_count_of_ships(); i++){
        check_ship(list_of_ships->get_arr_of_ships()[i], i, coords[i]);
    }
}

void Playground::get_ship(Length_of_the_ship length, Location location, Coords coord){
    list_of_ships->add_ship(length, location);
    check_ship(Ship(length, location), list_of_ships->get_count_of_ships() - 1, coord);
}

Manager_of_ships Playground::return_manager() const{
    return *list_of_ships;
}

void Playground::put_new_ships(int index){
    for (Coords j: coords_of_ship[index])
        arr_of_ground[j.y][j.x] = SHIP;
}

void Playground::shoot(Coords coord){
    int index;
    if (arr_of_ground[coord.y][coord.x] == SHIP){
        for (int i = 0; i < list_of_ships->get_count_of_ships(); i++){
            index = 0;
            for (Coords c: coords_of_ship[i]){
                if (c.x == coord.x && c.y == coord.y){
                    list_of_ships->shoot_to_ship(i, index);
                    std::cout << "popal epta " << coord.x << ":" <<coord.y<< std::endl;
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