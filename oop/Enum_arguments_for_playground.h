#ifndef ENUM_PLAYGROUND_H
#define ENUM_PLAYGROUND_H

enum Statement_of_the_coord{
    UNKNOWN = 2,
    EMPTY = 1,
    SHIP = 0
};

typedef struct Coords{
    int x;
    int y;
}Coords;

#endif