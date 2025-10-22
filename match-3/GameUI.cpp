#include "GameUI.h"

GameUI::GameUI() :levelObjective(nullptr), uiFont(nullptr)
{
	sidePanel.setSize(Vector2f(220.f, 600.f));
	sidePanel.setFillColor(Color(230, 230, 230));
	sidePanel.setPosition(800.f - 220.f, 0.f);
	for (int i = 0; i < 5; ++i) {
		objectiveLines[i] = sf::Text();
		objectiveSwatches[i] = sf::RectangleShape();
	}
}

void GameUI::init(Font* fontPtr)
{
	uiFont = fontPtr;
	titleText.setFont(*uiFont);
	titleText.setCharacterSize(22);
	titleText.setFillColor(Color::Black);
	titleText.setString("Objetivos");
	titleText.setPosition(800.f - 200.f, 20.f);

	scoreAndMovesText.setFont(*uiFont);
	scoreAndMovesText.setCharacterSize(18);
	scoreAndMovesText.setFillColor(Color::Black);
	scoreAndMovesText.setString("Score: 0 | Moves: 0");
	scoreAndMovesText.setPosition(800.f - 210.f, 60.f);

	for (int i = 0; i < 5; i++) {
		objectiveLines[i].setFont(*uiFont);
		objectiveLines[i].setCharacterSize(18);
		objectiveLines[i].setFillColor(Color::Black);
		objectiveLines[i].setString("Tipo " + to_string(i) + ":0/0");
		objectiveLines[i].setPosition(800.f - 180.f, 120.f + i * 30.f + 2.f);

		auto clamp255 = [](unsigned v) {return v > 255u ? 255u : v; };
		objectiveSwatches[i].setSize(Vector2f(18.f, 18.f));
		objectiveSwatches[i].setFillColor(Color(50 * (i + 1), 80 * (i + 1), 100));
		objectiveSwatches[i].setPosition(800.f - 210.f, 120.f + i * 30.f + 2.f);
	}
}

void GameUI::setObjective(Objective* obj)
{
	levelObjective = obj;
	refreshObjectiveView();
}

void GameUI::setScoreMoves(int score, int moves)
{
	scoreAndMovesText.setString("Puntos: " + to_string(score) + " | Movimientos: " + to_string(moves));

}

void GameUI::refreshObjectiveView()
{
	if (!levelObjective)return;
	for (int i = 0; i < 5; i++) {
		int tgt = levelObjective->getTarget(i);
		int cur = levelObjective->getProgress(i);
		if (tgt > 0) {
			objectiveLines[i].setString("Tipo " + to_string(i) + ": " + to_string(cur) + "/" + to_string(tgt));
		}
		else {
			objectiveLines[i].setString("");
		}
	}
}

void GameUI::draw(RenderWindow& window)
{
	window.draw(sidePanel);
	window.draw(titleText);
	window.draw(scoreAndMovesText);
	for (int i = 0; i < 5; i++) {
		if (!objectiveLines[i].getString().isEmpty()) {
			window.draw(objectiveSwatches[i]);
			window.draw(objectiveLines[i]);
		}
	}
}
RectangleShape GameUI::createButton(Vector2f size, Vector2f position, Color color)
{
	RectangleShape button(size);
	button.setFillColor(color);
	button.setPosition(position);
	button.setOutlineColor(Color::White);
	button.setOutlineThickness(2.f);
	return button;
}

Text GameUI::createText(const string& str, Font& font, unsigned int size, Color color, Vector2f position)
{
	Text text;
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(position.x, position.y);
	return text;

}

bool GameUI::isButtonClicked(RenderWindow& window, RectangleShape& button, Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		Vector2f m = window.mapPixelToCoords({ event.mouseButton.x ,event.mouseButton.y });
		return button.getGlobalBounds().contains(m);
	}
	return false;
}

