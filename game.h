#ifndef GAME_H
#define GAME_H

#include <memory>
#include <cstddef>
#include <string>

#include "player.h"

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

    // Returns the player who's turn is next
    // The project spec says to return a pointer to the object,
    // but it would be easier to just return an index to the "p" array
    std::size_t nextPlayer() const;
    
    // Conducts the main game loop
    void play();
    
    // Announces the end of the game and the name of the winner (or a tie).
    void announceWinner();
};

#endif