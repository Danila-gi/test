#include "../headers/SaveLoad.h"

SaveLoad::SaveLoad(const std::string& filename):filename(filename){}

void SaveLoad::save_game(const Game_state& game_state){
    FileWrapper file(filename, std::ios::out | std::ios::trunc);

    file << game_state;

    FileWrapper file_hash("../hash.txt", std::ios::out | std::ios::trunc);
    file.rewind();
    save_hash(file_hash);
}

void SaveLoad::load_game(Game_state& game_state){
    FileWrapper file(filename, std::ios::in);
    FileWrapper file_hash("../hash.txt", std::ios::in);

    int hash_count = this->count_hash();
    int has_original;
    file_hash.read(has_original);
    if (has_original != hash_count){
        throw std::runtime_error("Incorrect file!");
    }
    file.rewind();

    file >> game_state;
}

void SaveLoad::save_hash(FileWrapper& file_hash){
    file_hash.write(this->count_hash());
}
int SaveLoad::count_hash(){
    FileWrapper file_read(filename, std::ios::in);
    int hash = 0;
    int x = 0;
    int index = 1;
    while (file_read.read(x)){
        hash += (x * (index % 10));
        index++;
    }
    return hash;
}