#pragma once
#ifndef BOARDLOGIC_H
#define BOARDLOGIC_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gem.h"
#include "NormalGem.h"
#include "BombGem.h"
#include "IceGem.h"

#define MAX_MATCHES 64
using namespace sf;
using namespace std;

class BoardLogic {
private:
	int boardWidth,boardHeight;
	Gem*** gemGrid;
	int iceChancePercent;
	bool avoidRefillMatches;
	int cascadeDampingPercent;
	int promoteRun4ChancePercent;
	bool wouldCreateImmediateMatch(int r, int c, int type)const;
	int pickRefillType(int r, int c);
	void placeGemRefill(int r, int c, int type);
	bool lastSwapTriggeredBomb = false;
	bool suppressPromoteNext;
	int  postExplosionPromotePercent;

public:
	BoardLogic(int w, int h,int icePtc,bool avoidRefill, int cascadeDampPtc,int promote4Ptc);
	~BoardLogic();
	void applyInitialIce(int count);
	void setPostExplosionPromotePercent(int pct);
	bool consumeLastSwapTriggeredBomb();
	void update();
	void swapGems(Vector2i a, Vector2i b);
	int findMatches(Vector2i matchedCells[], int maxMatches);
	void suppressNextPromotion();
	void promoteRunOfFourOrMore(Vector2i matchedCells[], int matchCount);
	void applyMatchEffectsAndExplosions(Vector2i matchedCells[], int count);
	void removeMatchedCells(Vector2i matchedCells[], int count);
	void dropGems();
	void refill();
	bool isMoving();

	int getWidht()const { return boardWidth; }
	int getHeight() const { return boardHeight; }
	Gem* get(int c, int r) const { return gemGrid[r][c]; }
	
	bool inBounds(const Vector2i& p) const { return p.x >= 0 && p.y >= 0 && p.x < boardWidth && p.y < boardHeight;}
	bool attemptSwapAndResolve(Vector2i a, Vector2i b);
	void weakenAdjacentIceGems(const Vector2i affected[], int count);
};

#endif