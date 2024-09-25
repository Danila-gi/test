#include "Playground.h"

Playground::Playground(int p_width, int p_heigth, Manager_of_ships& manager, std::vector<Coords> coords)
:list_of_ships(manager), height(p_heigth), width(p_width)
{
    if (p_heigth <= 0 || p_width <= 0)
        exit(0);
    arr_of_ground = new Statement_of_the_coord*[height];
    if (arr_of_ground == NULL)
        exit(0);
    for (int i = 0; i < height; i++){
        arr_of_ground[i] = new Statement_of_the_coord[width];
        if (arr_of_ground[i] == NULL)
            exit(0);
        for (int j = 0; j < width; j++)
            arr_of_ground[i][j] = UNKNOWN;
    }

    int i = 0;
    int j = 0;
    while (i < list_of_ships.get_count_of_ships()){
        if (j >= coords.size()){
            list_of_ships.remove_ship(i);
            continue;
        }
        if (check_ship(list_of_ships.get_arr_of_ships()[i], i, coords[j]))
            i++;
        j++;
    }
}

Playground::~Playground(){
    for(int i = 0; i < height; i++)
        delete[] arr_of_ground[i];
    delete[] arr_of_ground;
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

bool Playground::check_ship(Ship ship, int index, Coords coord){
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
        coords_of_ship[index] = mas_of_coords;

        this->put_new_ships(index);
        return true;
    }
    else{
        list_of_ships.remove_ship(index);
        return false;
    }
}

void Playground::add_ship(Length_of_the_ship length, Location location, Coords coord){
    list_of_ships.add_ship(length, location);
    check_ship(Ship(length, location), list_of_ships.get_count_of_ships() - 1, coord);
}

Manager_of_ships Playground::return_manager() const{
    return list_of_ships;
}

void Playground::put_new_ships(int index){
    for (Coords j: coords_of_ship[index])
        arr_of_ground[j.y][j.x] = SHIP;
}

void Playground::shoot(Coords coord){
    if (coord.x < 0 || coord.x >= width || coord.y < 0 || coord.y >= height){
        std::cout<<"Incorrect coords"<<std::endl;
        return;
    }
    int index;
    if (arr_of_ground[coord.y][coord.x] == SHIP){
        for (int i = 0; i < list_of_ships.get_count_of_ships(); i++){
            index = 0;
            for (Coords c: coords_of_ship[i]){
                if (c.x == coord.x && c.y == coord.y){
                    list_of_ships.shoot_to_ship(i, index);
                    std::cout << "good hit " << coord.x << ":" << coord.y << std::endl;
                    index = -1;
                    break;
                }
                index++;
            }
            if (index == -1)
                break;
        }
    }
    else{
        arr_of_ground[coord.y][coord.x] = EMPTY;
        std::cout << "miss " << coord.x << ":" << coord.y <<std::endl;
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

Playground::Playground(const Playground &obj)
    : width(obj.width), height(obj.height), list_of_ships(obj.list_of_ships),
    coords_of_ship(obj.coords_of_ship)
{
    arr_of_ground = new Statement_of_the_coord*[height];
    if (arr_of_ground == NULL)
        exit(0);
    for (int i = 0; i < height; i++){
        arr_of_ground[i] = new Statement_of_the_coord[width];
        if (arr_of_ground[i] == NULL)
            exit(0);
        for (int j = 0; j < width; j++)
            arr_of_ground[i][j] = obj.arr_of_ground[i][j];
    }
}

Playground::Playground(Playground &&obj)
    : width(obj.width), height(obj.height), list_of_ships(obj.list_of_ships),
    coords_of_ship(std::move(obj.coords_of_ship)), arr_of_ground(obj.arr_of_ground)
{
    obj.arr_of_ground = nullptr;
    obj.width = 0;
    obj.height = 0;
}

Playground& Playground::operator=(const Playground &obj)
{
    if (this != &obj)
    {
        width = obj.width;
        height = obj.height;
        list_of_ships = obj.list_of_ships;
        coords_of_ship = obj.coords_of_ship;

        arr_of_ground = new Statement_of_the_coord*[height];
        for (int i = 0; i < height; i++){
            arr_of_ground[i] = new Statement_of_the_coord[width];
            for (int j = 0; j < width; j++)
                arr_of_ground[i][j] = obj.arr_of_ground[i][j];
        }
    }
    return *this;
}

Playground& Playground::operator=(Playground &&obj)
{
    if (this != &obj)
    {
        width = obj.width;
        height = obj.height;
        list_of_ships = obj.list_of_ships;
        coords_of_ship = std::move(obj.coords_of_ship);

        for (int i = 0; i < height; ++i) {
            delete[] arr_of_ground[i];
        }
        delete[] arr_of_ground;

        arr_of_ground = obj.arr_of_ground;

        obj.arr_of_ground = nullptr;
        obj.width = 0;
        obj.height = 0;
    }
    return *this;
}