#include "../headers/Player.h"

Player::Player(){
    std::vector<Length_of_the_ship> length = {FOUR, THREE, THREE, TWO, TWO, TWO, ONE, ONE, ONE, ONE};
    ships_manager = new Manager_of_ships(10, length);

    get_cor = new Get_coords(coords_for_scanner);
    maker = new Ability_maker(get_cor);
    ability_manager = new Manager_of_abilities(*maker);
    add_abil = new Add_ability(*ability_manager);

    playground = new Playground(10, 10, nullptr);

    this->put_ships();
}

void Player::perform_shoot(Playground& enemy_playground, Coords coord){
    enemy_playground.set_command(add_abil);
    try{
        enemy_playground.shoot(coord);
    } catch(AtackException &err){
        std::cout << "Error: " << err.what() << std::endl;
    }
}

void Player::use_ability(Playground& enemy_playground){
    try
    {
        auto get = ability_manager->get_ability();
        if (get->is_need_arguments()){
            std::cout<<"Print coords"<<std::endl;
            int x, y;
            std::cin >> x >> y;
            coords_for_scanner = {x, y};
            auto ex = get->make_ability();
            std::cout<<ex->perform_ability(enemy_playground)<<std::endl;
        }
        else{
            auto ex = get->make_ability();
            ex->perform_ability(enemy_playground);
        }
    } catch (NoAbilitiesException &err) 
    {
        std::cout << "Error: " << err.what() << std::endl;
    }
}

Playground& Player::get_playground(){
    return *playground;
}

void Player::put_ships(){
    std::vector<Coords> c = {{2, 2}, {3, 4}, {0, 0}, {6, 0}, {1, 6}, {7, 4}, {0, 4}, {4, 0}, {9, 0}, {7, 7}};
    std::vector<Orientation> o = {Horizontal, Vertical, Vertical, Horizontal, Vertical, Horizontal, Vertical, Vertical, Horizontal, Horizontal};
    int index = 0;
    while (index < ships_manager->get_count_of_ships())
    {
        ships_manager->get_ship(index).set_orientation(o[index]);
        try{
            playground->add_ship(ships_manager->get_ship(index), c[index]);
        } catch(ShipPlacmentException &err){
            std::cout << "Error: " << err.what() << std::endl;
            continue;
        }
        index++;
    }    
}