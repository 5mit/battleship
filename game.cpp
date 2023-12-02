#include <iostream>
#include <string>

#include "game.h"
#include "humanplayer.h"
#include "randomplayer.h"
#include "player.h"
#include "board.h"



void Game::selectPlayers() {
    
    // for each player (there are 2 players in battleship)
    for (int i = 0; i < 2; ++i) {
        
        // Get the type of player from the user
        char playerType = '\0';
        std::string tmp;
        do {
            std::cout << "Is Player " << i + 1 << " a human or computer? (h or c): ";
            if (std::getline(std::cin, tmp, '\n') && tmp.length() > 0) {
                playerType = static_cast<char>(tolower(tmp[0]));  // Just grab the first character from the input and make it case insensitive
            }
        } while (playerType != 'c' && playerType != 'h'); // Keep taking input until the first character is a "c" or an "h" 
        
        // If the user chose a human player, get a name for that player and create a HumanPlayer for it
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
    // Ipdate the playerSelected flag
    playersSelected = true;

}

// returns the index of to the next player and increases the turn counter in the process
std::size_t Game::nextPlayer() const {
    return turn % 2;
}

// This function checks both player's boards to see if they have any remaining battleships
bool Game::isRunning() const {
    // For each player
    for (std::size_t curPlayer = 0; curPlayer < 2; ++curPlayer) {
        // Check to see if their board is empty (i.e all their ships are destroyed)
        if (p[curPlayer]->getBoard().isEmpty()) {
                return false;
        }
    }
    return true;  
}

void Game::announceWinner() {
    
    std::cout << "\nGAME OVER\n\n";

    // the player who's turn is next was going to win before the last turn was played
    // (i.e we already know the other player's board is empty)
    // Thus, if this player's board is empty, it is a tie.
    if (p[nextPlayer()]->getBoard().isEmpty()) {
        std::cout << "It's a tie!\n";
    }
    // otherwise, this player wins as they still have atleast one battleship remaining
    else {
        std::cout << p[nextPlayer()]->getName() << "WINS!\n";
    }

}

void Game::playTurn() {
       
        std::size_t curPlayer = nextPlayer();
        Board &curPlayerBoard = p[curPlayer]->getBoard();
        Board &otherPlayerBoard = p[(curPlayer + 1) % 2]->getBoard();

        std::cout << "\nTurn " << turn << " (" << p[curPlayer]->getName() << "):\n" << divider << "\n";
        std::cout << p[curPlayer]->getName() <<", it's your turn:" << '\n';
        std::cout << curPlayerBoard;
        
        Move m;
        do {
        m = p[curPlayer]->getMove();
        } while (!curPlayerBoard.isLegal(m));

        curPlayerBoard.makeMove(m, otherPlayerBoard, true);
        otherPlayerBoard.makeMove(m, curPlayerBoard, false);

        std::cout << '\n' << divider << '\n' << p[curPlayer]->getName() << " shot at " << m.row << m.col << "!\n\n" << curPlayerBoard << '\n';

        ++turn; // Increment the turn counter in preperation for the next turn
}

void Game::play() {
    if (!playersSelected) {
        std::cerr << "Error: Cannot play - No players selected\n";
        return;
    }


    
    while(isRunning()) {
        // Run the next turn
        playTurn();
        // Have the user press enter in order to start the next turn
        std::cout << "Press enter to start the next turn.\n";
        std::string tmp;
        std::getline(std::cin, tmp, '\n');
    } 

    // Run one last turn
    // this can provide the losing player an opportunity to tie
    playTurn();

    announceWinner();
}