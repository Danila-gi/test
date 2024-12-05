#include "../headers/Game_state.h"

Game_state::Game_state(){
    this->player = std::make_shared<Player>();
    this->enemy = std::make_shared<Enemy>();
    current_round = 1;
}

void Game_state::save(const std::string& filename){
    FileWrapper file(filename, std::ios::out | std::ios::trunc);

    file << *this;

    FileWrapper file_hash("../hash.txt", std::ios::out | std::ios::trunc);
    file.rewind();
    save_hash(filename, file_hash);
}

void Game_state::load(const std::string& filename) {
    FileWrapper file(filename, std::ios::in);
    FileWrapper file_hash("../hash.txt", std::ios::in);

    int hash_count = this->count_hash(filename);
    int has_original;
    file_hash.read(has_original);
    if (has_original != hash_count){
        throw std::runtime_error("Incorrect file!");
    }
    file.rewind();

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

void Game_state::save_hash(const std::string& filename, FileWrapper& file_hash){
    file_hash.write(this->count_hash(filename));
}

int Game_state::count_hash(const std::string& filename){
    FileWrapper file_read(filename, std::ios::in);
    int hash = 0;
    int x = 0;
    while (file_read.read(x)){
        hash += x;
    }
    return hash;
}