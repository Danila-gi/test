#include "../headers/Get_coords.h"

Get_coords::Get_coords(Coords& p_coords):coords(p_coords){}

Coords Get_coords::get_coords(){
    return coords;
}