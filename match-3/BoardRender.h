#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "BoardLogic.h"
using namespace sf;

class BoardRender
{
private:
	Texture textures[5];
public:
	void loadTextures();
	void draw(RenderWindow& window, BoardLogic& logic);
};