bool GameUI::showStartScreen(RenderWindow& window)
{
	Text title = createText("Zombie match-3", *uiFont, 60, Color::White, { 220,100 });
	RectangleShape playButton = createButton({ 200,80 }, { 300,300 }, Color(100, 200, 100));
	Text playText = createText("JUGAR", *uiFont, 40, Color::Black, { 345,310 });
	RectangleShape exitButton = createButton({ 200.f,809.f }, { 300.f,4009.f }, Color(200,100,100));
	Text exitText = createText("SALIR", *uiFont, 40, Color::Black, { 360.f,410.f });
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}
			if (isButtonClicked(window, playButton, event)) {
				return true;
			}
			if (isButtonClicked(window, exitButton, event)) {
				return false;
			}
		}
		window.clear(Color::Black);
		window.draw(title);
		window.draw(playButton);
		window.draw(playText);
		window.display();
	}
	return false;
}
int GameUI::showEndScreen(RenderWindow& window, int finalScore)
{
	Text finalText = createText("Puntaje: " + to_string(finalScore), *uiFont, 40, Color::White, { 220.f,150.f });

	RectangleShape restartButton = createButton({ 200, 80 }, { 300, 300 }, Color(100, 200, 100));
	Text restartText = createText("REINICIAR", *uiFont, 30, Color::Black, { 325, 320 });

	RectangleShape exitButton = createButton({ 200, 80 }, { 300, 420 }, Color(200, 100, 100));
	Text exitText = createText("SALIR", *uiFont, 30, Color::Black, { 365, 440 });

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}
			if (isButtonClicked(window, restartButton, event))return 1;
			if (isButtonClicked(window, exitButton, event)) return 0;
		}
		window.clear(Color::Black);
		window.draw(finalText);
		window.draw(restartButton);
		window.draw(restartText);
		window.draw(exitButton);
		window.draw(exitText);
		window.display();
	}
}

int GameUI::showResultScreen(RenderWindow& window, bool won, int finalScore, int levelIndex, bool hasNext)
{
	string titleStr = won ? "!Ganaste¡" : "Perdiste";
	Text title = createText(titleStr, *uiFont, 48, Color::White, { 220.f,100.f });
	Text score = createText("Puntaje: " + to_string(finalScore), *uiFont, 26, Color::White, { 220.f,160.f });
	Text level = createText("Nivel " + to_string(levelIndex), *uiFont, 22, Color(200, 200, 200), { 220.f,200.f });
	RectangleShape nextButton = createButton({ 260.f,70.f }, { 270.f,260.f }, won && hasNext ? Color(60, 160, 100) : Color(90, 90, 90));
	Text nextText = createText(hasNext ? "Siguiente nivel" : "No hay mas niveles", *uiFont, 24, Color::Black, { 280.f, 282.f });
	RectangleShape restartButton = createButton({ 140.f,50.f }, { 640.f,530.f }, Color(100, 180, 240));
	Text restartText = createText("Reiniciar", *uiFont, 20, Color::Black, { 658.f,545.f });

	RectangleShape menuButton = createButton({ 260.f,70.f }, { 270.f,350.f }, Color(60, 120, 200));
	Text menuText = createText("Menu principal", *uiFont, 24, Color::Black, { 300.f,372.f });
	RectangleShape exitButton = createButton({ 260.f,70.f }, { 270.f,440.f }, Color(180, 70, 70));
	Text exitText = createText("Salir", *uiFont, 24, Color::Black, { 360.f,462.f });

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) { window.close(); return-1; }
			if (isButtonClicked(window, exitButton, event)) return -1;
			if (isButtonClicked(window, menuButton, event)) return 0;
			if (isButtonClicked(window, restartButton, event))return 2;
			if (won && hasNext && isButtonClicked(window, nextButton, event))return 1;
		}
		window.clear(Color::Black);
		window.draw(title);
		window.draw(score);
		window.draw(level);
		window.draw(nextButton);
		window.draw(nextText);
		window.draw(restartButton);
		window.draw(restartText);
		window.draw(menuButton);
		window.draw(menuText);
		window.draw(exitButton);
		window.draw(exitText);
		window.display();
	}
	return -1;
}