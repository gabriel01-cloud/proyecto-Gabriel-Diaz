#pragma once
#include <iostream>
#include "Gem.h"

class NormalGem : public Gem {
public: 
	NormalGem(int t, int posX, int posY) :Gem(t, posX, posY) {}
	int onMatch(BoardLogic& board)override {
		markForClear();
		return 0;
	}
};