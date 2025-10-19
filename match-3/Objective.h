#pragma once
#include <iostream>
class Objective
{
private:
	int targets[5];
	int progress[5];
public:
	Objective();
	void setTarget(int type, int amount);
	void addProgress(int type, int amount);
	int getTarget(int type)const;
	int getProgress(int tipe)const;
	bool isCompleted()const;
	void reset();
};

