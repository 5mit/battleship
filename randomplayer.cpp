#include <random>
#include <cstddef>

#include "randomplayer.h"
#include "board.h"

Move RandomPlayer::getMove() {

    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_int_distribution<std::size_t> randomIndex(0, BOARD_SIZE - 1); // Random number in range [0,99]

    std::size_t chosenMoveIndex = randomIndex(mt);

    Move move = Move();

    move.col = chosenMoveIndex % BOARD_LENGTH;
    move.row = static_cast<char>(chosenMoveIndex / BOARD_LENGTH) + 'A';

    return move;
}