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

    void input_ships();

    void play();

    void start_new_game();

    void player_turn(bool is_need_ability);

    void enemy_turn();

    void start_next_round();

    void save_game(const std::string& filename);

    void load_game(const std::string& filename);
};

#endif