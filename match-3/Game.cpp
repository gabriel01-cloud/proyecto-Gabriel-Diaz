#include "Game.h"
using namespace sf;
using namespace std;
Game::Game() {
	window = new RenderWindow(VideoMode(800, 600), "Match-3", Style::Close);
	board = new Board(8, 8);
	score = 0;
	moves = 20;
	gameState = GameState::start;

	if (!font.loadFromFile("imagenes/arial.ttf")) {
		cout << "No se pudo cargar la fuente\n";
	}

	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10, 550);
	scoreText.setString("Score: 0 | Moves: 20");
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
	gameState = GameState::Playing;
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
	moves--;
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
	while (!matches.empty()) {

		board->removeMatches(matches);
		score += 10;
	if (validMove) {
		moves--;
	}

		render();
		sleep(milliseconds(400));

		board->dropGems();
		render();
		sleep(milliseconds(400));

		board->refill();
		render();
		sleep(milliseconds(400));

		matches = board->findMatches();
	}
}

void Game::showStartScreen()
{

	Font font;
	if (!font.loadFromFile("imagenes/arial.ttf")) {
		cout << "No se pudo cargar fuente\n";
		return;
	}

	Text title("MATCH-3", font, 60);
	title.setFillColor(Color::White);
	title.setPosition(220, 100);

	RectangleShape playButton(Vector2f(200, 80));
	playButton.setFillColor(Color(100, 200, 100));
	playButton.setPosition(300, 300);

	Text playText("JUGAR", font, 40);
	playText.setFillColor(Color::Black);
	playText.setPosition(345, 310);

	bool startGame = false;
	while (window->isOpen() && !startGame) {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(*window);
				if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
					startGame = true;
				}
			}
		}

		window->clear(Color::Black);
		window->draw(title);
		window->draw(playButton);
		window->draw(playText);
		window->display();
	}
}
// prueba push

