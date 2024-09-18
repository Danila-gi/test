#pragma once
enum Location{
    Horizontal,
    Vertical
};

enum Length_of_the_ship{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4
};

enum Statment_of_the_ship{
    INTACT = 2,
    DAMAGED = 1,
    DESTROYED = 0
};

enum Statment_of_the_coord{
    UNKNOWN = 2,
    EMPTY = 1,
    SHIP = 0
};

typedef struct Coords{
    int x;
    int y;
}Coords;