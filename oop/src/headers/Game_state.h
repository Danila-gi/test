#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "FileWrapper.h"

class Game_state {
private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;
    int& current_round;
    //bool is_player_turn;

public:
    Game_state(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, int& current_round);
    void save(const std::string& filename) const;
    void load(const std::string& filename);
    friend FileWrapper& operator<<(FileWrapper& file, const Game_state& state);
    friend FileWrapper& operator>>(FileWrapper& file, Game_state& state);

    std::shared_ptr<Player> getPlayer() const;
    std::shared_ptr<Enemy> getEnemy() const;
};

#endif