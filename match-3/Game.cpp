#include "Game.h"

using namespace sf;
using namespace std;
Game::Game() {
	window = new RenderWindow(VideoMode(800, 600), "Match-3", Style::Close);
	logic = new BoardLogic(8, 8);
	renderBoard.loadTextures();
	score = 0;
	moves = 20;

	if (!font.loadFromFile("imagenes/arial.ttf")) {
		cout << "No se pudo cargar la fuente\n";
	}
	if (!backgroundTexture.loadFromFile("imagenes/fondo.png"))
		cout << "No se pudo abrir fondo";
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(800.0f / backgroundTexture.getSize().x, 600.0f / backgroundTexture.getSize().y);
	firstSelected = false;
	firstCell = { -1,-1 };
	gameUI.init(&font);
	gameUI.setObjective(&objective);
	objective.reset();
	objective.setTarget(0, 10);
	objective.setTarget(3, 8);
	gameUI.setScoreMoves(score, moves);
}
Game::~Game() {
	delete logic;
	delete window;
}
void Game::run() {
	if (!gameUI.showStartScreen(*window))return;
	while (window->isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::handleClick(Vector2i cell) {
	if (!firstSelected) {
		firstSelected = true;
		firstCell = cell;
		return;
	}
	int dx = abs(firstCell.x - cell.x);
	int dy = abs(firstCell.y - cell.y);
	if (dx + dy != 1) {
		cout << " No son adyacentes\n";
		firstSelected = false;
		return;
	}
	logic->swapGems(firstCell, cell);

	Vector2i matches[MAX_MATCHES];
	int count = logic->findMatches(matches, MAX_MATCHES);
	if (count == 0) {
		logic->swapGems(firstCell, cell);
		cout << "Swap revertido: no se genero combinacion\n";
		firstSelected = false;
		return;
	}
	resolveMatches();
	firstSelected = false;
}
void Game::processEvents() {
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == Event::Closed) window->close();

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			Vector2i mousePos = Mouse::getPosition(*window);
			int col = mousePos.x / 64;
			int row = mousePos.y / 64;

			if (col >= 0 && col < logic->getWidht() && row >= 0 && row < logic->getHeight()) {
				handleClick({ col,row });
			}
		}
	}
}

void Game::update() {
	gameUI.setScoreMoves(score, moves);

	if (moves <= 0) {
		int choice = gameUI.showEndScreen(*window, score);
		if (choice == 1) {
			delete logic;
			logic = new BoardLogic(8, 8);
			score = 0;
			moves = 20;
			firstSelected = false;
			firstCell = { -1,-1 };
			objective.reset();
			objective.setTarget(0, 10);
			objective.setTarget(3, 8);
			gameUI.refreshObjectiveView();
			return;
		}
		else {
			window->close();
			return;
		}
	}
}

void Game::render() {
	window->clear();
	window->draw(backgroundSprite);
	renderBoard.draw(*window, *logic);
	if (firstSelected) {
		RectangleShape outline(Vector2f(64, 64));
		outline.setPosition(firstCell.x * 64, firstCell.y * 64);
		outline.setFillColor(Color::Transparent);
		outline.setOutlineColor(Color::Red);
		outline.setOutlineThickness(3);
		window->draw(outline);
	}
	gameUI.draw(*window);
	window->display();
}

void Game::resolveMatches() {
	Vector2i matches[MAX_MATCHES];
	int count = logic->findMatches(matches, MAX_MATCHES);
	bool validMove = (count > 0);
	if (validMove) {
		moves--;
	}

	while (count > 0) {
		if (count >= 4)logic->promoteIfRun4Plus(matches, count);
		for (int i = 0; i < count; i++) {
			int cx = matches[i].x, cy = matches[i].y;
			int type = logic->get(cx, cy)->getType();
			if (type >= 0 && type < 5)objective.addProgress(type, 1);
		}
		gameUI.refreshObjectiveView();
		logic->applyOnMatchAndExplosions(matches, count);
		logic->removeMatches(matches, count);
		score += count * 10;

		render();
		logic->dropGems();
		while (logic->isMoving() && window->isOpen()) {
			logic->update();
			render();
		}

		logic->refill();
		while (logic->isMoving() && window->isOpen()) {
			logic->update();
			render();
		}
		count = logic->findMatches(matches, MAX_MATCHES);
	}
	
}
