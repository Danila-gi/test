#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <random>
#include "Playground.h"
#include "Manager_of_abilities.h"
#include "Player.h"
#include "Paint.h"
#include "Enemy.h"
#include "Get_coords.h"
#include "Add_ability.h"
#include "Game_state.h"

class Game{
private:
    Game_state* game_state;
    Paint painter;

    bool is_player_turn;
    bool is_game_end;

public:
    Game();

    ~Game();

    void input_ships(std::vector<Length_of_the_ship> length_of_ships, std::vector<Coords> coords_of_ships, std::vector<Orientation> orientations_of_ships);

    bool is_player_won();

    void start_new_game();

    std::shared_ptr<Interface_of_builders> player_ability();

    bool player_turn_ability(std::shared_ptr<Interface_of_builders> builder, Coords coords_for_abil={0, 0});
    void player_turn_shoot(Coords coords);

    void enemy_turn();

    void start_next_round();

    void save_game(const std::string& filename);

    void load_game(const std::string& filename);

    Playground& get_playground(bool is_player);
};

#endif