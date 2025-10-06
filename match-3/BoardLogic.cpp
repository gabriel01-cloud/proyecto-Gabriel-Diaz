#include "BoardLogic.h"

BoardLogic::BoardLogic(int w, int h) : width(w), height(h) {
	srand(time(NULL));
	grid = new Gem * *[height];
	for (int i = 0; i < height; i++) {
		grid[i] = new Gem * [width];
		for (int j = 0; j < width; j++) {
			int type = rand() % 5;
			grid[i][j] = new SpecialGem(type, j * 64, i * 64);
			grid[i][j]->setGrid(j, i);
		}
	}
	Vector2i tmp[MAX_MATCHES];
	int count = findMatches(tmp, MAX_MATCHES);
	int tries = 0;
	while (count > 0 && tries++ < 50) {
		for (int i = 0; i < count; i++) {
			const int cx = tmp[i].x, cy = tmp[i].y;
			grid[cy][cx]->setType(rand() % 5);
		}
		count = findMatches(tmp, MAX_MATCHES);
	}
}
BoardLogic::~BoardLogic() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) delete grid[i][j];
		delete[] grid[i];
	}
	delete[] grid;
}
void BoardLogic::update() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j]->update();
		}
	}
}
void BoardLogic::swapGems(sf::Vector2i a, sf::Vector2i b) {
	Gem* temp = grid[a.y][a.x];
	grid[a.y][a.x] = grid[b.y][b.x];
	grid[b.y][b.x] = temp;
	grid[a.y][a.x]->setTargetPosition(a.x * 64, a.y * 64);
	grid[b.y][b.x]->setTargetPosition(b.x * 64, b.y * 64);
}
int BoardLogic::findMatches(Vector2i matches[], int maxMatches) {
	int count = 0;
	for (int y = 0; y < height; y++) {
		int run = 1;
		for (int x = 1; x < width; x++) {
			int current = grid[y][x]->getType();
			int previous = grid[y][x - 1]->getType();
			if (current == previous && current != -1) {
				run++;
				continue;
			}
			if (run >= 3) {
				for (int k = 0; k < run && count < maxMatches; k++)
					matches[count++] = Vector2i(x - 1 - k, y);
			}
			run = 1;
		}
		if (run >= 3) {
			for (int k = 0; k < run && count < maxMatches; k++)
				matches[count++] = Vector2i(width - 1 - k, y);
		}
	}
	for (int x = 0; x < width; x++) {
		int run = 1;
		for (int y = 1; y < height; y++) {
			int current = grid[y][x]->getType();
			int previous = grid[y - 1][x]->getType();
			if (current == previous && current != -1) {
				run++;
				continue;
			}
			if (run >= 3) {
				for (int k = 0; k < run && count < maxMatches; k++)
					matches[count++] = Vector2i(x, y - 1 - k);
			}
			run = 1;
		}
		if (run >= 3) {
			for (int k = 0; k < run && count < maxMatches; k++)
				matches[count++] = Vector2i(x, height - 1 - k);
		}
	}
	return count;
}
void BoardLogic::promoteIfRun4Plus(Vector2i matches[], int matchCount)
{
	if (matchCount < 4)return;
	const int c = matches[0].x, r = matches[0].y;
	SpecialGem* g = (SpecialGem*)grid[r][c];
	if (g)g->setSpecial(BOMB);
}
void BoardLogic::applyOnMatchAndExplosions(Vector2i matches[], int matchCount)
{
	for (int i = 0; i < matchCount; i++) {
		const int c = matches[i].x;
		const int r = matches[i].y;
		Gem* g = grid[r][c];
		if (!g)continue;

		const int radius = g->onMatch(*(Board*)this);
		if (radius <= 0)continue;
		int rStart = r - radius; if (rStart < 0)rStart = 0;
		int rEnd = r + radius; if (rEnd >= height)rEnd = height - 1;
		int cStart = c - radius; if (cStart < 0)cStart = 0;
		int cEnd = c + radius; if (cEnd >= width)cEnd = width - 1;
		for (int nr = rStart; nr <= rEnd; nr++) {
			for (int nc = cStart; nc <= cEnd; nc++) {
				grid[nr][nc]->markForClear();
			}
		}

	}
}
	void BoardLogic::removeMatches(Vector2i matches[], int matchCount)
	{
		for (int i = 0; i < matchCount;i++) {
			const int c = matches[i].x, r = matches[i].y;
			grid[r][c]->setType(-1);
			grid[r][c]->markForClear();
		}
	}

	void BoardLogic::dropGems() {
		for (int x = 0; x < width; x++) {
			for (int y = height - 1; y >= 0; y--) {
				if (grid[y][x]->getType() != -1) continue;

				int ny = y - 1;
				while (ny >= 0 && grid[ny][x]->getType() == -1) ny--;
				if (ny < 0) continue;

				grid[y][x]->setType(grid[ny][x]->getType());
				grid[y][x]->setPosition(grid[ny][x]->getX(), grid[ny][x]->getY());
				grid[y][x]->setTargetPosition(x * 64, y * 64);

				grid[ny][x]->setType(-1);
			}
		}
	}
	void BoardLogic::refill() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (grid[i][j]->getType() == -1) {
					int type = rand() % 5;
					grid[i][j]->setType(type);
					grid[i][j]->setPosition(j * 64, -64);
					grid[i][j]->setTargetPosition(j * 64, i * 64);
				}
			}
		}
	}
	bool BoardLogic::isMoving() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (grid[i][j]->getType() == -1) continue;
				if (grid[i][j]->getX() != j * 64 || grid[i][j]->getY() != i * 64) {
					return true;
				}
			}
		}
		return false;
	}
	void BoardLogic::loadTextures() {
		for (int i = 0; i < 5; i++) {
			string path = "imagenes/gem" + to_string(i) + ".png";
			if (!textures[i].loadFromFile(path)) {
				cout << "No se pudo cargar " << path << ", usando color sólido\n";
				Image img; img.create(64, 64, sf::Color(50 * (i + 1), 80 * (i + 1), 100));
				textures[i].loadFromImage(img);
			}
		}
	}
	void BoardLogic::draw(RenderWindow & window) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int type = grid[i][j]->getType();
				if (type == -1)continue;
				if (!textures[type].getSize().x)continue;
				Sprite sprite;
				sprite.setTexture(textures[type]);
				sprite.setPosition(grid[i][j]->getX(), grid[i][j]->getY());
				window.draw(sprite);
			}
		}
	}