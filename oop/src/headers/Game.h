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
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;
    Paint painter;

    void get_ships_for_player(Manager_of_ships& manager);
    void get_ships_for_enemy(Manager_of_ships& manager, Playground playground_player);

    bool is_player_turn;
    int current_round;

public:
    Game();

    void play();

    void start_new_game();

    void player_turn(bool is_need_ability);

    void enemy_turn();

    void start_next_round();

    void save_game(const std::string& filename);

    void load_game(const std::string& filename);
};

#endif