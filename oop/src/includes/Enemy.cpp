#include "../headers/Enemy.h"

Enemy::Enemy(){
}

Enemy::~Enemy(){
    delete ships_manager;
    delete playground;
}

void Enemy::set_arguments(int height, int width, std::vector<Length_of_the_ship> length_of_ships){
    this->length_of_ships = length_of_ships;
    this->coords_of_ships = coords_of_ships;
    this->orientations_of_ships = orientations_of_ships;

    playground = new Playground(height, width, nullptr);
    ships_manager = new Manager_of_ships(length_of_ships.size(), length_of_ships);
}

void Enemy::perform_shoot(Playground& enemy_playground, Coords coord){
    enemy_playground.shoot(coord);
}

Playground& Enemy::get_playground(){
    return *playground;
}

void Enemy::clear_ships(){
    ships_manager = new Manager_of_ships(length_of_ships.size(), length_of_ships);
    coords_of_ships.clear();

    int old_height = playground->get_height_of_playground();
    int old_width = playground->get_width_of_playground();

    playground = new Playground(old_height, old_width, nullptr);
}

void Enemy::put_ships(){
    std::random_device rd;
    std::mt19937 generator(rd()); 

    int index = 0;
    while (index < ships_manager->get_count_of_ships())
    {
        std::uniform_int_distribution<int> distribution_width(0, playground->get_width_of_playground() - 1);
        std::uniform_int_distribution<int> distribution_height(0, playground->get_height_of_playground() - 1);
        std::uniform_int_distribution<int> distribution_orientation(0, 1);
        const int rand_coord_x = distribution_width(generator);
        const int rand_coord_y = distribution_height(generator);
        const int rand_orientation = distribution_orientation(generator);

        ships_manager->get_ship(index).set_orientation(static_cast<Orientation>(rand_orientation));

        try{
            playground->add_ship(ships_manager->get_ship(index), {rand_coord_x, rand_coord_y});
        } catch(ShipPlacmentException &err){
            //std::cout << "Error: " << err.what() << std::endl;
            continue;
        }
        coords_of_ships.push_back({rand_coord_x, rand_coord_y});
        orientations_of_ships.push_back(static_cast<Orientation>(rand_orientation));
        index++;
    }   
}


void Enemy::serialize(FileWrapper& file) const {
    file.write(ships_manager->get_count_of_ships());
    file.write('\n');

    for (int i = 0; i < ships_manager->get_count_of_ships(); i++){
        file.write(static_cast<int>(length_of_ships[i]));
        file.write(' ');
    }
    file.write('\n');

    for (int i = 0; i < ships_manager->get_count_of_ships(); i++){
        file.write(static_cast<int>(ships_manager->get_ship(i).get_orientation()));
        file.write(' ');
        for (int j = 0; j < ships_manager->get_ship(i).get_length(); j++){
            file.write(static_cast<int>(ships_manager->get_ship(i).get_segment_by_index(j)));
            file.write(' ');
        }
        file.write('\n');
    }
    playground->serialize(file);

    for (int i = 0; i < ships_manager->get_count_of_ships(); i++){
        file.write(coords_of_ships[i].x);
        file.write(' ');
        file.write(coords_of_ships[i].y);
        file.write('\n');
    }
}

void Enemy::deserialize(FileWrapper& file) {
    int ships_count;
    file.read(ships_count);
    for (int i = 0; i < ships_count; i++){
        int l;
        file.read(l);
        length_of_ships.push_back(static_cast<Length_of_the_ship>(l));
    }
    ships_manager = new Manager_of_ships(ships_count, length_of_ships);

    for (int i = 0; i < ships_count; i++){
        int orientation;
        file.read(orientation);
        ships_manager->get_ship(i).set_orientation(static_cast<Orientation>(orientation));
        for (int j = 0; j < ships_manager->get_ship(i).get_length(); j++){
            int segment;
            file.read(segment);
            if (segment == 1){
                ships_manager->get_ship(i).shoot_to_segment(j);
            }
            else if (segment == 0){
                ships_manager->get_ship(i).shoot_to_segment(j);
                ships_manager->get_ship(i).shoot_to_segment(j);
            }
        }
    }
    int width, height;
    file.read(height);
    file.read(width);

    playground = new Playground(height, width, nullptr);
    playground->deserialize(file);

    for (int i = 0; i < ships_count; i++){
        int x, y;
        file.read(x);
        file.read(y);
        playground->add_ship(ships_manager->get_ship(i), {x, y});
        coords_of_ships.push_back({x, y});
    }
}