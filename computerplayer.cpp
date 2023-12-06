#include <string>
#include "computerplayer.h"

// Start the cpuCount at 'A'
char ComputerPlayer::cpuCount = 'A';

// Generates a name for the cpu and increments the cpu count
std::string ComputerPlayer::generateName() {
    std::string n = "Computer ";
    n += cpuCount++;
    return n;
}

ComputerPlayer::ComputerPlayer() : Player(generateName()) {}