#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoardLogic.h"
using namespace sf;

class BoardRender
{
private:
	Texture gemTextures[7];
public:
	void loadTextures();
	void draw(RenderWindow& window, BoardLogic& boardLogic);
};