// ScoreManager.cpp
#include "ScoreManager.h"
#include <fstream>
#include <iostream>

void ScoreManager::AddScore(const std::string& name, int score) {
    LoadScores();
    scores.push_back({name, score});
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });
    SaveScores();
}

std::vector<ScoreEntry> ScoreManager::GetTopScores(int count) {
    LoadScores();
    if (scores.size() > count) {
        return std::vector<ScoreEntry>(scores.begin(), scores.begin() + count);
    }
    return scores;
}

void ScoreManager::LoadScores() {
    scores.clear();
    std::ifstream file("scores.dat");
    if (file) {
        ScoreEntry entry;
        while (file >> entry.playerName >> entry.score) {
            scores.push_back(entry);
        }
    }
}

void ScoreManager::SaveScores() {
    std::ofstream file("scores.dat");
    for (const auto& entry : scores) {
        file << entry.playerName << " " << entry.score << "\n";
    }
}