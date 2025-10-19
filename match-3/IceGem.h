#pragma once
#include <iostream>
#include "Gem.h"
 
class BoardLogic;

class IceGem :public Gem {
private:
	int hits;
public:
	IceGem(int t, int posX, int posY) :Gem(t, posX, posY), hits(2) {}
	int onMatch(BoardLogic& board)override;
	bool isFrozen()const { return hits > 0; }
};
