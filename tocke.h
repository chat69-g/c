// ScoreManager.h
#pragma once
#include <vector>
#include <string>
#include <algorithm>

struct ScoreEntry {
    std::string playerName;
    int score;
};

class ScoreManager {
public:
    void AddScore(const std::string& name, int score);
    std::vector<ScoreEntry> GetTopScores(int count = 5);

private:
    std::vector<ScoreEntry> scores;
    void LoadScores();
    void SaveScores();
};