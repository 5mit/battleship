#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <string>

#include "player.h"


class ComputerPlayer : public Player {
private:
    // Count for the number of computer players (starts at 'A')
    static char cpuCount;
    // Generates the Computer Player's name
    std::string generateName();

public: 
    ComputerPlayer();
};

#endif