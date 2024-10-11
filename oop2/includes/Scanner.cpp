#include "../headers/Scanner.h"

void Scanner::perform_ability(Playground& playground){
    throw "Incorrect arguments";
}

void Scanner::perform_ability(Playground& playground, Coords coord){
    for (int Y = coord.y; Y < playground.height && Y < coord.y + 2; Y++){
        for (int X = coord.x; X < playground.width && X < coord.x + 2; X++){
            if (playground.arr_of_ground[Y][X] == SHIP)
                std::cout<<"S ";
            else
                std::cout<<"E ";
        }
        std::cout<<std::endl;
    }
}