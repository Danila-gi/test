#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "Player.h"
#include "Enemy.h"

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
    friend std::ostream& operator<<(std::ostream& os, const Game_state& state);
    friend std::istream& operator>>(std::istream& is, Game_state& state);

    std::shared_ptr<Player> getPlayer() const;
    std::shared_ptr<Enemy> getEnemy() const;
};