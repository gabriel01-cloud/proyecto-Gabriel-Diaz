#include "BoardLogic.h"
BoardLogic::BoardLogic(int w, int h, int icePtc, bool avoidRefill, int cascadeDampPtc, int promote4Ptc) {
	suppressPromoteNext = false;
	postExplosionPromotePercent = 0;
	boardHeight = h;
	boardWidth = w;
	gemGrid = nullptr;
	iceChancePercent = icePtc;
	avoidRefillMatches = avoidRefill;
	cascadeDampingPercent = cascadeDampPtc;
	promoteRun4ChancePercent = promote4Ptc;
	srand(time(NULL));
	gemGrid = new Gem * *[boardHeight];
	for (int i = 0; i < boardHeight; i++) {
		gemGrid[i] = new Gem * [boardWidth];
		for (int j = 0; j < boardWidth; j++) {
			int type = rand() % 5;
			bool makeIce = (iceChancePercent > 0) && ((rand() % 100) < iceChancePercent);
			if (makeIce) {
				gemGrid[i][j] = new IceGem(type, j * 64, i * 64);
			}
			else {
				gemGrid[i][j] = new NormalGem(type, j * 64, i * 64);
			}
			gemGrid[i][j]->setGrid(j, i);
		}
	}
	Vector2i tmp[MAX_MATCHES];
	int count = findMatches(tmp, MAX_MATCHES);
	int tries = 0;
	while (count > 0 && tries++ < 50) {
		for (int i = 0; i < count; i++) {
			const int cx = tmp[i].x, cy = tmp[i].y;
			gemGrid[cy][cx]->setType(rand() % 5);
		}
		count = findMatches(tmp, MAX_MATCHES);
	}
}

bool BoardLogic::wouldCreateImmediateMatch(int r, int c, int type) const
{
	if (c >= 2) {
		int type1 = gemGrid[r][c - 1]->getType();
		int type2 = gemGrid[r][c - 2]->getType();
		if (type1 == type && type2 == type)return true;
	}
	if (r >= 2) {
		int type1 = gemGrid[r - 1][c]->getType();
		int type2 = gemGrid[r - 2][c]->getType();
		if (type1 == type && type2 == type)return true;
	}
	return false;
}

int BoardLogic::pickRefillType(int r, int c)
{
	int type = rand() % 5;
	bool creates = wouldCreateImmediateMatch(r, c, type);
	if (!creates)return type;
	bool dampen = (cascadeDampingPercent > 0) && ((rand() % 100) < cascadeDampingPercent);
	if (!dampen)return type;
	for (int tries = 0; tries < 20; tries++) {
		int candidate = rand() % 5;
		if (!wouldCreateImmediateMatch(r, c, candidate)) {
			return candidate;
		}
	}
	return type;
}

