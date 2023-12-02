#include <cstddef>
#include <random>
#include <iostream>

#include "board.h"

Board::Board() {reset();}

void Board::reset() {
    for(std::size_t i = 0; i < BOARD_SIZE; ++i){
        playerBoard[i] = PlayerPiece::EMPTY;
        enemyBoard[i] = EnemyPiece::EMPTY;
    }

    const std::size_t indexToLength[] = {5, 4, 3, 3, 2};
    const PlayerPiece indexToPiece[] = {PlayerPiece::AIRCRAFT, PlayerPiece::BATTLESHIP, PlayerPiece::CRUISER, PlayerPiece::SUBMARINE, PlayerPiece::PATROL};

    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<std::size_t> randomPosition(0, BOARD_LENGTH - 1);


    for (std::size_t i = 0 ; i < 5; ++i) {
        bool validPlacement;
        bool vertical;
        std::size_t startIndex;
        std::size_t verticalMultipler, horizontalMultipler;
        
        
        do {
            validPlacement = true;
            vertical = randomPosition(mt) % 2 == 0? true: false;
            verticalMultipler = vertical == true? BOARD_LENGTH: 1;
            horizontalMultipler = vertical == false? BOARD_LENGTH: 1;
            startIndex = verticalMultipler * (randomPosition(mt) % (BOARD_LENGTH - indexToLength[i]) + 1);
            startIndex +=  horizontalMultipler * randomPosition(mt);
            for (std::size_t j = 0; j < indexToLength[i] && validPlacement; j++) {
                if (playerBoard[startIndex + (j * verticalMultipler)] != PlayerPiece::EMPTY) {
                    validPlacement = false;
                }
            }
        } while(!validPlacement);
        
        // Random placement has been chosen and valid so we can go ahead and place it on the board
        for (std::size_t j = 0; j < indexToLength[i] || !validPlacement; j++) {
            playerBoard[startIndex + (j * verticalMultipler)] = indexToPiece[i];
        }


    } 
}


bool Board::isEmpty() const {
    for (PlayerPiece piece : playerBoard) {
        if (piece != PlayerPiece::EMPTY) {
            return false;
        }
    }
    return true;
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
        }
    }

}

// Assumes a move is legal!
bool Board::moveHits(Move m) {
    return playerBoard[m.getIndex()] != PlayerPiece::EMPTY;
}


bool Board::isLegal(Move m) const {
    return m.isPossible() && enemyBoard[m.getIndex()] == EnemyPiece::EMPTY;
} 


// I will try to make this code more modular in order to reduce repetition
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

/*             switch(b.playerBoard[i * BOARD_LENGTH + j]) {
                case PlayerPiece::EMPTY:
                    os << static_cast<char>(b.playerBoard[i * BOARD_LENGTH + j]);
                    break;
                default: // part of a ship:
                    os << 'B';
            } */
            //os << ' ';

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