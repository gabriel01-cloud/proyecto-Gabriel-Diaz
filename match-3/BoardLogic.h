#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gem.h"
#include "SpecialGem.h"
#define MAX_MATCHES 64
using namespace sf;
using namespace std;

class BoardLogic {
private:
	int width,height;
	Gem*** grid;


public:
	BoardLogic(int w, int h);
	~BoardLogic();

	void update();
	void swapGems(Vector2i a, Vector2i b);
	int findMatches(Vector2i matches[], int maxMatches);
	void promoteIfRun4Plus(Vector2i matches[], int matchCount);
	void applyOnMatchAndExplosions(Vector2i matches[], int matchCount);
	void removeMatches(Vector2i matches[], int matchCount);
	void dropGems();
	void refill();
	bool isMoving();

	int getWitdht()const { return width; }
	int getHeight() const { return height; }
	Gem* get(int c, int r) const { return grid[r][c]; }
};
	void loadTextures();
	void draw(RenderWindow& window);

#endif