void BoardLogic::placeGemRefill(int i, int j, int type)
{
	Gem* cell = gemGrid[i][j];
	if (cell && cell->getType() != -1)return;
	if (!cell) {
		gemGrid[i][j] = new NormalGem(type, j * 64, -64);
		gemGrid[i][j]->setGrid(j, i);
	}
	else {
		cell->setType(type);
		cell->setPosition(j * 64, -64);
		cell->setTargetPosition(j * 64, i * 64);
		cell->resetAlpha();
	}
	if (iceChancePercent > 0 && (rand() % 100) < iceChancePercent) {
		int px = gemGrid[i][j]->getX();
		int py = gemGrid[i][j]->getY();
		int curType = gemGrid[i][j]->getType();
		delete gemGrid[i][j];
		gemGrid[i][j] = new IceGem(curType, px, py);
		gemGrid[i][j]->setGrid(j, i);
	}
}
BoardLogic::~BoardLogic() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) delete gemGrid[i][j];
		delete[] gemGrid[i];
	}
	delete[] gemGrid;
}
void BoardLogic::applyInitialIce(int count)
{
	if (count <= 0) return;

	int total = boardWidth * boardHeight;
	if (count > total) count = total;

	int placed = 0;
	int tries = 0;
	const int maxTries = total * 6;

	while (placed < count && tries < maxTries) {
		int i = rand() % boardHeight;
		int j = rand() % boardWidth;

		Gem* g = gemGrid[i][j];
		if (!g) { tries++; continue; }

		if (dynamic_cast<IceGem*>(g)) { tries++; continue; }

		int t = g->getType();
		int px = g->getX();
		int py = g->getY();

		delete g;
		gemGrid[i][j] = new IceGem(t, px, py);
		gemGrid[i][j]->setGrid(j, i);

		placed++;
		tries++;
	}
	std::cout << "[BoardLogic] applyInitialIce: solicitadas=" << count
		<< " colocadas=" << placed << "\n";
}
void BoardLogic::setPostExplosionPromotePercent(int pct)
{
	if (pct < 0) pct = 0;
	if (pct > 100) pct = 100;
	postExplosionPromotePercent = pct;
}
bool BoardLogic::consumeLastSwapTriggeredBomb()
{
	bool v = lastSwapTriggeredBomb;
	lastSwapTriggeredBomb = false;
	return v;
}
void BoardLogic::update() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			gemGrid[i][j]->update();
		}
	}
}
void BoardLogic::swapGems(sf::Vector2i a, sf::Vector2i b) {
	Gem* temp = gemGrid[a.y][a.x];
	gemGrid[a.y][a.x] = gemGrid[b.y][b.x];
	gemGrid[b.y][b.x] = temp;
	gemGrid[a.y][a.x]->setGrid(a.x, a.y);
	gemGrid[b.y][b.x]->setGrid(b.x, b.y);
}
int BoardLogic::findMatches(Vector2i matchedCells[], int maxMatches) {
	int count = 0;
	for (int y = 0; y < boardHeight; y++) {
		int run = 1;
		for (int x = 1; x < boardWidth; x++) {
			int current = gemGrid[y][x]->getType();
			int previous = gemGrid[y][x - 1]->getType();
			if (current == previous && current != -1) {
				run++;
				continue;
			}
			if (run >= 3) {
				for (int k = 0; k < run && count < maxMatches; k++)
					matchedCells[count++] = Vector2i(x - 1 - k, y);
			}
			run = 1;
		}
		if (run >= 3) {
			for (int k = 0; k < run && count < maxMatches; k++)
				matchedCells[count++] = Vector2i(boardWidth - 1 - k, y);
		}
	}
	for (int x = 0; x < boardWidth; x++) {
		int run = 1;
		for (int y = 1; y < boardHeight; y++) {
			int current = gemGrid[y][x]->getType();
			int previous = gemGrid[y - 1][x]->getType();
			if (current == previous && current != -1) {
				run++;
				continue;
			}
			if (run >= 3) {
				for (int k = 0; k < run && count < maxMatches; k++)
					matchedCells[count++] = Vector2i(x, y - 1 - k);
			}
			run = 1;
		}
		if (run >= 3) {
			for (int k = 0; k < run && count < maxMatches; k++)
				matchedCells[count++] = Vector2i(x, boardHeight - 1 - k);
		}
	}
	return count;
}
void BoardLogic::suppressNextPromotion() {
	suppressPromoteNext = true;
}
void BoardLogic::promoteRunOfFourOrMore(sf::Vector2i matchedCells[], int matchCount) {
	if (suppressPromoteNext) {
		suppressPromoteNext = false;
		return;
	}

	if (matchCount < 4) return;

	const int c = matchedCells[0].x;
	const int r = matchedCells[0].y;
	Gem* current = gemGrid[r][c];
	if (!current) return;
	if (dynamic_cast<BombGem*>(current)) return; 

	const int t = current->getType();
	const int px = current->getX();
	const int py = current->getY();

	delete current;
	gemGrid[r][c] = new BombGem(t, px, py);
	gemGrid[r][c]->setGrid(c, r);
	gemGrid[r][c]->setJustPromoted(true);
}
void BoardLogic::applyMatchEffectsAndExplosions(sf::Vector2i matchedCells[], int matchCount) {
	using sf::Vector2i;

	Vector2i pending[MAX_MATCHES * 8];
	int head = 0, tail = 0;
	for (int i = 0; i < matchCount && i < MAX_MATCHES * 8; ++i) pending[tail++] = matchedCells[i];

	Vector2i affected[MAX_MATCHES * 8];
	int affectedCount = 0;

	auto pushAffected = [&](int x, int y) {
		if (affectedCount < MAX_MATCHES * 8) affected[affectedCount++] = Vector2i(x, y);
		};

	auto queueIfNotQueued = [&](const Vector2i& pos) {
		for (int k = head; k < tail; ++k) if (pending[k].x == pos.x && pending[k].y == pos.y) return false;
		if (tail < MAX_MATCHES * 8) { pending[tail++] = pos; return true; }
		return false;
		};

	auto markClear = [&](Gem* g, int x, int y) {
		if (!g) return;
		g->markForClear();
		if (g->getType() != -1) g->setType(-1);
		pushAffected(x, y);
		};

	auto hitIce = [&](IceGem* ice, Gem* g, int x, int y) {
		ice->onMatch(*this);
		if (!ice->isFrozen()) {
			markClear(g, x, y);
		}
		else {
			if (affectedCount < MAX_MATCHES) affected[affectedCount++] = Vector2i(x, y);
		}
		};

	auto affectNeighbor = [&](int x, int y) {
		if (!inBounds({ x, y })) return;

		Gem* eg = gemGrid[y][x];
		if (!eg) return;

		if (dynamic_cast<BombGem*>(eg)) { 
			suppressPromoteNext = true;
			queueIfNotQueued({ x, y });
			return;
		}

		if (IceGem* iceEg = dynamic_cast<IceGem*>(eg)) {
			hitIce(iceEg, eg, x, y);
			return;
		}

		markClear(eg, x, y);
		};

	while (head < tail) {
		const int c = pending[head].x;
		const int r = pending[head].y;
		++head;

		if (!inBounds({ c, r })) continue;
		Gem* g = gemGrid[r][c];
		if (!g) continue;

		if (dynamic_cast<BombGem*>(g) && g->wasJustPromoted()) {
			g->clearJustPromoted();
			continue;
		}

		if (IceGem* ice = dynamic_cast<IceGem*>(g)) {
			hitIce(ice, g, c, r);
			continue;
		}

		const int radius = g->onMatch(*this);
		markClear(g, c, r);
		if (radius <= 0) continue;

		suppressPromoteNext = true;

		if (dynamic_cast<BombGem*>(g)) {
			for (int dy = -1; dy <= 1; ++dy)
				for (int dx = -1; dx <= 1; ++dx)
					if (dx != 0 || dy != 0) affectNeighbor(c + dx, r + dy);
			continue;
		}

		const int rStart = (r - radius < 0) ? 0 : r - radius;
		const int rEnd = (r + radius >= boardHeight) ? boardHeight - 1 : r + radius;
		const int cStart = (c - radius < 0) ? 0 : c - radius;
		const int cEnd = (c + radius >= boardWidth) ? boardWidth - 1 : c + radius;

		for (int rr = rStart; rr <= rEnd; ++rr)
			for (int cc = cStart; cc <= cEnd; ++cc)
				affectNeighbor(cc, rr);
	}

	weakenAdjacentIceGems(affected, affectedCount);
}


