#include "../headers/Shelling.h"

void Shelling::perform_ability(Playground& playground){
    srand((unsigned int)time(NULL));
    const int rand_index_for_key = rand() % playground.coords_of_ship.size();
    std::vector<Coords> coords;
    int index = 0;
    for (const auto& pair: playground.coords_of_ship){
        if (index == rand_index_for_key){
            coords = pair.second;
            break;
        }
        index++;
    }

    srand((unsigned int)time(NULL));
    int rand_index_for_vector = rand() % coords.size();
    playground.shoot(coords[rand_index_for_vector]);

}

void Shelling::perform_ability(Playground& playground, Coords coord){
    throw "Incorrect arguments";
};