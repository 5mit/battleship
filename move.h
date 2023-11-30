#ifndef MOVE_H
#define MOVE_H

#include <cstddef>

struct Move {
    std::size_t col;   // column number (0-9)
    char row;          // row letter (A-J) *uppercase*

    // returns index that row and col correspond to in the 1-D board array 
    std::size_t getIndex() const {return static_cast<std::size_t>(row - 'A') * 10 + col;}
};
#endif