void BoardLogic::removeMatchedCells(sf::Vector2i matchedCells[], int count)
{
	for (int i = 0; i < count; ++i) {
		const int c = matchedCells[i].x;
		const int r = matchedCells[i].y;
		Gem* g = gemGrid[r][c];
		if (!g) continue;
		if (dynamic_cast<BombGem*>(g) && g->wasJustPromoted()) {
			g->clearJustPromoted();
			continue;
		}
		g->setType(-1);
		g->markForClear();
	}
}

void BoardLogic::dropGems() {
	for (int x = 0; x < boardWidth; x++) {
		for (int y = boardHeight - 1; y >= 0; y--) {
			if (gemGrid[y][x]->getType() != -1) continue;

			int ny = y - 1;
			while (ny >= 0 && gemGrid[ny][x]->getType() == -1) ny--;
			if (ny < 0) continue;
			Gem* tmp = gemGrid[y][x];
			gemGrid[y][x] = gemGrid[ny][x];
			gemGrid[ny][x] = tmp;
			gemGrid[y][x]->setGrid(x, y);
			gemGrid[ny][x]->setGrid(x, ny);
		}
	}
}
void BoardLogic::refill() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			if (gemGrid[i][j]->getType() == -1) {
				const int type = pickRefillType(i, j);
				placeGemRefill(i, j, type);
			}
		}
	}
}
bool BoardLogic::isMoving() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			if (!gemGrid[i][j]->isIdle())return true;
		}
	}
	return false;
}
<<<<<<< HEAD
=======
Gem* BoardLogic::get(int c, int r)
{
	if (r < 0 || r >= boardHeight || c < 0 || c >= boardWidth)
		throw out_of_range("BoardLogic::get fuera de rango");
	return gemGrid[r][c];
}
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
bool BoardLogic::attemptSwapAndResolve(Vector2i a, Vector2i b)
{
	if (abs(a.x - b.x) + abs(a.y - b.y) != 1) return false;

	Gem* ga0 = gemGrid[a.y][a.x];
	Gem* gb0 = gemGrid[b.y][b.x];
	if (ga0) {
		if (IceGem* ia = dynamic_cast<IceGem*>(ga0)) {
			if (ia->isFrozen()) return false; 
		}
	}
	if (gb0) {
		if (IceGem* ib = dynamic_cast<IceGem*>(gb0)) {
			if (ib->isFrozen()) return false;
		}
	}
	swapGems(a, b);
	Gem* ga = gemGrid[a.y][a.x];
	Gem* gb = gemGrid[b.y][b.x];
	bool aIsBomb = (ga && dynamic_cast<BombGem*>(ga));
	bool bIsBomb = (gb && dynamic_cast<BombGem*>(gb));
	bool aIsIce = (ga && dynamic_cast<IceGem*>(ga));
	bool bIsIce = (gb && dynamic_cast<IceGem*>(gb));

	if ((aIsBomb && !bIsIce) || (bIsBomb && !aIsIce)) {
		Vector2i centers[2];
		int n = 0;
		if (aIsBomb && !bIsIce)centers[n++] = a;
		if (bIsBomb && !aIsIce)centers[n++] = b;
		applyMatchEffectsAndExplosions(centers, n);
		lastSwapTriggeredBomb = true;
		return true;
	}

	Vector2i tmp[MAX_MATCHES];
	int count = findMatches(tmp, MAX_MATCHES);
	if (count <= 0) {
		swapGems(a, b);
		return false;
	}
	return true;
}

void BoardLogic::weakenAdjacentIceGems(const Vector2i affected[], int count)
{
	static const int DX[4] = { 1,-1,0,0 };
	static const int DY[4] = { 0,0,1,-1 };
	for (int i = 0; i < count; i++) {
		Vector2i p = affected[i];
		for (int k = 0; k < 4; k++) {
			Vector2i q{ p.x + DX[k],p.y + DY[k] };
			if (!inBounds(q))continue;
			Gem* g = gemGrid[q.y][q.x];
			if (!g)continue;
			if (dynamic_cast<IceGem*>(g)) {
				g->onMatch(*this);
			}
		}
	}
}
