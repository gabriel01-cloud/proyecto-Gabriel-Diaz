#include "GameUI.h"

GameUI::GameUI():objective(nullptr),font(nullptr)
{
	panel.setSize(Vector2f(220.f, 600.f));
	panel.setFillColor(Color(230, 230, 230));
	panel.setPosition(800.f - 220.f, 0.f);
	for (int i = 0; i < 5; ++i) {
		lines[i] = sf::Text();
		colorSwatch[i] = sf::RectangleShape();
	}
}

void GameUI::init(Font* uiFont)
{
	font = uiFont;
	titleText.setFont(*font);
	titleText.setCharacterSize(22);
	titleText.setFillColor(Color::Black);
	titleText.setString("Objetivos");
	titleText.setPosition(800.f - 200.f, 20.f);

	scoreMovesText.setFont(*font);
	scoreMovesText.setCharacterSize(18);
	scoreMovesText.setFillColor(Color::Black);
	scoreMovesText.setString("Score: 0 | Moves: 0");
	scoreMovesText.setPosition(800.f-210.f,60.f);

	for (int i = 0; i < 5; i++) {
		lines[i].setFont(*font);
		lines[i].setCharacterSize(18);
		lines[i].setFillColor(Color::Black);
		lines[i].setString("Tipo " + to_string(i) + ":0/0");
		lines[i].setPosition(800.f - 180.f, 120.f + i * 30.f + 2.f);
		
		colorSwatch[i].setSize(Vector2f(18.f, 18.f));
		colorSwatch[i].setFillColor(Color(50 * (i + 1), 80 * (i + 1), 100));
		colorSwatch[i].setPosition(800.f - 210.f, 120.f + i * 30.f + 2.f);
	}
}

void GameUI::setObjective(Objective* obj)
{
	objective = obj;
	refreshObjectiveView();
}

void GameUI::setScoreMoves(int score, int moves)
{
	scoreMovesText.setString("Puntos: " + to_string(score) + " | Movimientos: " + to_string(moves));

}

void GameUI::refreshObjectiveView()
{
	if (!objective)return;
	for (int i = 0; i < 5; i++) {
		int tgt = objective->getTarget(i);
		int cur = objective->getProgress(i);
		if (tgt <= 0) {
			lines[i].setString("Tipo " + to_string(i) + ": " + to_string(cur) + "/" + to_string(tgt));
		}
	}
}

void GameUI::draw(RenderWindow& window)
{
	window.draw(panel);
	window.draw(titleText);
	window.draw(scoreMovesText);
	for (int i = 0; i < 5; i++) {
		window.draw(colorSwatch[i]);
		window.draw(lines[i]);
	}
}
RectangleShape GameUI::createButton(Vector2f size, Vector2f position, Color color)
{
	RectangleShape button(size);
	button.setFillColor(color);
	button.setPosition(position);
	return button;
}

Text GameUI::createText(const string& str, Font& font, unsigned int size, Color color, Vector2f position)
{
	Text text;
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(position.x,position.y);
	return text;
}

bool GameUI::isButtonClicked(RenderWindow& window, RectangleShape& button, Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2i mousePos = Mouse::getPosition(window);
		return button.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
	}
	return false;
}

bool GameUI::showStartScreen(RenderWindow& window)
{
	Text title = createText("Zombie match-3", *font, 60, Color::White, { 220,100 });
	RectangleShape playButton = createButton({ 200,80 }, { 300,300 }, Color(100, 200, 100));
	Text playText = createText("JUGAR", *font, 40, Color::Black, { 345,310 });

	bool startGame = false;
	while (window.isOpen() && !startGame) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (isButtonClicked(window, playButton, event)) {
				startGame = true;
			}
		}
		window.clear(Color::Black);
		window.draw(title);
		window.draw(playButton);
		window.draw(playText);
		window.display();
	}
	return startGame;
}
int GameUI::showEndScreen(RenderWindow& window, int finalScore)
{
	Text FinalText = createText(": " + to_string(finalScore), *font, 40, Color::White, { 220,150 });

	RectangleShape restartButton = createButton({ 200, 80 }, { 300, 300 }, Color(100, 200, 100));
	Text restartText = createText("REINICIAR", *font, 30, Color::Black, { 325, 320 });

	RectangleShape exitButton = createButton({ 200, 80 }, { 300, 420 }, Color(200, 100, 100));
	Text exitText = createText("SALIR", *font, 30, Color::Black, { 365, 440 });

	bool waiting = true;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close(); 
				return 0;
			}
			if (isButtonClicked(window, restartButton, event))return 1; 
			/*	delete logic;
				logic = new BoardLogic(8, 8);
				score = 0;
				moves = 20;

				firstSelected = false;
				firstCell = { -1, -1 };

				scoreText.setString("Score: 0 | Moves: " + to_string(moves));

				return;
			}*/

			if (isButtonClicked(window, exitButton, event)) return 0;
			/*	window->close();
				return;
			}*/
		}
		window.clear(Color::Black);
		window.draw(FinalText);
		window.draw(restartButton);
		window.draw(restartText);
		window.draw(exitButton);
		window.draw(exitText);
		window.display();
	}
}