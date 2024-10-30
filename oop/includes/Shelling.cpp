#include "../headers/Shelling.h"

Shelling::Shelling() : generator(std::random_device{}()) {}

bool Shelling::perform_ability(Playground& playground){
    std::cout<<"Shelling process..\n";
    if (playground.get_ships_count() == 0)
        return false;
    while (true){
        std::uniform_int_distribution<int> distribution_width(0, playground.get_width_of_playground() - 1);
        std::uniform_int_distribution<int> distribution_height(0, playground.get_height_of_playground() - 1);
        const int rand_coord_x = distribution_width(generator);
        const int rand_coord_y = distribution_height(generator);

        if (playground.get_statment_of_coord({rand_coord_x, rand_coord_y}) == SHIP){
            if (!playground.shoot({rand_coord_x, rand_coord_y})){
                continue;
            }
        }
        else{
            continue;
        }
        return true;
    }

}