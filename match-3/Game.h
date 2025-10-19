#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoardLogic.h"
#include "BoardRender.h"
#include "Objective.h"
#include "GameUI.h"

using namespace sf;
using namespace std;

class Game {
private:
	RenderWindow* window;
	BoardLogic* logic;
	BoardRender renderBoard;
	int score;
	int moves;
	Font font;

	Texture backgroundTexture;
	Sprite backgroundSprite;

	bool firstSelected;
	Vector2i firstCell;

	Objective objective;
	GameUI gameUI;

	void handleClick(Vector2i cell);
	void resolveMatches();

	
public:
	Game();
	~Game();

	void run();
	void processEvents();
	void update();
	void render();
};

#endif
