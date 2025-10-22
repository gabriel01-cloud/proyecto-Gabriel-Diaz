#include "Objective.h"

Objective::Objective() { reset(); }

void Objective::setTarget(int type, int amount)
{
	if (type < 0 || type >= 5)return;
	if (amount < 0)amount = 0;
	targetCount[type] = amount;
}

void Objective::addProgress(int type, int amount)
{
	if (type < 0 || type >= 5)return;
	if (amount <= 0)return;
	progressCount[type] += amount;
}

int Objective::getTarget(int type) const
{
	if (type < 0 || type >= 5)return 0;
	return targetCount[type];
}

int Objective::getProgress(int type) const
{
	if (type < 0 || type >= 5) return 0;
	return progressCount[type];
}

bool Objective::isCompleted() const
{
	for (int i = 0; i < 5; i++) {
		if (targetCount[i] > 0 && progressCount[i] < targetCount[i])return false;
	}
	return true;
}

void Objective::reset()
{
	for (int i = 0; i < 5; i++) {
		targetCount[i] = 0; 
		progressCount[i] = 0;
	}
}
