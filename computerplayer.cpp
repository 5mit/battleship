#include <string>
#include "computerplayer.h"

char ComputerPlayer::cpuCount = 'A';

std::string ComputerPlayer::generateName() {
    std::string n = "Computer ";
    n += cpuCount++;
    return n;
}

ComputerPlayer::ComputerPlayer() : Player(generateName()) {}