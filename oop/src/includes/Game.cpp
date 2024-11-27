#include "../headers/Game.h"

Game::Game(){
    this->game_state = new Game_state();
    this->painter = Paint();
    is_game_end = false;
}

Game::~Game(){
    delete game_state;
}

void Game::input_ships(){
    int ships_count = 10;
    std::vector<Length_of_the_ship> length_of_ships = {FOUR, THREE, THREE, TWO, TWO, TWO, ONE, ONE, ONE, ONE};
    std::vector<Length_of_the_ship> l_for_enemy = {TWO, ONE};
    std::vector<Coords> coords_of_ships = {{2, 2}, {3, 4}, {0, 0}, {6, 0}, {1, 6}, {7, 4}, {0, 4}, {4, 0}, {9, 0}, {7, 7}};
    std::vector<Orientation> orientations_of_ships = {Horizontal, Vertical, Vertical, Horizontal, Vertical, Horizontal, Vertical, Vertical, Horizontal, Horizontal};

    game_state->getPlayer()->set_arguments(10, 10, length_of_ships, coords_of_ships, orientations_of_ships);
    game_state->getEnemy()->set_arguments(10, 10, l_for_enemy);
    game_state->getEnemy()->put_ships();
}

void Game::play(){
    if (is_game_end)
        return;
    std::cout << "Round number: " << game_state->get_current_round() << std::endl;
    while (!is_game_end)
    {
        if (is_player_turn){
            painter.print_your_ground(game_state->getPlayer()->get_playground());
            std::cout<< "-----------------------------------"<<std::endl;
            painter.print_enemy_ground(game_state->getEnemy()->get_playground());
            std::cout<<"Are you need ability? - 1"<<std::endl;
            std::cout<<"Save game? - 2"<<std::endl;
            std::cout<<"Continue game - 0"<<std::endl;
            std::cout<<"End game - 3"<<std::endl;
            int flag;
            std::cin >> flag;
            if (flag == 3){
                is_game_end = true;
                return;
            }
            if (flag == 2){
                this->save_game("../game.txt");
                continue;
            }
            this->player_turn((flag == 1));

            std::cout<<game_state->getEnemy()->get_playground().get_ships_count()<<std::endl;
            if (game_state->getEnemy()->get_playground().get_ships_count() == 0){
                std::cout << "You won!" << std::endl;
                this->start_next_round();
            }
            is_player_turn = false;
        }

        else{
            this->enemy_turn();
            if (game_state->getPlayer()->get_playground().get_ships_count() == 0){
                std::cout << "You loss!" << std::endl;
                return;
            }
            is_player_turn = true;
        }
    }
    
}

void Game::player_turn(bool is_need_ability){
    if (is_need_ability){
        game_state->getPlayer()->use_ability(game_state->getEnemy()->get_playground());
    }
    std::cout<<"Print coords"<<std::endl;
    int x, y;
    std::cin >> x >> y;
    game_state->getPlayer()->perform_shoot(game_state->getEnemy()->get_playground(), {x, y});
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
    if (!is_game_end)
        this->play();
}

void Game::start_new_game(){
    game_state->get_current_round() = 1;
    is_player_turn = true;

    std::cout<<"Start new game!"<<std::endl;
    int choose_start;
    std::cout << "Choose. Input ships (0) or load game (1)" << std::endl;
    std::cin >> choose_start;
    if (choose_start == 0){
        input_ships();
    }
    else if (choose_start == 1){
        this->load_game("../game.txt");
    }
    if (!is_game_end)
        this->play();
}

void Game::save_game(const std::string& filename) {
    game_state->save(filename);
}

void Game::load_game(const std::string& filename) {
    game_state = new Game_state();

    game_state->load(filename);
}