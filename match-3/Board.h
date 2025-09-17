#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gem.h"
using namespace sf;
using namespace std;

class Board {
private:
	int width;
	int height;
	Gem*** grid;
	Texture textures[5];

public:
	Board(int w, int h);
	~Board();

	void loadTextures();
	void draw(sf::RenderWindow& window);
	void refill();
	void swapGems(Vector2i a, Vector2i b);
	vector<Vector2i> findMatches();
	void removeMatches(const vector<Vector2i>& matches);
	void dropGems();
	void update();
	bool isMoving();
};

#endif