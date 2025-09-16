#pragma once
#ifndef GEM_H
#define GEM_H

#include <SFML/Graphics.hpp>

class Gem {
private:
	int type;
	int x, y;
	int targetX, targetY;
public:
	Gem(int t, int posX, int posY);

	int getType() const;
	void setType(int t);

	int getX() const;
	int getY() const;

	void setPosition(int posX, int posY);
	void setTargetPosition(int posX, int posY);

	void update();
};

#endif
