#ifndef GAME_H
#define GAME_H

#include <memory>

#include "player.h"

class Game {
private: 
    std::unique_ptr<Player> p[2];
    static unsigned int turn;

public:
    void selectPlayers();
    Player* nextPlayer() const;
    bool isRunning() const;
    void play();
    void announceWinner();
};

#endif