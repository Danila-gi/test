#include "../headers/ShipPlacmentException.h"

ShipPlacmentException::ShipPlacmentException(int x, int y)
    : std::runtime_error(constructMessage(x, y)) {}

std::string ShipPlacmentException::constructMessage(int x, int y) const {
    std::ostringstream oss;
    oss << "Incorrect coords for the ship! Coordinates of incorrect segment: (" << x << ", " << y << ")";
    return oss.str();
}
