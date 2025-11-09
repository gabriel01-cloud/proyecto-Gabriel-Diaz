#pragma once
#include <iostream>
#include<string>

using namespace std;

struct LevelDef {
	int index = 1;
	int width = 8;
	int height = 8;
	int moves = 20;
	int targets[5] = { 0,0,0,0,0 };
	int iceChancePercent = 0;
	bool avoidRefillMatches = false;
	int cascadeDampingPercent = 0;
	int promoteRun4ChancePercent = 30;
	int iceInitialCount = 0;
};

class LevelManager
{
private:
	LevelDef currentLevel;
public:
	LevelManager();
	const LevelDef& current()const { return currentLevel; }
	int currentIndex()const { return currentLevel.index; }
	int total()const { return 3; }
	bool advance();
	void reset();
	string nextLevelLabel()const;
	void build(int index);
};

