#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoardLogic.h"
#include "BoardRender.h"
using namespace sf;
using namespace std;
struct Button {
	RectangleShape shape;
	Text text;
};
class Game {
private:
	RenderWindow* window;
	BoardLogic* logic;
	BoardRender renderBoard;
	Font font;
	Text scoreText;
	int score;
	int moves;
	bool firstSelected;
	Vector2i firstCell;

	Texture backgroundTexture;
	Sprite backgroundSprite;

	void handleClick(Vector2i cell);
	void resolveMatches();

	RectangleShape createButton(Vector2f size, Vector2f position, Color color);
	Text createText(const string& str, Font& font, unsigned int size, Color color, Vector2f position);
	bool isButtonClicked(RenderWindow& window, RectangleShape& button, Event& event);
public:
	Game();
	~Game();

	void run();
	void processEvents();
	void update();
	void render();

	void showStartScreen();
	void showEndScreen();
};

#endif
