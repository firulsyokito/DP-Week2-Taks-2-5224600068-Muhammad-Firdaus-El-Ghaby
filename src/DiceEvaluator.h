#pragma once
#include <vector>
#include <string>

struct EvalResult {
    int baseScore;
    double totalMultiplier;
    std::vector<std::string> comboNames;
};

// Mengevaluasi kombinasi dadu dan menentukan combo yang aktif
class DiceEvaluator {
public:
    EvalResult evaluate(const std::vector<int>& dice);
};
