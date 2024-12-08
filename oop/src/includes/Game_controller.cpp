#include "../headers/Game_controller.h"

template <typename InputType, typename OutputType, typename PaintType>
Game_controller<InputType, OutputType, PaintType>::Game_controller(Game* game):game(game), display(){
    input = new InputType();
    output = new OutputType();
}

template <typename InputType, typename OutputType, typename PaintType>
Game_controller<InputType, OutputType, PaintType>::~Game_controller(){
    delete input;
    delete output;
}

template <typename InputType, typename OutputType, typename PaintType>
void Game_controller<InputType, OutputType, PaintType>::start_init(){
    input->load_commands("../arguments.txt");
    game->start_new_game();

    display.print_commands(input->get_map_of_commands());
    bool flag_correct_command = false;

    while (!flag_correct_command)
    {
        display.execute_message("input_command");
        COMMAND command = input->read_command();
        if (command == INPUT_SHIPS){
            std::vector<Length_of_the_ship> length_of_ships;
            std::vector<Coords> coords_of_ships;
            std::vector<Orientation> orientations_of_ships;
            display.execute_message("input_ships");
            input->read_ships(length_of_ships, coords_of_ships, orientations_of_ships);
            game->input_ships(length_of_ships, coords_of_ships, orientations_of_ships);
            flag_correct_command = true;
        }
        else if (command == LOAD){
            try
            {
                game->load_game("../game.txt");
            }
            catch(const std::runtime_error& e)
            {
                std::cerr << e.what() << '\n';
                continue;
            }
            flag_correct_command = true;
        }
        else if (command == EXIT){
            flag_correct_command = true;
            return;
        }
    }

}

template <typename InputType, typename OutputType, typename PaintType>
void Game_controller<InputType, OutputType, PaintType>::play(){
    this->start_init();

    bool flag = true;
    display.print_round(game->get_round_number());
    while (flag)
    {
        display.print_player_ground(game->get_playground(true));
        display.execute_message("line");
        display.print_player_ground(game->get_playground(false));
        display.execute_message("input_command");
        COMMAND command = input->read_command();

        switch (command)
        {
        case ABILITY:{
            std::shared_ptr<Interface_of_builders> builder = game->player_ability();
            if (!builder)
                continue;
            display.print_builder(builder->get_name());
            if (builder->is_need_arguments()){
                display.execute_message("input_coords");
                Coords coords_for_abil = input->read_coords();
                display.print_scanner_result(game->player_turn_ability(builder, coords_for_abil));
            }
            else{
                game->player_turn_ability(builder);
            }
        }

        case ATACK:{
            display.execute_message("input_coords");
            Coords coords = input->read_coords();
            bool shoot = game->player_turn_shoot(coords);
            display.print_player_shoot_result(shoot, coords);

            if (game->is_player_won()){
                game->start_next_round();
                display.print_round(game->get_round_number());
                continue;
            }

            if (game->is_ship_destroyed())
                display.execute_message("new_ability");
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
        
        default:{
            continue;
            break;
        }
        }
        Coords coord = game->enemy_turn();
        display.print_enemy_turn(coord);
    }
    
}

template class Game_controller<Input_from_terminal, Output_to_terminal, Paint>;