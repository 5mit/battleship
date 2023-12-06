#include <string>
#include <iostream>
#include <limits>

#include "humanplayer.h"
#include "player.h"
#include "move.h"

HumanPlayer::HumanPlayer(const std::string& n) : Player(n) {}

Move HumanPlayer::getMove() {
    
    Move move = Move();

    // Keeps asking got user input until a syntactially valid move is given
    do {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << name << " - Enter your move: ";
        std::cin >> move.row;
        std::cin >> move.col;
        move.row = static_cast<char>(std::toupper(move.row)); // make row letter case insenstive 
    } while (std::cin.fail());

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return move;

}