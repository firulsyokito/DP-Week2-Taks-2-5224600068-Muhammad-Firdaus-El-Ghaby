#include "RunSession.h"
#include <iostream>
#include <sstream>
#include <string>

namespace {
void line(const std::string& s = "") {
    std::cout << s << "\n";
}

void stepHeader(const std::string& step, const std::string& invariant, const std::string& title) {
    line("[" + step + " | " + invariant + "] " + title);
}

void resolverHeader(const std::string& name) {
    line("[Resolver] " + name + ":");
}

void todo(const std::string& s) {
    line("  >> TODO: " + s);
}

void info(const std::string& s) {
    line("  >> " + s);
}

void sub(const std::string& tag, const std::string& s) {
    line("  [" + tag + "] " + s);
}

std::string formatDice(const std::vector<int>& dice) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < dice.size(); i++) {
        if (i) oss << ", ";
        oss << dice[i];
    }
    oss << "]";
    return oss.str();
}

} // namespace

// -------------------------------------------------------
// Satu iterasi hand mengikuti template (INVARIANT):
// STEP B (ChooseAction) -> STEP C (PlayerAction) -> STEP D (ResolveSystem) -> STEP E (UpdateState) -> STEP A (Draw)
// -------------------------------------------------------
void RunSession::playHand(
    std::vector<int>& dice,
    int& totalScore,
    int& commitLeft,
    int& rerollLeft,
    int targetScore,
    int handPenalty,
    int diceCount
) {
    // STEP B - ChooseAction (player memilih apa yang akan dilakukan)
    line();
    stepHeader("STEP B", "INVARIANT", "ChooseAction");
    resolverHeader("PlayerDecision");
    info("Dice di tangan: " + formatDice(dice));
    todo("player memilih: reroll sebagian/semua dadu, atau langsung commit.");
    todo("player reroll dadu hingga mendapatkan kombinasi angka terbaik.");
    info("Sistem reroll tersedia: max rerollLeft=" + std::to_string(rerollLeft)
        + " (tidak disimulasikan agar output ringkas).");
    info("Simulasi: pilih aksi Commit.");

    // STEP C - PlayerAction (posisi step ini dalam loop adalah invariant)
    line();
    stepHeader("STEP C", "INVARIANT posisi", "PlayerAction");
    resolverHeader("PlayerAction");
    info("Commit dengan dice: " + formatDice(dice));

    // STEP D - ResolveSystem
    line();
    stepHeader("STEP D", "INVARIANT", "ResolveSystem");
    resolverHeader("ResolveHand");

    sub("D1", "Evaluate combo");
    info("DiceEvaluator::evaluate(diceCount=" + std::to_string(dice.size()) + ")");
    EvalResult eval = evaluator.evaluate(dice);
    (void)eval;

    sub("D2", "Calculate score");
    info("ScoreRule: dummy-ceil-to-target (MUTABLE)");
    const int remainingToTarget = targetScore - totalScore;
    const int finalScore = (remainingToTarget + commitLeft - 1) / commitLeft; // ceil(remaining/commitLeft)
    info("Skor turn ini: " + std::to_string(finalScore)
        + " (remaining=" + std::to_string(remainingToTarget)
        + ", commitLeft=" + std::to_string(commitLeft) + ")");

    // STEP E - UpdateState
    line();
    stepHeader("STEP E", "INVARIANT", "UpdateState");
    totalScore += finalScore;
    commitLeft--;
    info("Score turn ini: " + std::to_string(finalScore));
    info("Total score  : " + std::to_string(totalScore));
    info("Commit sisa  : " + std::to_string(commitLeft));

    // STEP A - Draw (siapkan dice untuk turn berikutnya)
    line();
    stepHeader("STEP A", "INVARIANT", "Draw");
    line("[DiceSystem] Draw dadu sampai tangan berisi " + std::to_string(diceCount) + " dadu.");
    todo("sort dadu descending by value.");
    const bool shouldRepeat = (commitLeft > 0 && totalScore < targetScore);
    if (!shouldRepeat) {
        return;
    }

    dice = diceSystem.rollDice(diceCount);
    info("Dice baru: " + formatDice(dice));
}

// -------------------------------------------------------
// Satu ronde: loop playHand sampai target tercapai atau commit habis
// -------------------------------------------------------
void RunSession::playRound(int round, int& coins, bool& runLost) {
    const int targetScore = 300; // Skeleton: hanya Round 1
    int commitLeft  = 1;
    int rerollLeft  = 3;
    int handPenalty = 0;
    int diceCount   = 5;

    std::cout << "\n===== ROUND " << round << " =====\n";
    info("Config (MUTABLE): targetScore=" + std::to_string(targetScore)
        + ", commitLeft=" + std::to_string(commitLeft)
        + ", rerollLeft=" + std::to_string(rerollLeft)
        + ", handPenalty=" + std::to_string(handPenalty)
        + ", diceCount=" + std::to_string(diceCount));

    int totalScore = 0;
    std::vector<int> dice;
    int handIndex = 1;

    // Setup awal: Draw dice untuk hand pertama (sebelum STEP C pertama)
    line();
    stepHeader("STEP A", "INVARIANT", "Draw (setup)");
    line("[DiceSystem] Draw dadu sampai tangan berisi " + std::to_string(diceCount) + " dadu.");
    todo("sort dadu descending by value.");
    dice = diceSystem.rollDice(diceCount);
    info("Dice awal: " + formatDice(dice));

    // Core loop per ronde
    while (commitLeft > 0 && totalScore < targetScore) {
        line();
        line("----- TURN/HAND " + std::to_string(handIndex) + " -----");
        playHand(dice, totalScore, commitLeft, rerollLeft, targetScore, handPenalty, diceCount);
        handIndex++;
        // TODO: beri opsi pemain untuk reroll sebelum commit
    }

    if (totalScore < targetScore) {
        line();
        line("[INVARIANT] PHASE 3 - PlayerTurnLoop selesai");

        line();
        line("[INVARIANT] PHASE 4 - EvaluateResult");
        info("Score akhir: " + std::to_string(totalScore));
        info("Target    : " + std::to_string(targetScore));
        line("[LOSE] Skor tidak mencapai target.");

        line();
        line("[RESULT] GAME OVER - Gagal mencapai target.");
        runLost = true;
        return;
    }

    line();
    line("[INVARIANT] PHASE 3 - PlayerTurnLoop selesai");

    line();
    line("[INVARIANT] PHASE 4 - EvaluateResult");
    info("Score akhir: " + std::to_string(totalScore));
    info("Target    : " + std::to_string(targetScore));
    line("[WIN] Target tercapai.");

    int reward = 4 + commitLeft + rerollLeft;
    coins += reward;

    line();
    line("[RESULT] ROUND CLEAR");
    info("Reward coin: +" + std::to_string(reward) + " (totalCoin=" + std::to_string(coins) + ")");
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
