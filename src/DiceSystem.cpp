#include "DiceSystem.h"
#include <iostream>

int DiceSystem::rollValueForSlot(int slotIndex) const {
    std::cout << "[DiceSystem] rollValueForSlot(" << slotIndex << ")\n";
    return 1;
}

std::vector<int> DiceSystem::rollDice(int count) {
    // TODO: roll sebanyak count, kembalikan vector hasil
    std::cout << "[DiceSystem] rollDice count=" << count << "\n";
    return std::vector<int>(count, 1);
}

void DiceSystem::rerollDice(std::vector<int>& dice) {
    // TODO: minta input index dari pemain, reroll dadu yang dipilih
    std::cout << "[DiceSystem] rerollDice\n";
}

void DiceSystem::setDiceTypeName(int slotIndex, const std::string& typeName) {
    // TODO: set nama tipe dadu pada slot tertentu
    std::cout << "[DiceSystem] setDiceTypeName slot=" << slotIndex << " name=" << typeName << "\n";
}

std::string DiceSystem::getDiceTypeNameAt(int slotIndex) const {
    return "norml";
}

std::vector<std::string> DiceSystem::getDiceTypeNames(int count) const {
    return std::vector<std::string>(count, "norml");
}

int DiceSystem::calculateDiceValueScore(const std::vector<int>& dice) const {
    std::cout << "[DiceSystem] calculateDiceValueScore\n";
    return 0;
}

double DiceSystem::calculateFinalScoreMultiplier(const std::vector<int>& dice) const {
    return 1.0;
}
