#include "DiceSystem.h"
#include <cstdlib>

int DiceSystem::rollValueForSlot(int slotIndex) const {
    (void)slotIndex;
    return (rand() % 6) + 1;
}

std::vector<int> DiceSystem::rollDice(int count) {
    // TODO: roll sebanyak count, kembalikan vector hasil
    std::vector<int> dice(count);
    for (int i = 0; i < count; i++) {
        dice[i] = rollValueForSlot(i);
    }
    return dice;
}

void DiceSystem::rerollDice(std::vector<int>& dice) {
    // TODO: minta input index dari pemain, reroll dadu yang dipilih
    for (size_t i = 0; i < dice.size(); i++) {
        dice[i] = rollValueForSlot(static_cast<int>(i));
    }
}

void DiceSystem::setDiceTypeName(int slotIndex, const std::string& typeName) {
    // TODO: set nama tipe dadu pada slot tertentu
}

std::string DiceSystem::getDiceTypeNameAt(int slotIndex) const {
    return "norml";
}

std::vector<std::string> DiceSystem::getDiceTypeNames(int count) const {
    return std::vector<std::string>(count, "norml");
}

int DiceSystem::calculateDiceValueScore(const std::vector<int>& dice) const {
    return 0;
}

double DiceSystem::calculateFinalScoreMultiplier(const std::vector<int>& dice) const {
    return 1.0;
}
