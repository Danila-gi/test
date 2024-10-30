#ifndef INCERRECT_SHIP_COORDS_H
#define INCERRECT_SHIP_COORDS_H

#include <iostream>
#include <sstream>

class ShipPlacmentException : public std::runtime_error {
public:
    explicit ShipPlacmentException(int x, int y);

private:
    std::string constructMessage(int x, int y) const;
};

#endif