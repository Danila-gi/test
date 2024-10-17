#include "../headers/AtackException.h"

AtackException::AtackException(const std::string& message): std::runtime_error(message) {}