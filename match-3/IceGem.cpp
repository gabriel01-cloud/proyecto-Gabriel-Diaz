#include "IceGem.h"

int IceGem::onMatch(BoardLogic& board)
{
    if (hits > 0) {
        hits--;
        markForClear();
        animClearing = false;
        marked = false;
        return 0;
    }
    markForClear();
    return 0;
}

