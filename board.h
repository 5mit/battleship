#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstddef>
#include "move.h"

constexpr std::size_t BOARD_LENGTH = 10; 
constexpr std::size_t BOARD_SIZE = BOARD_LENGTH * BOARD_LENGTH;
constexpr std::size_t NUM_PIECES = 5; // Number of different types of pieces

// These enums are assigned to the chars they will be printed as when the game outputs the board
enum class EnemyPiece {HIT = 'X', MISS = 'O', EMPTY = '_'};
enum class PlayerPiece {AIRCRAFT = 'A', BATTLESHIP = 'B', CRUISER = 'C', SUBMARINE = 'S', PATROL = 'P', EMPTY = '_'};

// For reference:
// Index: 0 = Aircraft, 1 = BATTLESHIP, 2 = CRUISER, 3 = SUBMARINE, 4 = PATROL

// Array to get the size of a ship given its index:
constexpr std::size_t indexToLength[] = {5, 4, 3, 3, 2};

// Array to get the enum value of the piece (it's corresponding char), given its index
const PlayerPiece indexToPiece[] = {PlayerPiece::AIRCRAFT, PlayerPiece::BATTLESHIP, PlayerPiece::CRUISER, PlayerPiece::SUBMARINE, PlayerPiece::PATROL};

class Board {
private:
    
    std::size_t curNumberShipPieces; // Holds a counter of how many ship pieces remain on the board

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

    // A helper function for makeMove that returns true if a move hits one of the player's pieces on the playerBoard
    bool moveHits(Move);

    // Retuns false if out of bounds of the board, or if the Move has already been done by checking the enemy's board.
    bool isLegal(Move) const;   

    // Displays both the boards to the specified stream
    friend std::ostream &operator<<(std::ostream &, const Board&);

};

#endif