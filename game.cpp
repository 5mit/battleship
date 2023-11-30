#include <iostream>
#include <string>
#include <limits>

#include "game.h"
#include "humanplayer.h"
#include "randomplayer.h"
#include "player.h"

unsigned int Game::turn = 0;

void Game::selectPlayers() {
    
    // for each player
    for (int i = 0; i < 2; ++i) {
        
        // Get the type of player from the user
        char playerType = '\0';
        std::string tmp;
        do {
            std::cout << "Is Player " << i + 1 << " a human or computer? (h or c): ";
            if (std::getline(std::cin, tmp, '\n') && tmp.length() > 0) {
                playerType = static_cast<char>(tolower(tmp[0]));
            }
        } while (playerType != 'c' && playerType != 'h');
        
        // if the user chose a human player, get a name for that player and create a HumanPlayer for it
        if (playerType == 'h') {
            std::cout << "Enter the player's name: ";
            std::string name;
            std::getline(std::cin, name, '\n');
            p[i] = std::make_unique<HumanPlayer>(name);
        }
        // Otherwise, they chose a computer player so just make a new RandomPlayer
        else {
            p[i] = std::make_unique<RandomPlayer>();
        }
    }
}

Player* Game::nextPlayer() const {
    return p[turn++ % 2];
}

bool isRunning() const {
    
    /*
    // For each board
    for (int i = 0; i < 2; ++i) {
        Board b = p[i]->getBoard();
    }
    */
    // DUMMY return
    return true;
}

void Game::play() {
    while(isRunning()) {

    }
}