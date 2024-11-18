#include "../headers/Enemy.h"

Enemy::Enemy(){
    std::vector<Length_of_the_ship> length = {TWO, ONE};
    ships_manager = new Manager_of_ships(2, length);

    playground = new Playground(10, 10, nullptr);

    this->put_ships();
}

void Enemy::perform_shoot(Playground& enemy_playground, Coords coord){
    enemy_playground.shoot(coord);
}

Playground& Enemy::get_playground(){
    return *playground;
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
        index++;
    }   
}