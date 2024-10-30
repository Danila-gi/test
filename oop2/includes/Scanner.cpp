#include "../headers/Scanner.h"

Scanner::Scanner(Coords p_coords):coords(p_coords){}

Scanner::Scanner():Scanner({0, 0}){}

bool Scanner::perform_ability(Playground& playground){
    std::cout<<"Scanner result: ";
    std::cout<<"Check: "<<coords.x<<" "<<coords.y<<std::endl;
    for (int Y = coords.y; Y < playground.get_height_of_playground() && Y < coords.y + 2; Y++){
        for (int X = coords.x; X < playground.get_width_of_playground() && X < coords.x + 2; X++){
            if (playground.get_statment_of_coord({X, Y}) == SHIP)
                return true;
        }
    }
    return false;
}