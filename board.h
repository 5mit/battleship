#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstddef>
#include "move.h"

constexpr std::size_t BOARD_LENGTH = 10; 
constexpr std::size_t BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

enum class EnemyPiece {HIT, MISS, EMPTY};
enum class PlayerPiece {AIRCRAFT, BATTLESHIP, CRUISER, SUBMARINE, PATROL, EMPTY};

class Board {
private:
    
    PlayerPiece playerBoard[BOARD_SIZE];
    EnemyPiece enemyBoard[BOARD_SIZE];
    
public:



    Board();      // Initalizes boards by calling reset()
    void reset(); // Sets all pieces on both boards to "EMPTY", then randomly places the 5 player ships
    
    // Executes the move indicated by the first function parameter
    void makeMove(Move, bool); // If second parameter is true, it is the players move, if false, it is the enemy's

    // Retuns false if out of bounds of the board, or if the Move has already been done by checking the enemy's board.
    bool isLegal(Move) const;   

    // Displays both the boards to the specified stream
    friend std::ostream &operator<<( std::ostream &, const Board&);

};

#endif