#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include "computerplayer.h"

class RandomPlayer : public ComputerPlayer {
    virtual Move getMove() override;
};

#endif