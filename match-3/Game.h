#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
<<<<<<< HEAD
=======
#include <memory>
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
#include "BoardLogic.h"
#include "BoardRender.h"
#include "Objective.h"
#include "GameUI.h"
#include "LevelManager.h"
<<<<<<< HEAD
=======
#include "RankingManager.h"
>>>>>>> 2175d52 (Agregar archivos de proyecto.)

using namespace sf;
using namespace std;

class Game {
private:
<<<<<<< HEAD
	RenderWindow* gameWindow;
	BoardLogic* boardLogic;
=======
	unique_ptr<RenderWindow> gameWindow;
	unique_ptr <BoardLogic> boardLogic;
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
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
<<<<<<< HEAD
	
public:
	Game();
	~Game();
=======
	void resetAllGameData();
	string playerName;
	
public:
	Game();
>>>>>>> 2175d52 (Agregar archivos de proyecto.)

	void run();
	void processEvents();
	void update();
	void render();
};

#endif
