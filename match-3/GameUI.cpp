#include "GameUI.h"

GameUI::GameUI() :levelObjective(nullptr), uiFont(nullptr)
{
	sidePanel.setSize(Vector2f(220.f, 600.f));
	sidePanel.setFillColor(Color(230, 230, 230));
	sidePanel.setPosition(800.f - 220.f, 0.f);
	for (int i = 0; i < 5; ++i) {
		objectiveLines[i] = sf::Text();
		objectiveSwatches[i] = sf::RectangleShape();
		gemIconLoaded[i] = false;
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
	scoreAndMovesText.setString("Score: 0 \n Moves: 0");
	scoreAndMovesText.setPosition(800.f - 210.f, 60.f);

	for (int i = 0; i < 5; i++) {
		objectiveLines[i].setFont(*uiFont);
		objectiveLines[i].setCharacterSize(18);
		objectiveLines[i].setFillColor(Color::Black);
		objectiveLines[i].setString("Tipo " + to_string(i) + ":0/0");
		objectiveLines[i].setPosition(800.f - 180.f, 120.f + i * 30.f + 2.f);

		objectiveSwatches[i].setSize(Vector2f(18.f, 18.f));
		objectiveSwatches[i].setFillColor(Color(50 * (i + 1), 80 * (i + 1), 100));
		objectiveSwatches[i].setPosition(800.f - 210.f, 120.f + i * 30.f + 2.f);
		const string path = "imagenes/gem" + to_string(i) + ".png";
		if (gemIconTextures[i].loadFromFile(path)) {
			gemIconSprites[i].setTexture(gemIconTextures[i]);
			const float sx = 18.f / static_cast<float>(gemIconTextures[i].getSize().x);
			const float sy = 18.f / static_cast<float>(gemIconTextures[i].getSize().y);
			gemIconSprites[i].setScale(sx, sy);
			gemIconSprites[i].setPosition(800.f - 210.f, 120.f + i * 30.f + 2.f);
			gemIconLoaded[i] = true;
		}
		else {
			gemIconLoaded[i] = false;
		}
	}
}

void GameUI::setObjective(Objective* obj)
{
	levelObjective = obj;
	refreshObjectiveView();
}

void GameUI::setScoreMoves(int score, int moves)
{
	scoreAndMovesText.setString("Puntos: " + to_string(score) + " \n Movimientos: " + to_string(moves));

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
			if (gemIconLoaded[i]) {
				window.draw(gemIconSprites[i]);
			}
			else {
			window.draw(objectiveSwatches[i]);
			}
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

int GameUI::showStartScreen(RenderWindow& window)
{
	Text title = createText("Zombie match-3", *uiFont, 60, Color::White, { 220,100 });

	RectangleShape resetButton = createButton({ 260.f, 70.f }, { 270.f, 190.f }, Color(120, 160, 220));
	Text resetText = createText("BORRAR PROGRESO", *uiFont, 24, Color::Black, { 285.f, 212.f });

	RectangleShape playButton = createButton({ 200,80 }, { 300,300 }, Color(100, 200, 100));
	Text playText = createText("JUGAR", *uiFont, 40, Color::Black, { 345,310 });

	RectangleShape exitButton = createButton({ 200.f,80.f }, { 300.f,420.f }, Color(200,100,100));
	Text exitText = createText("SALIR", *uiFont, 40, Color::Black, { 360.f,440.f });
	
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}
			if (isButtonClicked(window, playButton, event)) {
				return 1;
			}
			if (isButtonClicked(window, exitButton, event)) {
				return 0;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) return -1;
			if (isButtonClicked(window, resetButton, event)) return -1;
		}
		window.clear(Color::Black);
		window.draw(title);
		window.draw(resetButton);
		window.draw(resetText);
		window.draw(playButton);
		window.draw(playText);
		window.draw(exitButton);
		window.draw(exitText);
		window.display();
	}
	return 0;
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
	return 0;
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

