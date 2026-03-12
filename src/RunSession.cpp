#include "RunSession.h"
#include <iostream>
#include <cstdio>

// -------------------------------------------------------
// Satu iterasi: Roll -> Evaluate -> Score -> UpdateState
// Urutan ini adalah INVARIANT - tidak boleh berubah
// -------------------------------------------------------
void RunSession::playHand(
    std::vector<int>& dice,
    int& totalScore,
    int& commitLeft,
    int targetScore,
    int handPenalty,
    int diceCount
) {
    // Fase 1: Roll dadu
    dice = diceSystem.rollDice(diceCount);
    std::cout << "[RunSession] Fase 1: Roll dadu\n";

    // Fase 2: Evaluasi combo
    EvalResult eval = evaluator.evaluate(dice);
    std::cout << "[RunSession] Fase 2: Evaluasi combo\n";

    // Fase 3: Hitung score
    // Skeleton: score dummy (tanpa algoritma scoring).
    // Dibuat cukup untuk memastikan Round 1 bisa selesai.
    const int remainingToTarget = targetScore - totalScore;
    const int finalScore = (remainingToTarget + commitLeft - 1) / commitLeft; // ceil(remaining/commitLeft)
    std::printf("[RunSession] Fase 3: Score (dummy) = %d (remaining=%d, commitLeft=%d)\n",
        finalScore, remainingToTarget, commitLeft);

    // Fase 4: Update state
    totalScore += finalScore;
    commitLeft--;
    std::cout << "[RunSession] Fase 4: Total score = " << totalScore
              << " | Commit left = " << commitLeft << "\n";
}

// -------------------------------------------------------
// Satu ronde: loop playHand sampai target tercapai atau commit habis
// -------------------------------------------------------
void RunSession::playRound(int round, int& coins, bool& runLost) {
    const int targetScore = 300; // Skeleton: hanya Round 1
    int commitLeft  = 3;
    int rerollLeft  = 3;
    int handPenalty = 0;
    int diceCount   = 5;

    std::cout << "\n===== ROUND " << round << " =====\n";

    int totalScore = 0;
    std::vector<int> dice;

    // Core loop per ronde
    while (commitLeft > 0 && totalScore < targetScore) {
        playHand(dice, totalScore, commitLeft, targetScore, handPenalty, diceCount);
        // TODO: beri opsi pemain untuk reroll sebelum commit
    }

    // Fase 5: Cek hasil ronde
    if (totalScore < targetScore) {
        std::cout << "[RunSession] Target tidak tercapai. GAME OVER.\n";
        runLost = true;
        return;
    }

    std::cout << "[RunSession] Round " << round << " lolos!\n";

    // Fase 6: Shop (placeholder)
    int reward = 4 + commitLeft + rerollLeft;
    coins += reward;
    std::cout << "[RunSession] Reward coin: " << reward
              << " | Total coin: " << coins << "\n";
    shopSystem.openShop(scoringSystem, diceSystem, coins);
}

// -------------------------------------------------------
// Entry point - skeleton hanya Round 1, urutan fase tetap INVARIANT
// -------------------------------------------------------
void RunSession::start() {
    bool runLost = false;
    int coins = 0;

    std::cout << "===== RUN DIMULAI =====\n";

    playRound(1, coins, runLost);
    if (runLost) return;

    std::cout << "\n===== SELESAI (SKELETON ROUND 1) =====\n";
}
