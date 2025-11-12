#pragma once
#include "Gem.h"

class BoardLogic;

class IceGem : public Gem {
private:
    int remainingHits;
public:
    IceGem(int t, int posX, int posY) : Gem(t, posX, posY), remainingHits(2) {}

    int onMatch(BoardLogic& board) override {
        if (remainingHits > 0) {         
            remainingHits--;
        }
            return 0;
    }

    bool isFrozen() const { return remainingHits > 0; }
};
