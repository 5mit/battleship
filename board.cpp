#include <cstddef>
#include <random>
#include <iostream>

#include "board.h"

// Initalizes boards by calling reset()
Board::Board() {reset();}


void Board::reset() {
    // Set all pieces on both boards to "EMPTY",
    for(std::size_t i = 0; i < BOARD_SIZE; ++i){
        playerBoard[i] = PlayerPiece::EMPTY;
        enemyBoard[i] = EnemyPiece::EMPTY;
    }

    // Create a device to generate random numbers
    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<std::size_t> randomPosition(0, BOARD_LENGTH - 1);

    // Place each piece randomly on the board
    for (std::size_t i = 0 ; i < NUM_PIECES; ++i) {
        bool validPlacement; // Flag that states if generated ship placement is valid
        bool vertical;       // Flag that states whether ship is oriented vertically or not
        std::size_t startIndex; // Start Index of ship placement
        std::size_t verticalMultipler, horizontalMultipler; // multipliers that account for placement being horizontal or vertical
        
        // Keep generating random placements for this ship until a valid one is found
        do {
            validPlacement = true; 
            vertical = randomPosition(mt) % 2 == 0? true: false; // randomly decide if ship is vertical or horizontal
            // Adjust multipliers accordingly
            verticalMultipler = vertical == true? BOARD_LENGTH: 1; 
            horizontalMultipler = vertical == false? BOARD_LENGTH: 1;
            // Get a random start index within valid range
            startIndex = verticalMultipler * (randomPosition(mt) % (BOARD_LENGTH - indexToLength[i]) + 1);
            startIndex +=  horizontalMultipler * randomPosition(mt);
            // See if that results in a valid placement
            for (std::size_t j = 0; j < indexToLength[i] && validPlacement; ++j) {
                if (playerBoard[startIndex + (j * verticalMultipler)] != PlayerPiece::EMPTY) {
                    validPlacement = false;
                }
            }
        } while(!validPlacement);
        
        // Random placement has been chosen and valid so we can go ahead and place it on the board
        for (std::size_t j = 0; j < indexToLength[i] || !validPlacement; ++j, ++curNumberShipPieces) { // Also increment the number of ship pieces on board
            playerBoard[startIndex + (j * verticalMultipler)] = indexToPiece[i];
        }


    } 
}

// Returns true if every place on board is empty. 
bool Board::isEmpty() const {

    return curNumberShipPieces == 0;

}


// Assumes a move is legal!
void Board::makeMove(Move m, Board& enemy, bool playerMove) {
    std::size_t idx = m.getIndex();

    if (playerMove) {
        if (enemy.moveHits(m)) {
            enemyBoard[idx] = EnemyPiece::HIT;
        }
        else {
            enemyBoard[idx] = EnemyPiece::MISS;
        }
    }
    else {
        if (moveHits(m)) {
            playerBoard[idx] = PlayerPiece::EMPTY;
            --curNumberShipPieces;
        }
    }

}

// Assumes a move is legal!
bool Board::moveHits(Move m) {
    return playerBoard[m.getIndex()] != PlayerPiece::EMPTY;
}

// returns true if move is within bounds of board and not already attempted.
bool Board::isLegal(Move m) const {
    return m.isPossible() && enemyBoard[m.getIndex()] == EnemyPiece::EMPTY;
} 

// Prints both boards to screen
std::ostream& operator<<( std::ostream& os , const Board& b) {

    os << "Enemy Board:\n";
    os << "  0 1 2 3 4 5 6 7 8 9 \n";
    for (std::size_t i = 0; i < BOARD_LENGTH; ++i) {
        os << static_cast<char>('A' + i) << " ";
        for (std::size_t j = 0; j < BOARD_LENGTH; ++j){
            os << static_cast<char>(b.enemyBoard[i * BOARD_LENGTH + j]) << ' ';
        }
    os << "\n";
    } 

    os << '\n';
    os << "Player Board:\n";
    os << "  0 1 2 3 4 5 6 7 8 9 \n";
    for (std::size_t i = 0; i < BOARD_LENGTH; ++i) {
        os << static_cast<char>('A' + i) << " ";
        for (std::size_t j = 0; j < BOARD_LENGTH; ++j){
            os << static_cast<char>(b.playerBoard[i * BOARD_LENGTH + j]) << ' ';
        }
    os << "\n";
    }

    
    return os;
}