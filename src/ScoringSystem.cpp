#include "ScoringSystem.h"
#include <iostream>

int ScoringSystem::calculateScore(int baseScore) {
    std::cout << "[ScoringSystem] calculateScore base=" << baseScore << "\n";
    return baseScore;
}

int ScoringSystem::calculateScore(int baseScore, const std::vector<std::string>& comboNames) {
    return calculateScore(baseScore);
}
