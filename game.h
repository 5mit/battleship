#ifndef GAME_H
#define GAME_H

#include <memory>
#include <cstddef>
#include <string>

#include "player.h"

// The Game class controls the flow of a game.
class Game {
private: 
    // a string of '-' to help format the game output by dividing it into sections
    static constexpr std::string_view divider = "---------------------"; 
    std::unique_ptr<Player> p[2];   // holds pointers to both player objects
    std::size_t turn;               // keeps track of the current turn number
    bool playersSelected;           // flag for if players have been selected or not

    // Checks both players boards to see if there is a winner
    bool isRunning() const;  
    
    // Conducts the next turn of the game
    void playTurn();   

public:

    // Initalizes the player objects based on user input
    void selectPlayers();

    // Returns the the player who is making a move,
    Player* nextPlayer() const { return p[turn % 2].get(); }

    // Returns the the player who is NOT making a move.
    Player* otherPlayer() const { return p[(turn + 1) % 2].get(); }

    // Conducts the main game loop
    void play();
    
    // Announces the end of the game and the name of the winner (or a tie).
    void announceWinner();
};

#endif