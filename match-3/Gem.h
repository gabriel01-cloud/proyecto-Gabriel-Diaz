#pragma once
#ifndef GEM_H
#define GEM_H
#include <SFML/Graphics.hpp>

class BoardLogic;

class Gem {
protected:
	int gemType;
	int posX, posY;
	int targetX, targetY;
	int gridCol, gridRow;
	int fadeAlpha;
	bool isClearingAnim;
	bool isMarkedForDeletion;
	static int sMoveSpeed;
	static int sAlphaStep;
	bool justPromoted = false;

public:
	Gem(int t, int posX, int posY);
	virtual~Gem() {}

	virtual int onMatch(BoardLogic& board) = 0;
	virtual void update();
	virtual void draw(sf::RenderTarget& rt)const {}
	static void setAnimationSpeeds(int moveSpeed, int alphaStep);
	virtual int getType() const { return gemType; }
	void setType(int t) { gemType = t; }

	int getX() const { return posX; }
	int getY() const { return posY; }

	void setPosition(int newX, int newY);
	void setTargetPosition(int newX, int newY);
	void setGrid(int col, int row);

	void markForClear() { isClearingAnim = true; }
	bool isMarked()const { return isMarkedForDeletion; }
	bool isIdle()const { return posX == targetX && posY == targetY && !isClearingAnim; }
	int getAlpha()const { return fadeAlpha; }
	void resetAlpha() { fadeAlpha = 255; }
	void setJustPromoted(bool v) { justPromoted = v; }
	bool wasJustPromoted() const { return justPromoted; } 
	void clearJustPromoted() { justPromoted = false; }
};

#endif
