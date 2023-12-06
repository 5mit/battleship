#ifndef MOVE_H
#define MOVE_H

#include <cstddef>

// All of the member functions of Move are suitable for inlining so there is Move.cpp

struct Move {
    std::size_t col;   // column number (0-9)
    char row;          // row letter (A-J) *uppercase*

    // returns index that row and col correspond to in the 1-D board array 
    std::size_t getIndex() const {return static_cast<std::size_t>(row - 'A') * 10 + col;}

    // Helper function for input validation 
    // Ensures the move is within the valid range
    bool isPossible() {return col <= 9 && row >= 'A' && row <= 'J';}
};
#endif