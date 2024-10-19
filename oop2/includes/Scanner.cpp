#include "../headers/Scanner.h"

Scanner::Scanner(Coords p_coords):coords(p_coords){}

Scanner::Scanner():Scanner({0, 0}){}

void Scanner::set_new_coords(Coords p_coords){
    coords = p_coords;
}

bool Scanner::perform_ability(Playground& playground){
    std::cout<<"Scanner result:\n";
    for (int Y = coords.y; Y < playground.height && Y < coords.y + 2; Y++){
        for (int X = coords.x; X < playground.width && X < coords.x + 2; X++){
            if (playground.arr_of_ground[Y][X] == SHIP)
                return true;
        }
    }
    return false;
}