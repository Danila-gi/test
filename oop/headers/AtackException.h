#ifndef ATACK_ERROR_H
#define ATACK_ERROR_H

#include <iostream>
#include <sstream>

class AtackException : public std::runtime_error {
public:
    explicit AtackException(int x, int y);

private:
    std::string constructMessage(int x, int y) const;
};

#endif