#include "../headers/Game_state.h"

Game_state::Game_state(std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy, int& current_round):
player(player), enemy(enemy), current_round(current_round) {}

void Game_state::save(const std::string& filename) const{
    FileWrapper file(filename, std::ios::out | std::ios::trunc);

    file << *this;
}

void Game_state::load(const std::string& filename) {
    FileWrapper file(filename, std::ios::in);

    file >> *this;
}

FileWrapper& operator<<(FileWrapper& file, const Game_state& state) {
    file.write(state.current_round);
    file.write('\n');

    state.player->serialize(file);
    std::cout<<"Good player save\n";
    state.enemy->serialize(file);
    std::cout<<"Good enemy save\n";

    return file;
}

FileWrapper& operator>>(FileWrapper& file, Game_state& state) {
    file.read(state.current_round);
    state.player->deserialize(file);
    state.enemy->deserialize(file);
    return file;
}

std::shared_ptr<Player> Game_state::getPlayer() const { return player; }
std::shared_ptr<Enemy> Game_state::getEnemy() const { return enemy; }