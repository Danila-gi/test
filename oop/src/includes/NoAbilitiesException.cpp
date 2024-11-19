#include "../headers/NoAbilitiesException.h"

NoAbilitiesException::NoAbilitiesException(const std::string& message): std::runtime_error(message) {}