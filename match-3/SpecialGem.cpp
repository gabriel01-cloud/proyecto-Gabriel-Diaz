#include "SpecialGem.h"
#include <iostream>
using namespace std;
int SpecialGem::onMatch(BoardLogic& board) {
	markForClear();
	if (special == BOMB) {
		cout << "Bomba activada!" << endl;
		return 1;
	}
	return 0;
}