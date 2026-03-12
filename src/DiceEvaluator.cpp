#include "DiceEvaluator.h"
#include <iostream>

EvalResult DiceEvaluator::evaluate(const std::vector<int>& dice) {
    // TODO: deteksi semua combo (Doble Luck, Chain, Golden Chain, dll)
    // TODO: akumulasi baseScore dan multiplier dari semua combo aktif
    std::cout << "[DiceEvaluator] Evaluasi " << dice.size() << " dadu\n";
    return {0, 1.0, {"No Combo"}};
}
