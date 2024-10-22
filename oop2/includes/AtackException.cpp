#include "../headers/AtackException.h"

AtackException::AtackException(int x, int y)
    : std::runtime_error(constructMessage(x, y)) {}

std::string AtackException::constructMessage(int x, int y) const {
    std::ostringstream oss;
    oss << "Incorrect coords for the attack! Coordinates: (" << x << ", " << y << ")";
    return oss.str();
}