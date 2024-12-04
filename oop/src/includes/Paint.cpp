#include "../headers/Paint.h"

void Paint::print_ground(Playground& p, const char c){
    for (int i = 0; i < p.get_height_of_playground(); i++){
        std::cout << "| ";
        for (int j = 0; j < p.get_width_of_playground(); j++){
            Statement_of_the_coord statment = p.get_statment_of_coord({j, i});
            if (statment == UNKNOWN)
                std::cout<<" ? ";
            else if (statment == EMPTY)
                std::cout<<" * ";
            else{
                Statement_of_the_ship segment = p.get_ship_on_the_coord({j, i});
                if (segment == INTACT)
                    std::cout<<" " << c <<" ";
                else if (segment == DAMAGED)
                    std::cout<<" 1 ";
                else if (segment == DESTROYED)
                    std::cout<<" 0 ";

            }
        }
        std::cout << "|\n";
    }

}

void Paint::print_your_ground(Playground& p){
    print_ground(p, '2');

}

void Paint::print_enemy_ground(Playground& p){
    print_ground(p, '?');

}