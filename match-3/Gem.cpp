#include "Gem.h"

int Gem::sMoveSpeed = 3;
int Gem::sAlphaStep = 10;
Gem::Gem(int t, int posX, int posY) : gridCol(posX / 64), gridRow(posY / 64), fadeAlpha(255), isClearingAnim(false), isMarkedForDeletion(false) {
	gemType = t;
	this->posX = posX;
	 this->posY= posY;
	targetX = posX;
	targetY = posY;
}
void Gem::setPosition(int newX, int newY) {
	posX = newX;
	posY = newY;
}
void Gem::setTargetPosition(int newX, int newY) {
	targetX = newX;
	targetY = newY;
}
void Gem::setGrid(int col, int row) {
	gridCol = col;
	gridRow= row;
	setTargetPosition(col * 64, row * 64);
}
void Gem::update() {
    const int speed = sMoveSpeed;
    if (posY < targetY) { posY += speed; if (posY > targetY) posY = targetY; }
    if (posY > targetY) { posY -= speed; if (posY < targetY) posY = targetY; }
    if (posX < targetX) { posX += speed; if (posX > targetX) posX = targetX; }
    if (posX > targetX) { posX -= speed; if (posX < targetX) posX = targetX; }
<<<<<<< HEAD

    if (isClearingAnim) {
        fadeAlpha -= 20;
    }
=======
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
    if(isClearingAnim){
        fadeAlpha -= sAlphaStep;
        if (fadeAlpha < 0) fadeAlpha = 0;
        if (fadeAlpha == 0) {
            isClearingAnim = false;
            isMarkedForDeletion = true;
        }
    }
}

void Gem::setAnimationSpeeds(int moveSpeed, int alphaStep)
{
    if (moveSpeed <= 0)moveSpeed = 1;
    if (alphaStep <= 0)alphaStep = 1;
    sMoveSpeed = moveSpeed;
    sAlphaStep = alphaStep;
}
