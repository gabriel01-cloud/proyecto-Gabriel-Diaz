#include "Objective.h"

Objective::Objective() { reset(); }

void Objective::setTarget(int type, int amount)
{
	if (type < 0 || type >= 5)return;
	if (amount < 0)amount = 0;
	targets[type] = amount;
}

void Objective::addProgress(int type, int amount)
{
	if (type < 0 || type >= 5)return;
	if (amount <= 0)return;
	progress[type] += amount;
}

int Objective::getTarget(int type) const
{
	if (type < 0 || type >= 5)return 0;
	return targets[type];
}

int Objective::getProgress(int type) const
{
	if (type < 0 || type >= 5) return 0;
	return progress[type];
}

bool Objective::isCompleted() const
{
	for (int i = 0; i < 5; i++) {
		if (targets[i] > 0 && progress[i] < targets[i])return false;
	}
	return true;
}

void Objective::reset()
{
	for (int i = 0; i < 5; i++) {
		targets[i] = 0; 
		progress[i] = 0;
	}
}
