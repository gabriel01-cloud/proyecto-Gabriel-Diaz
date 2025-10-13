#include "Game.h"
using namespace sf;
using namespace std;
Game::Game() {
	window = new RenderWindow(VideoMode(800, 600), "Match-3", Style::Close);
	board = new Board(8, 8);
	score = 0;
	moves = 20;

	if (!font.loadFromFile("imagenes/arial.ttf")) {
		cout << "No se pudo cargar la fuente\n";
	}

	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::Black);
	scoreText.setPosition(10, 550);
	scoreText.setString("Score: 0 | Moves: "+to_string(moves));
	if (!backgroundTexture.loadFromFile("imagenes/fondo.png"))
		cout << "No se pudo abrir";
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(800.0f / backgroundTexture.getSize().x, 600.0f / backgroundTexture.getSize().y);
	firstSelected = false;
	firstCell = { -1,-1 };
}

Game::~Game() {
	delete board;
	delete window;
}

void Game::run() {
	showStartScreen();
	if (!window->isOpen())return;
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
		cout << "Primera gema(" << cell.x << "," << cell.y << ") selecciona\n";
		return;
	}
	int dx = abs(firstCell.x - cell.x);
	int dy = abs(firstCell.y - cell.y);
	if (dx + dy != 1) {
		cout << " No son adyacentes\n";
		firstSelected = false;
		return;
	}
	board->swapGems(firstCell, cell);
	cout << "intercambiadas(" << firstCell.x << "," << firstCell.y << ") con (" << cell.x << "," << cell.y << ")\n";

	auto matches = board->findMatches();
	if (matches.empty()) {
		board->swapGems(firstCell, cell);
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
		if (event.type == Event::Closed)
			window->close();

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			Vector2i mousePos = Mouse::getPosition(*window);
			int col = mousePos.x / 64;
			int row = mousePos.y / 64;

			if (col >= 0 && col < 8 && row >= 0 && row < 8) {
				handleClick({ col,row });
			}
		}
	}
}

void Game::update() {

	scoreText.setString("Score: " + to_string(score) + " | Moves: " + to_string(moves));
	if (moves <= 0) {
		showEndScreen();
	}
}

void Game::render() {
	window->clear();
	window->draw(backgroundSprite);
	board->draw(*window);
	if (firstSelected) {
		RectangleShape outline(Vector2f(64, 64));
		outline.setPosition(firstCell.x * 64, firstCell.y * 64);
		outline.setFillColor(Color::Transparent);
		outline.setOutlineColor(Color::Red);
		outline.setOutlineThickness(3);
		window->draw(outline);
	}
	window->draw(scoreText);
	window->display();
}

void Game::resolveMatches() {
	auto matches = board->findMatches();
	bool validMove = !matches.empty();
	if (validMove) {
		moves--;
	}

	while (!matches.empty()) {
		board->removeMatches(matches);
		score += matches.size()*10;

		render();
		board->dropGems();
		while (board->isMoving() && window->isOpen()) {
			board->update();
			render();
		}

		board->refill();
		while (board->isMoving() && window->isOpen()) {
			board->update();
			render();
		}
		matches = board->findMatches();
	}
	if (moves <= 0) {
		showEndScreen();
	}
}


RectangleShape Game::createButton(Vector2f size, Vector2f position, Color color)
{
	RectangleShape button(size);
	button.setFillColor(color);
	button.setPosition(position);
	return button;
}

Text Game::createText(const string& str, Font& font, unsigned int size, Color color, Vector2f position)
{
	Text text(str, font, size);
	text.setFillColor(color);
	text.setPosition(position);
	return text;
}

bool Game::isButtonClicked(RenderWindow& window, RectangleShape& button, Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2i mousePos = Mouse::getPosition(window);
		return button.getGlobalBounds().contains(mousePos.x, mousePos.y);
	}
	return false;
}

void Game::showStartScreen()
{
	Text title = createText("match-3", font, 60, Color::White, { 220,100 });
	RectangleShape playButton = createButton({ 200,80 }, { 300,300 }, Color(100, 200, 100));
	Text playText = createText("JUGAR", font, 40, Color::Black, { 345,310 });

	bool startGame = false;
	while (window->isOpen() && !startGame) {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
			if (isButtonClicked(*window, playButton, event)) {
				startGame = true;
			}
		}
		window->clear(Color::Black);
		window->draw(title);
		window->draw(playButton);
		window->draw(playText);
		window->display();
	}
}
void Game::showEndScreen()
{
	string scoreStr = "PUNTAJE FINAL: " + to_string(score);
	Text finalScore = createText(scoreStr, font, 40, Color::White, { 220, 150 });

	RectangleShape restartButton = createButton({ 200, 80 }, { 300, 300 }, Color(100, 200, 100));
	Text restartText = createText("REINICIAR", font, 30, Color::Black, { 325, 320 });

	RectangleShape exitButton = createButton({ 200, 80 }, { 300, 420 }, Color(200, 100, 100));
	Text exitText = createText("SALIR", font, 30, Color::Black, { 365, 440 });

	bool waiting = true;
	while (window->isOpen() && waiting) {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) window->close();

			if (isButtonClicked(*window, restartButton, event)) {
				delete board;
				board = new Board(8, 8);
				score = 0;
				moves = 20;

				firstSelected = false;
				firstCell = { -1, -1 };

				scoreText.setString("Score: 0 | Moves: " + to_string(moves));

				return;
			}

			if (isButtonClicked(*window, exitButton, event)) {
				window->close();
				return;
			}
		}
		window->clear(Color::Black);
		window->draw(finalScore);
		window->draw(restartButton);
		window->draw(restartText);
		window->draw(exitButton);
		window->draw(exitText);
		window->display();
	}
}
