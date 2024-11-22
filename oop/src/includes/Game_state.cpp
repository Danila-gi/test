#include "../headers/Game_state.h"

Game_state::Game_state(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, int& current_round):
player(player), enemy(enemy), current_round(current_round) {}

void Game_state::save(const std::string& filename) const{
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for saving");
    }

    file << *this;
}

void Game_state::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file for loading");
    }

    file >> *this;
}

std::ostream& operator<<(std::ostream& os, const Game_state& state) {
    os << state.current_round << "\n";
    state.player->serialize(os);
    std::cout<<"Good player save\n";
    state.enemy->serialize(os);
    std::cout<<"Good enemy save\n";

    return os;
}

std::istream& operator>>(std::istream& is, Game_state& state) {
    is >> state.current_round;
    state.player->deserialize(is);
    state.enemy->deserialize(is);
    return is;
}

std::shared_ptr<Player> Game_state::getPlayer() const { return player; }
std::shared_ptr<Enemy> Game_state::getEnemy() const { return enemy; }