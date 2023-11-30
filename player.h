#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "board.h"
#include "move.h"

class Player{
protected:
    std::string name;
    Board board;

public:
    Player(const std::string&);

    const std::string& getName() const {return name;}

    virtual Move getMove() = 0;

    Board &getBoard() {return board;}

    virtual ~Player();
};

#endif