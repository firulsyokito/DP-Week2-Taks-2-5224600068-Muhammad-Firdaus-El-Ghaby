#pragma once
#include "ScoringSystem.h"
#include "DiceSystem.h"

// Mengelola toko antar ronde: pemain bisa beli item dan upgrade combo
class ShopSystem {
public:
    void openShop(ScoringSystem& scoringSystem, DiceSystem& diceSystem, int& coins);
};
