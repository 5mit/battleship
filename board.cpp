#include <cstddef>
#include "board.h"

Board::Board() {reset();}

void Board::reset() {
    for(std::size_t i = 0; i < BOARD_SIZE; ++i){
        playerBoard[i] = PlayerPiece::EMPTY;
        enemyBoard[i] = EnemyPiece::EMPTY;
    }

    // Temp code:
    // make ships in arbitrary fixed position:
    // Implement a randomizer later
    for(int i = 0; i < 5; i++) {
        playerBoard[4 + i * 10] = PlayerPiece::AIRCRAFT;

        if (i < 4) {
            playerBoard[36 + i] = PlayerPiece::BATTLESHIP;
        }

        if (i < 3) {
            playerBoard[52 + i * 10] = PlayerPiece::CRUISER;
            playerBoard[46 + i] = PlayerPiece::SUBMARINE;
        }
        if (i < 2) {
            playerBoard[90 + i] = PlayerPiece::PATROL;
        }
    }
    

}

// INCOMPLETE
// Will update this function to take another board object that belongs to the other player
void Board::makeMove(Move m, bool playerMove) {
    std::size_t idx = m.getIndex();
    if (!playerMove) {
        if (playerBoard[idx] != PlayerPiece::EMPTY) {
            enemyBoard[idx] = EnemyPiece::HIT;
        }
        else {
            enemyBoard[idx] = EnemyPiece::MISS;
        }
    }
}

bool Board::isLegal(Move m) const {
    std::size_t idx = m.getIndex();
    return idx < 100 && enemyBoard[idx] == EnemyPiece::EMPTY;
} 


// I will try to make this code more modular in order to reduce repetition
std::ostream& operator<<( std::ostream& os , const Board& b) {
    os << "Enemy Board:\n";
    os << "  0 1 2 3 4 5 6 7 8 9 \n";
    for (std::size_t i = 0; i < BOARD_LENGTH; ++i) {
        os << static_cast<char>('A' + i) << " ";
        for (std::size_t j = 0; j < BOARD_LENGTH; ++j){
            switch(b.enemyBoard[i * BOARD_LENGTH + j]) {
                case EnemyPiece::HIT:
                    os << 'X';
                    break;
                case EnemyPiece::MISS:
                    os << 'O';
                    break;
                default: // i.e case EnemyPiece::EMPTY:
                    os << '_';
            }
            os << ' ';
        }
    os << "\n";
    } 

    os << '\n';

    os << "Player Board:\n";
    os << "  0 1 2 3 4 5 6 7 8 9 \n";
    for (std::size_t i = 0; i < BOARD_LENGTH; ++i) {
        os << static_cast<char>('A' + i) << " ";
        for (std::size_t j = 0; j < BOARD_LENGTH; ++j){
            switch(b.playerBoard[i * BOARD_LENGTH + j]) {
                case PlayerPiece::EMPTY:
                    os << '_';
                    break;
                default: // part of a ship:
                    os << 'B';
            }
            os << ' ';
        }
    os << "\n";
    }

    
    return os;
}

