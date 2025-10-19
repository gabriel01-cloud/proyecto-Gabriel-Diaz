#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Objective.h"
using namespace sf;
using namespace std;
class GameUI
{
private:
	Objective* objective;
	Font* font;
	RectangleShape panel;
	Text titleText;
	Text lines[5];
	Text scoreMovesText;
	RectangleShape colorSwatch[5];
public:
	GameUI();
	void init(Font* uiFont);
	void setObjective(Objective* obj);
	void setScoreMoves(int score, int moves);
	void refreshObjectiveView();
	void draw(RenderWindow& window);

	RectangleShape createButton(Vector2f size, Vector2f position, Color color);
	Text createText(const string& str, Font& font, unsigned int size, Color color, Vector2f position);

	bool isButtonClicked(RenderWindow& window, RectangleShape& button, Event& event);
	bool showStartScreen(RenderWindow& window);
	int showEndScreen(RenderWindow& window, int finalScore);
};