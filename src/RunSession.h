#pragma once
#include <vector>
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "DiceSystem.h"
#include "DiceEvaluator.h"

// Controller utama yang mengatur urutan fase setiap ronde (skeleton)
class RunSession {
private:
    ScoringSystem scoringSystem;
    ShopSystem    shopSystem;
    DiceSystem    diceSystem;
    DiceEvaluator evaluator;

    void playHand(std::vector<int>& dice, int& totalScore, int& commitLeft, int& rerollLeft, int targetScore, int handPenalty, int diceCount);
    void playRound(int round, int& coins, bool& runLost);

public:
    void start();
};
