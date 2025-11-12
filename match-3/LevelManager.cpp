#include "LevelManager.h"
#include <fstream>

LevelManager::LevelManager() { build(1); }
void LevelManager::reset() { build(1); }

bool LevelManager::advance() {
	if (currentLevel.index >= 3)return false;
	build(currentLevel.index + 1);
	return true;
}
void LevelManager::build(int index) {
	{
		ifstream file("niveles.xml");
		if (!file.is_open()) {
			cout << "no su pudo abrir niveles.xml, usando valores por defecto.\n";
		}
		else {
			auto getAttrInt = [](const string& ln, const string& key)->int {
				size_t p = ln.find(key + "=");
				if (p == string::npos)return 0;
				size_t s = ln.find("\"", p);
				if (s == string::npos)return 0;
				s += 1;
				size_t e = ln.find("\"", s);
				if (e == string::npos)return 0;
				return stoi(ln.substr(s, e - s));
			};

			string line;
			LevelDef def{};
			bool found = false;

			while (getline(file, line)) {
				if (line.find("<Level") == string::npos)continue;
				int idx = getAttrInt(line, "Index");
				if (idx != index) continue;
				def.index = idx;
				def.width = getAttrInt(line, "width");
				def.height = getAttrInt(line, "height");
				def.moves = getAttrInt(line, "moves");
				def.iceChancePercent = getAttrInt(line, "iceChancePercent");
				def.iceInitialCount = getAttrInt(line, "iceInitialCount");
				def.cascadeDampingPercent = getAttrInt(line, "cascadeDampingPercent");
				def.promoteRun4ChancePercent = getAttrInt(line, "promoteRun4ChancePercent");

				found = true;
				break;
			}
			if (found) {
				while (getline(file, line)) {
					if (line.find("<Targets") != string::npos) {
						def.targets[0] = getAttrInt(line, "t0");
						def.targets[1] = getAttrInt(line, "t1");
						def.targets[2] = getAttrInt(line, "t2");
						def.targets[3] = getAttrInt(line, "t3");
						def.targets[4] = getAttrInt(line, "t4");
					}
					if (line.find("</Level>") != string::npos)break;
				}
				currentLevel = def;
				cout << "[LevelManager] Loaded Level" << currentLevel.index;
				cout << " (" << currentLevel.width << "x" << currentLevel.height;
				cout << ", moves=" << currentLevel.moves << ") from XML\n";
				return; // éxito: no usamos el fallback
			}
			cout << "[LevelManager] niveles.xml no contiene el nivel "<< index << ", usando valores por defecto.\n";
		}
	}
	currentLevel = LevelDef{};
	currentLevel.index = index;
	if (index == 1) {
		currentLevel.width = 8;
		currentLevel.height = 8;
		currentLevel.moves = 10;
		currentLevel.targets[0] = 10;
		currentLevel.targets[3] = 8;
		currentLevel.iceChancePercent = 0;
		currentLevel.iceInitialCount = 0;
		currentLevel.cascadeDampingPercent = 30;
		currentLevel.promoteRun4ChancePercent = 5;

		cout << "[LevelManager] Loaded Level" << currentLevel.index;
		cout << " (" << currentLevel.width << "x" << currentLevel.height;
		cout << ", moves=" << currentLevel.moves << ")\n";
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