int GameUI::showLevelSelectScreen(RenderWindow& window, int totalLevels, int maxUnlocked, int completedMax)
{
	Text title = createText("Selecciona nivel", *uiFont, 48, Color::White, { 180.f, 60.f });

	RectangleShape backButton = createButton({ 160.f, 50.f }, { 20.f, 20.f }, Color(180, 100, 100));
	Text backText = createText("Volver", *uiFont, 22, Color::Black, { 60.f, 32.f });

	const int MAX_LEVELS = 10;
	RectangleShape buttons[MAX_LEVELS];
	Text labels[MAX_LEVELS];

	const int cols = 4;
	const float bx = 80.f, by = 140.f;
	const float bw = 140.f, bh = 70.f, pad = 18.f;

	if (totalLevels > MAX_LEVELS) totalLevels = MAX_LEVELS;

	for (int i = 0; i < totalLevels; ++i) {
		int ci = i % cols;
		int ri = i / cols;
		Vector2f pos = { bx + ci * (bw + pad), by + ri * (bh + pad) };

		bool completed = (i + 1 <= completedMax);
		bool unlocked = (i + 1 <= maxUnlocked);

		Color color;
		string tag;
		if (completed) { color = Color(120, 200, 120); tag = " (OK)"; }
		else if (unlocked) { color = Color(120, 160, 220); tag = ""; }
		else { color = Color(90, 90, 90); tag = " (LOCK)"; }

		buttons[i] = createButton({ bw, bh }, pos, color);
		labels[i] = createText("Nivel " + to_string(i + 1) + tag, *uiFont, 20, Color::Black, { pos.x + 18.f, pos.y + 22.f });
	}

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) { window.close(); return 0; }

			if (isButtonClicked(window, backButton, event)) {
				return -1;
			}

			for (int i = 0; i < totalLevels; ++i) {
				if (isButtonClicked(window, buttons[i], event)) {
					int levelIndex = i + 1;
					if (levelIndex <= maxUnlocked) return levelIndex;
				}
			}
		}

		window.clear(Color::Black);
		window.draw(title);
		window.draw(backButton);
		window.draw(backText);
		for (int i = 0; i < totalLevels; ++i) {
			window.draw(buttons[i]);
			window.draw(labels[i]);
		}
		window.display();
	}
	return 0;
}



bool GameUI::promptPlayersName(RenderWindow& window, string& outName, const string& defaultName)
{
	string current = defaultName;
	Text title = createText("Nombre para el ranking:", *uiFont, 28, Color::White, { 180.f, 180.f });
	Text input = createText(current, *uiFont, 28, Color::Yellow, { 180.f, 220.f });

	RectangleShape okButton = createButton({ 120.f, 50.f }, { 180.f, 280.f }, Color(100, 200, 100));
	Text okText = createText("OK", *uiFont, 22, Color::Black, { 220.f, 295.f });

	RectangleShape cancelButton = createButton({ 120.f, 50.f }, { 320.f, 280.f }, Color(200, 100, 100));
	Text cancelText = createText("Cancelar", *uiFont, 22, Color::Black, { 330.f, 295.f });

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) { window.close(); return false; }

			if (event.type == Event::TextEntered) {
				uint32_t ch = event.text.unicode;
				if (ch == 8) { // backspace
					if (!current.empty()) current.pop_back();
				}
				else if (ch == 13) { // Enter
					if (current.empty()) current = defaultName;
					outName = current;
					return true;
				}
				else if (ch >= 32 && ch < 127) { // ASCII visible básico
					if (current.size() < 20) current.push_back(static_cast<char>(ch));
				}
				input.setString(current);
			}

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				return false;
			}

			if (isButtonClicked(window, okButton, event)) {
				if (current.empty()) current = defaultName;
				outName = current;
				return true;
			}
			if (isButtonClicked(window, cancelButton, event)) return false;
		}

		window.clear(Color::Black);
		window.draw(title);
		window.draw(input);
		window.draw(okButton);
		window.draw(okText);
		window.draw(cancelButton);
		window.draw(cancelText);
		window.display();
	}
	return false;
}
