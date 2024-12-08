#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <iostream>
#include "Game_state.h"

class SaveLoad{
private:
    const std::string& filename;

public:
    SaveLoad(const std::string& filename);

    void save_game(const Game_state& game_state);

    void load_game(Game_state& game_state);

    void save_hash(FileWrapper& file_hash);
    int count_hash();
};

#endif