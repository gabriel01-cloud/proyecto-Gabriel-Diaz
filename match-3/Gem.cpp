#include "Gem.h"

Gem::Gem(int t, int posX, int posY) {
    type = t;
    x = posX;
    y = posY;
    targetX = posX;
    targetY = posY;
}

int Gem::getType() const {
    return type;
}

void Gem::setType(int t) {
    type = t;
}

int Gem::getX() const {
    return x;
}

int Gem::getY() const {
    return y;
}

void Gem::setPosition(int posX, int posY) {
    x = posX;
    y = posY;
}
void Gem::setTargetPosition(int posX, int posY) {
    targetX = posX;
    targetY = posY;
}
void Gem::update() {
    int speed = 5;
    if (y < targetY) {
        y += speed;
        if (y > targetY)y = targetY;
    }
    if (y > targetY) {
        y -= speed;
        if (y < targetY)y = targetY;
    }
    if (x < targetX) {
        x += speed;
        if (y > targetY)y = targetY;
    }
    if (x > targetX) {
        x -= speed;
        if (x < targetX)x = targetX;
    }
}
