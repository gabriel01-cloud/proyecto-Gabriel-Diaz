#pragma once
#ifndef GEM_H
#define GEM_H
#include <SFML/Graphics.hpp>

class BoardLogic;

class Gem {
protected:
	int type;
	int x, y;
	int targetX, targetY;
	int col, row;
	int alpha;
	bool animClearing;
	bool marked;
public:
	Gem(int t, int posX, int posY);
	virtual~Gem() {}

	virtual int onMatch(BoardLogic& board) = 0;
	virtual void update();

	int getType() const { return type; }
	void setType(int t) { type = t; }
	int getX() const { return x; }
	int getY() const { return y; }

	void setPosition(int posX, int posY);
	void setTargetPosition(int posX, int posY);
	void setGrid(int c, int r);

	void markForClear() { animClearing = true; }
	bool isMarked()const { return marked; }
	bool isIdle()const { return x == targetX && y == targetY && !animClearing; }
};

#endif
