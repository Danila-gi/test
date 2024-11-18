#include "../headers/Game.h"

Game::Game(){
    this->player = std::make_unique<Player>();
    this->enemy = std::make_unique<Enemy>();
    this->painter = Paint();
}

void Game::play(){

    bool is_player_turn = true;
    while (true)
    {
        if (is_player_turn){
            painter.print_your_ground(player->get_playground());
            std::cout<< "-----------------------------------"<<std::endl;
            painter.print_enemy_ground(enemy->get_playground());
            std::cout<<"Are you need ability?"<<std::endl;
            bool ability;
            std::cin >> ability;
            this->player_turn(ability);

            if (enemy->get_playground().get_ships_count() == 0){
                std::cout << "You won!" << std::endl;
                return;
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

    std::uniform_int_distribution<int> distribution_width(0, player->get_playground().get_width_of_playground() - 1);
    std::uniform_int_distribution<int> distribution_height(0, player->get_playground().get_height_of_playground() - 1);
    const int rand_coord_x = distribution_width(generator);
    const int rand_coord_y = distribution_height(generator);

    enemy->perform_shoot(player->get_playground(), {rand_coord_x, rand_coord_y});
}