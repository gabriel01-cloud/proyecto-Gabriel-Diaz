#include "LevelManager.h"

LevelManager::LevelManager() { build(1); }
void LevelManager::reset() { build(1); }

bool LevelManager::advance() {
	if (currentLevel.index >= 3)return false;
	build(currentLevel.index + 1);
	return true;
}
void LevelManager::build(int index) {
	currentLevel = LevelDef{};
	currentLevel.index = index;
	if (index == 1) {
		currentLevel.width = 8;
		currentLevel.height = 8;
		currentLevel.moves = 20;
		currentLevel.targets[0] = 10;
		currentLevel.targets[3] = 8;
		currentLevel.iceChancePercent = 0;
		currentLevel.iceInitialCount = 0;
		currentLevel.cascadeDampingPercent = 50;
		currentLevel.promoteRun4ChancePercent = 40;

		cout << "[LevelManager] Loaded Level" << currentLevel.index;
		cout <<" ("<< currentLevel.width << "x" << currentLevel.height;
		cout << ", moves=" << currentLevel.moves<<")\n";
		return;
	}
	if (index == 2) {
		currentLevel.width = 8;
		currentLevel.height = 8;
		currentLevel.moves = 25;
		currentLevel.targets[2] = 12;
		currentLevel.iceChancePercent = 0;
		currentLevel.iceInitialCount = 10;
		currentLevel.cascadeDampingPercent = 25;
		currentLevel.promoteRun4ChancePercent = 40;  
		currentLevel.promoteRun4ChancePercent = 80;
		cout << "[LevelManager] Loaded Level" << currentLevel.index;
		cout << " (" << currentLevel.width << "x" << currentLevel.height;
		cout << ", moves=" << currentLevel.moves << ")\n";
		return;
	}
	if (index == 3) {
		currentLevel.width = 9;
		currentLevel.height = 9;
		currentLevel.moves = 25;
		currentLevel.targets[2] = 12;
		currentLevel.targets[0] = 8;
		currentLevel.iceChancePercent = 15;
		currentLevel.iceInitialCount = 12;
		currentLevel.cascadeDampingPercent = 15;
		currentLevel.promoteRun4ChancePercent = 60;
		cout << "[LevelManager] Loaded Level" << currentLevel.index;
		cout << " (" << currentLevel.width << "x" << currentLevel.height;
		cout << ", moves=" << currentLevel.moves << ")\n";
		return;
	}

	currentLevel.width = 8;
	currentLevel.height = 8;
	currentLevel.moves = 15;
	currentLevel.targets[0] = 5;
	currentLevel.iceChancePercent = 15;
	currentLevel.iceInitialCount = 5;
	currentLevel.cascadeDampingPercent = 40;
	currentLevel.promoteRun4ChancePercent = 50;
	cout << "[LevelManager] Loaded Level" << currentLevel.index;
	cout << "  Width: " << currentLevel.width;
	cout << "  Height: " << currentLevel.height;
	cout << "  Moves: " << currentLevel.moves;
}
string LevelManager::nextLevelLabel()const {
	int next = (currentLevel.index < 3) ? (currentLevel.index + 1) : 1;
	return "Play Next Level(Level " + to_string(next) + ")";
}

