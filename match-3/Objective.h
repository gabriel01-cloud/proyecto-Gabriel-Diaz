#pragma once
#include <iostream>
class Objective
{
private:
	int targetCount[5];
	int progressCount[5];
public:
	Objective();
	void setTarget(int type, int amount);
	void addProgress(int type, int amount);
	int getTarget(int type)const;
	int getProgress(int type)const;
	bool isCompleted()const;
	void reset();
};

