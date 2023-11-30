#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <string>

#include "player.h"
#include "move.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& n);    

    virtual Move getMove() override;

};

#endif