#ifndef LACK_OF_ABILITY_H
#define LACK_OF_ABILITY_H

#include <iostream>

class NoAbilitiesException : public std::runtime_error {
public:
    explicit NoAbilitiesException(const std::string& message = "You haven't got any abilities!");
};

#endif