#include "../headers/ShipPlacmentException.h"

ShipPlacmentException::ShipPlacmentException(const std::string& message): std::runtime_error(message) {}