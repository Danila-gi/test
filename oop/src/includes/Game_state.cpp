#include "../headers/Game_state.h"

Game_state::Game_state(){
    this->player = std::make_shared<Player>();
    this->enemy = std::make_shared<Enemy>();
    current_round = 1;
}

void Game_state::save(const std::string& filename) const{
    FileWrapper file(filename, std::ios::out | std::ios::trunc);

    file << *this;

    FileWrapper file_hash("../hash.txt", std::ios::out | std::ios::trunc);
    
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

std::shared_ptr<Player> Game_state::getPlayer() { return player; }
std::shared_ptr<Enemy> Game_state::getEnemy() { return enemy; }
int& Game_state::get_current_round() {return current_round;}

void Game_state::save_hash(FileWrapper& file_read, FileWrapper& file_hash){
    int hash = 0;
    int x;
    while (file_read.read(x)){
        hash += x;
    }
    file_hash.write(hash);
}