#include "../headers/Scanner_builder.h"

Scanner_builder::Scanner_builder(Command_coords* p_command):command(p_command){}

std::shared_ptr<Interface_of_abilities> Scanner_builder::make_ability(){
    auto p_builder = std::make_shared<Scanner>(command->get_coords());
    return p_builder;
}

bool Scanner_builder::is_need_arguments(){return true;}

Name_of_builder Scanner_builder::get_name(){return SCANNER;};
