#pragma once
#include "Gem.h"

class BoardLogic;

enum SpecialType {
NORMAL,
BOMB
};

class SpecialGem:public Gem {
private:
SpecialType special;
public:
SpecialGem(int t, int posX, int posY, SpecialType sp = NORMAL) :Gem(t, posX, posY), special(sp) {}
void setSpecial(SpecialType sp) { special = sp; }
SpecialType getSpecial()const { return special; }
int onMatch(BoardLogic& board)override;
};
