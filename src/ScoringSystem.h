#pragma once
#include <vector>
#include <string>
#include "DiceEvaluator.h"

// Mengelola perhitungan score
class ScoringSystem {
public:
    int calculateScore(int baseScore);
    int calculateScore(int baseScore, const std::vector<std::string>& comboNames);
};
