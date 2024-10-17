#ifndef INCERRECT_SHIP_COORDS_H
#define INCERRECT_SHIP_COORDS_H

#include <iostream>

class ShipPlacmentException : public std::runtime_error {
public:
    explicit ShipPlacmentException(const std::string& message = "Incorrect coords for the ship!");
};

#endif