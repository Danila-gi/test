#include "../headers/Game.h"

Game::Game(){
    this->game_state = new Game_state();
    this->painter = Paint();
    is_game_end = false;
}

Game::~Game(){
    delete game_state;
}

void Game::input_ships(std::vector<Length_of_the_ship> length_of_ships, std::vector<Coords> coords_of_ships, std::vector<Orientation> orientations_of_ships){
    game_state->getPlayer()->set_arguments(10, 10, length_of_ships, coords_of_ships, orientations_of_ships);
    game_state->getEnemy()->set_arguments(10, 10, {TWO, ONE});
    game_state->getEnemy()->put_ships();
}

bool Game::is_player_won(){
    return game_state->getEnemy()->get_playground().get_ships_count() == 0;
}

std::shared_ptr<Interface_of_builders> Game::player_ability(){
    std::shared_ptr<Interface_of_builders> builder = game_state->getPlayer()->get_player_ability();
    return builder;
}

bool Game::player_turn_ability(std::shared_ptr<Interface_of_builders> builder, Coords coords_for_abil){
    if (builder->is_need_arguments())
        return game_state->getPlayer()->use_ability(game_state->getEnemy()->get_playground(), builder, coords_for_abil);
    return game_state->getPlayer()->use_ability(game_state->getEnemy()->get_playground(), builder);
}

void Game::player_turn_shoot(Coords coords){
    game_state->getPlayer()->perform_shoot(game_state->getEnemy()->get_playground(), coords);
}

void Game::enemy_turn(){
    std::random_device rd;
    std::mt19937 generator(rd());

    while (true)
    {
        std::uniform_int_distribution<int> distribution_width(0, game_state->getPlayer()->get_playground().get_width_of_playground() - 1);
        std::uniform_int_distribution<int> distribution_height(0, game_state->getPlayer()->get_playground().get_height_of_playground() - 1);
        const int rand_coord_x = distribution_width(generator);
        const int rand_coord_y = distribution_height(generator);

        if (game_state->getPlayer()->get_playground().get_statment_of_coord({rand_coord_x, rand_coord_y}) != EMPTY){
            game_state->getEnemy()->perform_shoot(game_state->getPlayer()->get_playground(), {rand_coord_x, rand_coord_y});
            break;
        }
    }
}

void Game::start_next_round(){
    std::cout<<"Start new round!"<<std::endl;
    game_state->get_current_round()++;
    game_state->getEnemy()->clear_ships();
    game_state->getEnemy()->put_ships();
}

void Game::start_new_game(){
    game_state->get_current_round() = 1;
    is_player_turn = true;
}

void Game::save_game(const std::string& filename) {
    game_state->save(filename);
}

void Game::load_game(const std::string& filename) {
    game_state = new Game_state();

    game_state->load(filename);
}

Playground& Game::get_playground(bool is_player){
    if (is_player)
        return game_state->getPlayer()->get_playground();
    return game_state->getEnemy()->get_playground();
}