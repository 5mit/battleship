#include <string>
#include <iostream>

#include "humanplayer.h"
#include "player.h"
#include "move.h"

HumanPlayer::HumanPlayer(const std::string& n) : Player(n) {}

Move HumanPlayer::getMove() {
    std::cout << name << " - Enter your move: ";
    
    // Add imput validation
    Move m = Move();
    std::cin >> m.row;
    std::cin >> m.col;

    std::cout << "your move: " << m.row << m.col << '\n';

    return m;

}