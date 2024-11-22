#include "../headers/Player.h"

//Player::Player(){}

Player::Player(){
    get_cor = new Get_coords(coords_for_scanner);
    maker = new Ability_maker(get_cor);
    ability_manager = new Manager_of_abilities(*maker);
    add_abil = new Add_ability(*ability_manager);
}

Player::~Player(){
    delete ships_manager;
    delete get_cor;
    delete maker;
    delete ability_manager;
    delete add_abil;
    delete playground;
}

void Player::set_arguments(int height, int width, std::vector<Length_of_the_ship> length_of_ships, std::vector<Coords> coords_of_ships, 
std::vector<Orientation> orientations_of_ships){
    this->length_of_ships = length_of_ships;
    this->coords_of_ships = coords_of_ships;
    this->orientations_of_ships = orientations_of_ships;

    playground = new Playground(height, width, nullptr);
    ships_manager = new Manager_of_ships(length_of_ships.size(), length_of_ships);

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
            enemy_playground.set_command(add_abil);
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
    int index = 0;
    while (index < ships_manager->get_count_of_ships())
    {
        ships_manager->get_ship(index).set_orientation(orientations_of_ships[index]);
        try{
            playground->add_ship(ships_manager->get_ship(index), coords_of_ships[index]);
        } catch(ShipPlacmentException &err){
            std::cout << "Error: " << err.what() << std::endl;
            continue;
        }
        index++;
    }    
}

void Player::serialize(FileWrapper& file) const {
    file.write(ships_manager->get_count_of_ships());
    file.write('\n');

    for (int i = 0; i < ships_manager->get_count_of_ships(); i++){
        file.write(static_cast<int>(length_of_ships[i]));
        file.write(' ');
    }
    file.write('\n');

    for (int i = 0; i < ships_manager->get_count_of_ships(); i++){
        file.write(static_cast<int>(ships_manager->get_ship(i).get_orientation()));
        file.write(' ');
        for (int j = 0; j < ships_manager->get_ship(i).get_length(); j++){
            file.write(static_cast<int>(ships_manager->get_ship(i).get_segment_by_index(j)));
            file.write(' ');
        }
        file.write('\n');
    }
    playground->serialize(file);

    for (int i = 0; i < ships_manager->get_count_of_ships(); i++){
        file.write(coords_of_ships[i].x);
        file.write(' ');
        file.write(coords_of_ships[i].y);
        file.write('\n');
    }
    
    file.write(static_cast<int>(ability_manager->get_names_of_abilies().size()));
    file.write(' ');
    for (int i = 0; i < ability_manager->get_names_of_abilies().size(); i++){
        file.write(static_cast<int>(ability_manager->get_names_of_abilies()[i]));
        file.write(' ');
    }
    file.write('\n');
}

void Player::deserialize(FileWrapper& file) {
    int ships_count;
    file.read(ships_count);
    for (int i = 0; i < ships_count; i++){
        int l;
        file.read(l);
        length_of_ships.push_back(static_cast<Length_of_the_ship>(l));
    }
    ships_manager = new Manager_of_ships(ships_count, length_of_ships);

    for (int i = 0; i < ships_count; i++){
        int orientation;
        file.read(orientation);
        ships_manager->get_ship(i).set_orientation(static_cast<Orientation>(orientation));
        for (int j = 0; j < ships_manager->get_ship(i).get_length(); j++){
            int segment;
            file.read(segment);
            if (segment == 1){
                ships_manager->get_ship(i).shoot_to_segment(j);
            }
            else if (segment == 0){
                ships_manager->get_ship(i).shoot_to_segment(j);
                ships_manager->get_ship(i).shoot_to_segment(j);
            }
        }
    }
    int width, height;
    file.read(height);
    file.read(width);

    playground = new Playground(height, width, nullptr);
    playground->deserialize(file);

    for (int i = 0; i < ships_count; i++){
        int x, y;
        file.read(x);
        file.read(y);
        playground->add_ship(ships_manager->get_ship(i), {x, y});
        coords_of_ships.push_back({x, y});
    }

    ability_manager->clear_manager();
    int count_abilities;
    file.read(count_abilities);
    for (int i = 0; i < count_abilities; i++){
        int name;
        file.read(name);
        ability_manager->push_ability(static_cast<Name_of_builder>(name));
    }
}