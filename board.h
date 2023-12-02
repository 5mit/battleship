#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstddef>
#include "move.h"

constexpr std::size_t BOARD_LENGTH = 10; 
constexpr std::size_t BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;

enum class EnemyPiece {HIT = 'X', MISS = 'O', EMPTY = '_'};
enum class PlayerPiece {AIRCRAFT = 'A', BATTLESHIP = 'B', CRUISER = 'C', SUBMARINE = 'S', PATROL = 'P', EMPTY = '_'};

class Board {
private:
    
    PlayerPiece playerBoard[BOARD_SIZE];
    EnemyPiece enemyBoard[BOARD_SIZE];
    // If second parameter is true, it is the players move, if false, it is the enemy's
public:

    Board();      // Initalizes boards by calling reset()
    void reset(); // Sets all pieces on both boards to "EMPTY", then randomly places the 5 player ships
    
    // a helper function for isRunning in the Game class
    // returns true if the playerBoard has no more pieces left, otherwise it returns false
    bool isEmpty() const;

    // Executes the move indicated by the first function parameter
    // The second parameter takes in the enemy player's Board object so we can check where their pieces are.
    // If the third parameter is true, it is the players move, if false, it is the enemy's
    void makeMove(Move, Board&, bool); 

    // A helper function for makeMove
    bool moveHits(Move);

    // Retuns false if out of bounds of the board, or if the Move has already been done by checking the enemy's board.
    bool isLegal(Move) const;   

    // Displays both the boards to the specified stream
    friend std::ostream &operator<<( std::ostream &, const Board&);

};

#endif