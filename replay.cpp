// ReplayRecorder.cpp
#include "ReplayRecorder.h"

ReplayRecorder::ReplayRecorder() {
    replayFile.open("replay.txt");
}

ReplayRecorder::~ReplayRecorder() {
    replayFile.close();
}

void ReplayRecorder::RecordAction(const std::string& action) {
    static Uint32 startTime = SDL_GetTicks();
    Uint32 timestamp = SDL_GetTicks() - startTime;
    replayFile << timestamp << ":" << action << "\n";
}