#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "board.h"
#include "move.h"

// All of the player functions were simple so I decided to inline them all.
// Therefore, there is no player.cpp 

class Player{
protected:
    std::string name;
    Board board;

public:
    // Argumented constructor that takes in the Players name
    Player(const std::string& n) : name(n) {}

    // Returns the name of the player
    const std::string& getName() const {return name;}

    // Pure virtual function for getting the player's move
    virtual Move getMove() = 0;

    // Returns a nonconst reference to the player's board object
    Board& getBoard() {return board;}

    // Virtual desctructor (inline)
    virtual ~Player() {}
};

#endif