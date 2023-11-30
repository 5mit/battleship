#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <string>

#include "player.h"


class ComputerPlayer : public Player {
private:
    static char cpuCount;
    std::string generateName();

public: 
    ComputerPlayer();
};

#endif