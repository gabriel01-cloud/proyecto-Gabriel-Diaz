#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "BoardLogic.h"
#include "BoardRender.h"
#include "Objective.h"
#include "GameUI.h"
#include "LevelManager.h"
#include "RankingManager.h"

using namespace sf;
using namespace std;

class Game {
private:
	unique_ptr<RenderWindow> gameWindow;
	unique_ptr <BoardLogic> boardLogic;
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
	void resetAllGameData();
	string playerName;
	
public:
	Game();

	void run();
	void processEvents();
	void update();
	void render();
};

#endif
