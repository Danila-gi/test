#include "../headers/Game.h"

Game::Game(){
    this->player = std::make_shared<Player>();
    this->enemy = std::make_shared<Enemy>();
    this->painter = Paint();
    current_round = 1;
    is_player_turn = true;
    game_state = new Game_state(player, enemy, is_player_turn, current_round);

    this->load_game("../game.txt");
}

void Game::play(){
    while (true)
    {
        if (is_player_turn){
            painter.print_your_ground(player->get_playground());
            std::cout<< "-----------------------------------"<<std::endl;
            painter.print_enemy_ground(enemy->get_playground());
            std::cout<<"Are you need ability? - 1"<<std::endl;
            std::cout<<"Save game? - 2"<<std::endl;
            std::cout<<"Continue game - 0"<<std::endl;
            int ability;
            std::cin >> ability;
            if (ability == 2)
                this->save_game("../game.txt");
            this->player_turn((ability == 1));

            std::cout<<enemy->get_playground().get_ships_count()<<std::endl;
            if (enemy->get_playground().get_ships_count() == 0){
                std::cout << "You won!" << std::endl;
                this->start_next_round();
            }
            is_player_turn = false;
        }

        else{
            this->enemy_turn();
            if (player->get_playground().get_ships_count() == 0){
                std::cout << "You loss!" << std::endl;
                return;
            }
            is_player_turn = true;
        }
    }
    
}

void Game::player_turn(bool is_need_ability){
    if (is_need_ability){
        player->use_ability(enemy->get_playground());
    }
    std::cout<<"Print coords"<<std::endl;
    int x, y;
    std::cin >> x >> y;
    player->perform_shoot(enemy->get_playground(), {x, y});
}

void Game::enemy_turn(){
    std::random_device rd;
    std::mt19937 generator(rd());

    while (true)
    {
        std::uniform_int_distribution<int> distribution_width(0, player->get_playground().get_width_of_playground() - 1);
        std::uniform_int_distribution<int> distribution_height(0, player->get_playground().get_height_of_playground() - 1);
        const int rand_coord_x = distribution_width(generator);
        const int rand_coord_y = distribution_height(generator);

        if (player->get_playground().get_statment_of_coord({rand_coord_x, rand_coord_y}) != EMPTY){
            enemy->perform_shoot(player->get_playground(), {rand_coord_x, rand_coord_y});
            break;
        }
    }
}

void Game::start_next_round(){
    std::cout<<"Start new round!"<<std::endl;
    current_round++;
    this->enemy = std::make_shared<Enemy>();
    game_state = new Game_state(player, enemy, is_player_turn, current_round);
    this->play();
}

void Game::start_new_game(){
    std::cout<<"Start new game!"<<std::endl;
    this->player = std::make_shared<Player>();
    this->enemy = std::make_shared<Enemy>();
    this->play();
}

void Game::save_game(const std::string& filename) {
    game_state->save(filename);
}

void Game::load_game(const std::string& filename) {
    auto tempPlayer = std::make_shared<Player>();
    auto tempEnemy = std::make_shared<Enemy>();
    Game_state tempGameState(tempPlayer, tempEnemy, 1, true);

    tempGameState.load(filename);

    delete game_state;

    game_state = new Game_state(tempGameState);

    player = game_state->getPlayer();
    enemy = game_state->getEnemy();
}