#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
using namespace sf;
class Game {
private:
    RenderWindow* window;
    Board* board;
    Font font;
    Text scoreText;
    int score;
    int moves;
    bool firstSelected;
    Vector2i firstCell;
 enum class GameState{start, Playing,GameOver};
 GameState gameState;
 Texture backgroundTexture;
 Sprite backgroundSprite;
 Text startText;
 Text gameOverText;
 Text restarText;
 Text exitText;

public:
    Game();
    ~Game();

    void handleClick(Vector2i cell);
    void run();
    void processEvents();
    void update();
    void render();
    void resolveMatches();
    void showStartScreen();
};

#endif
