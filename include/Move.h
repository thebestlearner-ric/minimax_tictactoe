#pragma once

#include <sys/types.h>
struct Move{
    Move(){};
    Move(int Score): score(Score){};
    int location;
    char piece;
    int score;
};