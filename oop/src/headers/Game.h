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
#include "SaveLoad.h"

class Game{
private:
    Game_state game_state;

    bool is_player_turn;
    bool is_game_end;
    bool is_new_ship_destroyed;

public:
    Game();

    ~Game();

    void input_ships(int height, int width, std::vector<Length_of_the_ship> length_of_ships, std::vector<Coords> coords_of_ships, std::vector<Orientation> orientations_of_ships);

    bool is_player_won();
    bool is_player_loss();

    void start_new_game();

    std::shared_ptr<Interface_of_builders> player_ability();

    bool player_turn_ability(std::shared_ptr<Interface_of_builders> builder, Coords coords_for_abil={0, 0});
    bool player_turn_shoot(Coords coords);

    Coords enemy_turn();

    bool is_ship_destroyed();

    void start_next_round();

    void save_game(const std::string& filename);

    void load_game(const std::string& filename);

    Playground& get_playground(bool is_player);

    int get_round_number();
};

#endif