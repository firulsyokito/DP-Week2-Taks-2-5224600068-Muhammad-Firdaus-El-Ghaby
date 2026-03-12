#pragma once
#include <vector>
#include <string>

// Mengelola dadu: roll dan reroll
class DiceSystem {
private:
    std::vector<std::string> diceTypeNames;

    int rollValueForSlot(int slotIndex) const;

public:
    std::vector<int> rollDice(int count);
    void rerollDice(std::vector<int>& dice);
    void setDiceTypeName(int slotIndex, const std::string& typeName);
    std::string getDiceTypeNameAt(int slotIndex) const;
    std::vector<std::string> getDiceTypeNames(int count) const;
    int calculateDiceValueScore(const std::vector<int>& dice) const;
    double calculateFinalScoreMultiplier(const std::vector<int>& dice) const;
};
