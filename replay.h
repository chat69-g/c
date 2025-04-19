// ReplayRecorder.h
#pragma once
#include <fstream>
#include <string>

class ReplayRecorder {
public:
    ReplayRecorder();
    ~ReplayRecorder();
    void RecordAction(const std::string& action);
    
private:
    std::ofstream replayFile;
};