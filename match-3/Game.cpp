#include "Game.h"
#include "Gem.h"
<<<<<<< HEAD

Game::Game(): boardLogic(nullptr), playerScore(0),remainingMoves(0) {
	gameWindow = new RenderWindow(VideoMode(800, 600), "Match-3", Style::Close);
	
=======
#include "ProgressManager.h"

Game::Game() : boardLogic(nullptr), playerScore(0), remainingMoves(0) {
	ProgressManager progress;
	progress.ensureFileExists();

	int maxUnlocked = progress.loadMaxUnlocked();
	gameWindow = make_unique<RenderWindow>(VideoMode(800, 600), "Match-3", Style::Close);

>>>>>>> 2175d52 (Agregar archivos de proyecto.)
	boardRenderer.loadTextures();

	if (!uiFontAsset.loadFromFile("imagenes/arial.ttf")) {
		cout << "No se pudo cargar la fuente\n";
	}
	if (!backgroundTexture.loadFromFile("imagenes/fondo.png"))
		cout << "No se pudo abrir fondo";
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(800.0f / backgroundTexture.getSize().x, 600.0f / backgroundTexture.getSize().y);
<<<<<<< HEAD
	
	Gem::setAnimationSpeeds(3, 8);
=======

	Gem::setAnimationSpeeds(1, 2);
>>>>>>> 2175d52 (Agregar archivos de proyecto.)

	isFirstCellSelected = false;
	selectedCell = { -1,-1 };
	gameUI.init(&uiFontAsset);
	gameUI.setObjective(&levelObjective);
<<<<<<< HEAD
	loadCurrentLevel();
}

Game::~Game() {
	delete boardLogic;
	delete gameWindow;
}
void Game::loadCurrentLevel() {
	const LevelDef& L = levelManager.current();
	if (boardLogic)delete boardLogic;
	boardLogic = new BoardLogic(
=======
	levelManager.build(maxUnlocked);
}

void Game::loadCurrentLevel() {
	const LevelDef& L = levelManager.current();
	boardLogic = make_unique<BoardLogic>(
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
		L.width, L.height,
		L.iceChancePercent,
		L.avoidRefillMatches,
		L.cascadeDampingPercent,
		L.promoteRun4ChancePercent
	);
	if (L.iceInitialCount > 0) {
		boardLogic->applyInitialIce(L.iceInitialCount);
	}
	playerScore = 0;
	remainingMoves = L.moves;
	levelObjective.reset();
	for (int i = 0; i < 5; i++) {
		if (L.targets[i] > 0) {
			levelObjective.setTarget(i, L.targets[i]);
		}
	}
	gameUI.refreshObjectiveView();
<<<<<<< HEAD
	gameUI.setScoreMoves(playerScore,remainingMoves);
}
void Game::run() {
	if (!gameUI.showStartScreen(*gameWindow))return;
=======
	gameUI.setScoreMoves(playerScore, remainingMoves);
}
void Game::run() {
	int choice = gameUI.showStartScreen(*gameWindow);
	if (choice == 0)return;
	if (choice == -1) {
		resetAllGameData();
		choice = gameUI.showStartScreen(*gameWindow);
		if (choice == 0)return;
		if (choice == -1) { resetAllGameData(); return; }
	}
	while (true) {
		ProgressManager progress;
		int maxUnlocked = progress.loadMaxUnlocked();
		int totalLevels = levelManager.total();
		int completedMax = (maxUnlocked > 0) ? (maxUnlocked - 1) : 0;

		int chosen = gameUI.showLevelSelectScreen(*gameWindow, totalLevels, maxUnlocked, completedMax);
		if (chosen == -1) {

			choice = gameUI.showStartScreen(*gameWindow);
			if (choice == 0) return;
			if (choice == -1) { resetAllGameData(); }
			continue;
		}
		if (chosen <= 0) return;
		levelManager.build(chosen);
		break;
	}

	loadCurrentLevel();
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
	while (gameWindow->isOpen()) {
		processEvents();
		update();
		render();
	}
}

<<<<<<< HEAD
=======
void Game::resetAllGameData()
{
	ProgressManager pm;
	pm.saveMaxUnlocked(1);
	ofstream("ranking.txt", std::ios::trunc).close();

	levelManager.reset();
	loadCurrentLevel();
	playerScore = 0;
	cout << "Todo el progreso y ranking fueron borrados.Nivel actual = " << levelManager.currentIndex() << "\n";
}

>>>>>>> 2175d52 (Agregar archivos de proyecto.)
void Game::handleClick(Vector2i cell) {
	if (!isFirstCellSelected) {
		isFirstCellSelected = true;
		selectedCell = cell;
		return;
	}
	int dx = abs(selectedCell.x - cell.x);
	int dy = abs(selectedCell.y - cell.y);
	if (dx + dy != 1) {
		cout << " No son adyacentes\n";
		isFirstCellSelected = false;
		return;
	}
<<<<<<< HEAD
	bool ok= boardLogic->attemptSwapAndResolve(selectedCell, cell);
=======
	bool ok = boardLogic->attemptSwapAndResolve(selectedCell, cell);
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
	if (!ok) {
		cout << "Swap revertido: no se genero combinacion\n";
		isFirstCellSelected = false;
		return;
	}
	resolveAllMatches();
	isFirstCellSelected = false;
}
void Game::processEvents() {
	Event event;
	while (gameWindow->pollEvent(event)) {
		if (event.type == Event::Closed) gameWindow->close();

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			if (boardLogic->isMoving())continue;
			Vector2i mousePos = Mouse::getPosition(*gameWindow);
			int col = mousePos.x / 64;
			int row = mousePos.y / 64;

<<<<<<< HEAD
			if (col >= 0 && col < boardLogic->getWidht() && row >= 0 && row < boardLogic->getHeight()) {
=======
			if (col >= 0 && col < boardLogic->getWidth() && row >= 0 && row < boardLogic->getHeight()) {
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
				handleClick({ col,row });
			}
		}
	}
}

void Game::update() {
<<<<<<< HEAD
	gameUI.setScoreMoves(playerScore, remainingMoves);
	if(levelObjective.isCompleted()) {
		bool hasNext = levelManager.currentIndex() < levelManager.total();
		int choice = gameUI.showResultScreen(*gameWindow,true, playerScore,levelManager.currentIndex(),hasNext);
		if (choice == 1&&hasNext) {
=======

	gameUI.setScoreMoves(playerScore, remainingMoves);
	if (levelObjective.isCompleted()) {
		ProgressManager progress;
		int current = levelManager.currentIndex();
		int unlocked = progress.loadMaxUnlocked();
		int next = min(current + 1, levelManager.total());
		int newMax = max(unlocked, next);
		progress.saveMaxUnlocked(newMax);

		bool hasNext = (levelManager.currentIndex() < levelManager.total());
		int choice = gameUI.showResultScreen(*gameWindow, true, playerScore, levelManager.currentIndex(), hasNext);
		{
			RankingManager ranking;
			ranking.addEntry("Player", playerScore);
		}
		if (choice == 1 && hasNext) {
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
			levelManager.advance();
			loadCurrentLevel();
			return;
		}
<<<<<<< HEAD
		if(choice==0){
			if (!gameUI.showStartScreen(*gameWindow)) {
				gameWindow->close(); return;
			}
			loadCurrentLevel();
			return;
		}
		if (choice == 2) {
=======
		if (choice == 2) {
			loadCurrentLevel();
			return;
		}
		if (choice == 0) {
			int menu = gameUI.showStartScreen(*gameWindow);
			if (menu == 0) { gameWindow->close(); return; }
			if (menu == -1) { resetAllGameData(); return; }
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
			loadCurrentLevel();
			return;
		}
		gameWindow->close();
		return;
	}
	if (remainingMoves <= 0) {
		bool hasNext = false;
		int choice = gameUI.showResultScreen(*gameWindow, false, playerScore, levelManager.currentIndex(), hasNext);
<<<<<<< HEAD
		if (choice == 0) {
			if (!gameUI.showStartScreen(*gameWindow)) {
				gameWindow->close();
=======
		{
			RankingManager ranking;
			ranking.addEntry("Player", playerScore);
		}
		if (choice == 2) {
			loadCurrentLevel();
			return;
		}
		if (choice == 0) {
			int menu = gameUI.showStartScreen(*gameWindow);
			if (menu == 0) { gameWindow->close(); return; }
			if (menu == -1) {
				resetAllGameData();
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
				return;
			}
			loadCurrentLevel();
			return;
		}
<<<<<<< HEAD
=======

>>>>>>> 2175d52 (Agregar archivos de proyecto.)
		gameWindow->close();
		return;
	}
}

void Game::render() {
	gameWindow->clear();
	gameWindow->draw(backgroundSprite);
	boardRenderer.draw(*gameWindow, *boardLogic);
	if (isFirstCellSelected) {
		RectangleShape outline(Vector2f(64, 64));
		outline.setPosition(selectedCell.x * 64, selectedCell.y * 64);
		outline.setFillColor(Color::Transparent);
		outline.setOutlineColor(Color::Red);
		outline.setOutlineThickness(3);
		gameWindow->draw(outline);
	}
	gameUI.draw(*gameWindow);
	gameWindow->display();
}

void Game::resolveAllMatches() {
	bool bombSwap = boardLogic->consumeLastSwapTriggeredBomb();

	if (bombSwap) {
		boardLogic->suppressNextPromotion();
	}

	sf::Vector2i matched[MAX_MATCHES];
	int count = boardLogic->findMatches(matched, MAX_MATCHES);

	bool validMove = bombSwap || (count > 0);
	if (validMove) {
		remainingMoves--;
		gameUI.setScoreMoves(playerScore, remainingMoves);
	}

	if (bombSwap) {
		render();

		boardLogic->dropGems();
		while (boardLogic->isMoving() && gameWindow->isOpen()) {
			boardLogic->update();
			render();
		}

		boardLogic->refill();
		while (boardLogic->isMoving() && gameWindow->isOpen()) {
			boardLogic->update();
			render();
		}

		count = boardLogic->findMatches(matched, MAX_MATCHES);
	}

	while (count > 0) {
		if (count >= 4) boardLogic->promoteRunOfFourOrMore(matched, count);

		for (int i = 0; i < count; i++) {
			int cx = matched[i].x, cy = matched[i].y;
			int type = boardLogic->get(cx, cy)->getType();
			if (type >= 0 && type < 5) levelObjective.addProgress(type, 1);
		}
		gameUI.refreshObjectiveView();

		boardLogic->applyMatchEffectsAndExplosions(matched, count);
		boardLogic->removeMatchedCells(matched, count);
		playerScore += count * 10;

		render();
		boardLogic->dropGems();
		while (boardLogic->isMoving() && gameWindow->isOpen()) {
			boardLogic->update();
			render();
		}

		boardLogic->refill();
		while (boardLogic->isMoving() && gameWindow->isOpen()) {
			boardLogic->update();
			render();
		}

		count = boardLogic->findMatches(matched, MAX_MATCHES);
	}
}
