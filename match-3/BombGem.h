#pragma once
#include <iostream>
#include "Gem.h"

class BoardLogic;

class BombGem : public Gem{
public:
	BombGem(int t, int posX, int posY) :Gem(t, posX, posY) {}
	int onMatch(BoardLogic& board)override {
		markForClear();
		return 3;
	}
};