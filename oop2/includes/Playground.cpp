#include "../headers/Playground.h"

Playground::Playground(int p_width, int p_heigth, Command_ability* p_command)
:height(p_heigth), width(p_width), command(p_command),
original_shoot([this](Coords coord, Ship* ship, int index){return this->shoot_with_n_damage(coord, ship, index, 1);})
{
    if (p_heigth <= 0 || p_width <= 0){
        std::cout<<"Incorrect sizes"<<std::endl;
        return;
    }
    arr_of_ground = new Statement_of_the_coord*[height];

    for (int i = 0; i < height; i++){
        arr_of_ground[i] = new Statement_of_the_coord[width];
        for (int j = 0; j < width; j++)
            arr_of_ground[i][j] = UNKNOWN;
    }
}

Playground::Playground():Playground(0, 0, nullptr){}

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

bool Playground::check_ship(Ship* ship, Coords coord){
    std::vector<Coords> mas_of_coords;
    bool flag = true;
    if (ship->get_orientation() == Horizontal){
        for (int j = 0; j < ship->get_length(); j++){
            if (check_point({coord.x + j, coord.y}))
                mas_of_coords.push_back({coord.x + j, coord.y});
            else{
                throw ShipPlacmentException(coord.x + j, coord.y);
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
                throw ShipPlacmentException(coord.x, coord.y + j);
                flag = false;
                break;
            }
        }
    }

    if (flag){
        coords_of_ship[ship] = mas_of_coords;
        return true;
    }
    else{
        return false;
    }
}

void Playground::add_ship(Ship& ship, Coords coord){
    if (check_ship(&ship, coord)){
        this->put_new_ships(&ship);
        count_of_ships++;
    }
}

void Playground::put_new_ships(Ship* ship){
    for (Coords j: coords_of_ship[ship])
        arr_of_ground[j.y][j.x] = SHIP;
}

void Playground::set_multiple_attack(int num_attacks) {
    original_shoot = [this, num_attacks](Coords coord, Ship* ship, int index) {
        return shoot_with_n_damage(coord, ship, index, num_attacks);
    };
}

bool Playground::shoot_with_n_damage(Coords coord, Ship* ship, int index, int damage){
    for (int i = 0; i < damage; i++)
        ship->shoot_to_segment(index);
    if (damage == 1){
        std::cout<< "good hit " << coord.x << ":" << coord.y << std::endl;
        return true;
    }
    std::cout<< "good " << damage << "-force hit " << coord.x << ":" << coord.y << std::endl;
    set_multiple_attack(1);
    return true;
}

bool Playground::shoot(Coords coord) {
    if (coord.x < 0 || coord.x >= width || coord.y < 0 || coord.y >= height){
        throw AtackException(coord.x, coord.y);
    }
    int index;
    if (arr_of_ground[coord.y][coord.x] == SHIP){
        for (const auto& pair: coords_of_ship){
            index = 0;
            for (Coords c: coords_of_ship[pair.first]){
                if (c.x == coord.x && c.y == coord.y){
                    if (pair.first->is_destroyed()){
                        std::cout<<"Ship has already destroyed"<<std::endl;
                        set_multiple_attack(1);
                        return false;
                    }
                    original_shoot(coord, pair.first, index);
                    index = -1;
                    if (pair.first->is_destroyed()){
                        std::cout<<"Nice, you have destroyed a ship!\n";
                        command->add_ability();
                    }
                    return true;
                }
                index++;
            }
        }
    }
    arr_of_ground[coord.y][coord.x] = EMPTY;
    std::cout << "miss " << coord.x << ":" << coord.y <<std::endl;
    return false;
    //return (this->*original_shoot)(coord);
}

void Playground::print_ground(){
    for (int i = 0; i < height; i++){
        std::cout << "| ";
        for (int j = 0; j < width; j++)
            std::cout << arr_of_ground[i][j] << " ";
        std::cout << "|\n";
    }
}

int Playground::get_ships_count() const{
    return count_of_ships;
}

int Playground::get_width_of_playground() const{
    return width;
}

int Playground::get_height_of_playground() const{
    return height;
}

Statement_of_the_coord Playground::get_statment_of_coord(Coords coord) const{
    return arr_of_ground[coord.y][coord.x];
}

Playground::Playground(const Playground &obj)
    : width(obj.width), height(obj.height), command(obj.command)
{
    arr_of_ground = new Statement_of_the_coord*[height];
    for (int i = 0; i < height; i++){
        arr_of_ground[i] = new Statement_of_the_coord[width];
        for (int j = 0; j < width; j++)
            arr_of_ground[i][j] = obj.arr_of_ground[i][j];
    }

    coords_of_ship = obj.coords_of_ship;
}

Playground::Playground(Playground &&obj)
    : width(obj.width), height(obj.height), coords_of_ship(std::move(obj.coords_of_ship)), arr_of_ground(nullptr)
{
    obj.width = 0;
    obj.height = 0;
    std::swap(arr_of_ground, obj.arr_of_ground);
    std::swap(command, obj.command);
}

Playground& Playground::operator=(const Playground &obj)
{
    if (this != &obj)
    {
        for(int i = 0; i < height; i++)
            delete[] arr_of_ground[i];
        delete[] arr_of_ground;

        width = obj.width;
        height = obj.height;
        coords_of_ship = obj.coords_of_ship;

        arr_of_ground = new Statement_of_the_coord*[height];
        for (int i = 0; i < height; i++){
            arr_of_ground[i] = new Statement_of_the_coord[width];
            for (int j = 0; j < width; j++)
                arr_of_ground[i][j] = obj.arr_of_ground[i][j];
        command = obj.command;
        }
    }
    return *this;
}

Playground& Playground::operator=(Playground &&obj)
{
    if (this != &obj)
    {
        std::swap(width, obj.width);
        std::swap(height, obj.height);
        std::swap(coords_of_ship, obj.coords_of_ship);

        std::swap(arr_of_ground, obj.arr_of_ground);
        std::swap(command, obj.command);
    }
    return *this;
}