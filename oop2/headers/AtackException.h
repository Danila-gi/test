#ifndef ATACK_ERROR_H
#define ATACK_ERROR_H

#include <iostream>

class AtackException : public std::runtime_error {
public:
    explicit AtackException(const std::string& message = "Incorrect coords for the atack!");
};

#endif