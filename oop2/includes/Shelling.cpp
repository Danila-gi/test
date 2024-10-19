#include "../headers/Shelling.h"

Shelling::Shelling() : generator(std::random_device{}()) {}

bool Shelling::perform_ability(Playground& playground){
    std::cout<<"Shelling process..\n";
    while (true){
        std::uniform_int_distribution<int> distribution(0, playground.coords_of_ship.size() - 1);
        const int rand_index_for_key = distribution(generator);

        std::vector<Coords> coords;
        int index = 0;
        for (const auto& pair : playground.coords_of_ship) {
            if (pair.first->is_destroyed()){
                index = -1;
                break;
            }
            if (index == rand_index_for_key) {
                coords = pair.second;
                break;
            }
            index++;
        }
        if (index == -1)
            continue;

        std::uniform_int_distribution<int> vector_distribution(0, coords.size() - 1);
        int rand_index_for_vector = vector_distribution(generator);
        playground.shoot(coords[rand_index_for_vector]);
        return true;
    }

}