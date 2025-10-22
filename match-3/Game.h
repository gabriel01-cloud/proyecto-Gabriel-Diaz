#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoardLogic.h"
#include "BoardRender.h"
#include "Objective.h"
#include "GameUI.h"
#include "LevelManager.h"

using namespace sf;
using namespace std;

class Game {
private:
	RenderWindow* gameWindow;
	BoardLogic* boardLogic;
	BoardRender boardRenderer;
	int playerScore;
	int remainingMoves;
	Font uiFontAsset;

	Texture backgroundTexture;
	Sprite backgroundSprite;

	bool isFirstCellSelected;
	Vector2i selectedCell;

	Objective levelObjective;
	GameUI gameUI;
	LevelManager levelManager;

	void handleClick(Vector2i cell);
	void resolveAllMatches();
	void loadCurrentLevel();
	
public:
	Game();
	~Game();

	void run();
	void processEvents();
	void update();
	void render();
};

#endif
