#include "Gem.h"

Gem::Gem(int t, int posX, int posY) : col(posX / 64), row(posY / 64), alpha(255), animClearing(false), marked(false) {
	type = t;
	x = posX;
	y = posY;
	targetX = posX;
	targetY = posY;
}
void Gem::setPosition(int posX, int posY) {
	x = posX;
	y = posY;
}
void Gem::setTargetPosition(int posX, int posY) {
	targetX = posX;
	targetY = posY;
}
void Gem::setGrid(int c, int r) {
	col = c;
	row = r;
	setTargetPosition(c * 64, r * 64);
}
void Gem::update() {
	const int speed = 5;
	if (y < targetY) { y += speed; if (y > targetY)y = targetY; }
	if (y > targetY) { y -= speed; if (y < targetY)y = targetY; }
	if (x < targetY) { x += speed; if (x > targetX)x = targetX; }
	if (x > targetX) { x -= speed; if (x < targetX)x = targetX; }
	if (animClearing) {
		alpha -= 20;
		if (alpha < 0)alpha = 0;
		if (alpha == 0) {
			animClearing = false;
			marked = true;
		}
	}
}
