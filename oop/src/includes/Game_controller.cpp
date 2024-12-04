#include "../headers/Game_controller.h"

template <typename InputType, typename OutputType>
Game_controller<InputType, OutputType>::Game_controller(Game* game):game(game){
    input = new InputType();
    output = new OutputType();
}

template <typename InputType, typename OutputType>
void Game_controller<InputType, OutputType>::play(){
    input->load_commands("../arguments.txt");
    game->start_new_game();
    output->print_commands(input->get_map_of_commands());
    COMMAND command = input->read_command();
    if (command == INPUT_SHIPS){
        std::vector<Length_of_the_ship> length_of_ships;
        std::vector<Coords> coords_of_ships;
        std::vector<Orientation> orientations_of_ships;
        input->read_ships(length_of_ships, coords_of_ships, orientations_of_ships);
        game->input_ships(length_of_ships, coords_of_ships, orientations_of_ships);
    }
    else if (command == LOAD){
        game->load_game("../game.txt");
    }
    else {
        this->play();
    }
    Paint painter = Paint();
    bool flag = true;
    while (flag)
    {
        output->print_playground(painter, true, game->get_playground(true));
        std::cout<<"======================================="<<std::endl;
        output->print_playground(painter, true, game->get_playground(false));
        COMMAND command = input->read_command();
        switch (command)
        {
        case ABILITY:{
            std::shared_ptr<Interface_of_builders> builder = game->player_ability();
            if (!builder)
                continue;
            output->print_ability_process(builder);
            if (builder->is_need_arguments()){
                std::cout<<"Print coords for ability"<<std::endl;
                Coords coords_for_abil = input->read_coords();
                std::cout<<game->player_turn_ability(builder, coords_for_abil)<<std::endl;
            }
            else{
                game->player_turn_ability(builder);
            }
        }
        case ATACK:{
            Coords coords = input->read_coords();
            game->player_turn_shoot(coords);
            if (game->is_player_won()){
                game->start_next_round();
                continue;
            }
            break;
        }

        case SAVE:{
            game->save_game("../game.txt");
            continue;
            break;
        }

        case EXIT:{
            flag = false;
            continue;
            break;
        }
        
        default:
            break;
        }
        game->enemy_turn();
    }
    
}

template class Game_controller<Input_from_terminal, Output_to_terminal>;