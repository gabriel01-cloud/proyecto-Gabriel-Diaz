#include "Board.h"
#include <iostream> 
using namespace std;
using namespace sf;
Board::Board(int w, int h) {
	width = w;
	height = h;
	grid = new Gem * *[height];
	for (int i = 0; i < height; i++) {
		grid[i] = new Gem * [width];
		for (int j = 0; j < width; j++) {
			int type = rand() % 5;
			grid[i][j] = new Gem(type, j * 64, i * 64);
		}
	}
	loadTextures();
	vector<Vector2i>matches = findMatches();
	while (!matches.empty()) {
		for (auto& cell : matches) {
			int newType = rand() % 5;
			grid[cell.y][cell.x]->setType(newType);
		}
		matches = findMatches();
	}
}
Board::~Board() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete grid[i][j];
		}
		delete[] grid[i];
	}
	delete[] grid;
}
void Board::loadTextures() {
	for (int i = 0; i < 5; i++) {
		string path = "imagenes/gem" + to_string(i) + ".png";
		if (!textures[i].loadFromFile(path)) {
			cout << "No se pudo cargar " << path << ", usando color sólido\n";
			Image img; img.create(64, 64, sf::Color(50 * (i + 1), 80 * (i + 1), 100));
			textures[i].loadFromImage(img);
		}
	}
}
void Board::draw(RenderWindow& window) {
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
void Board::refill() {
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
void Board::swapGems(sf::Vector2i a, sf::Vector2i b) {
	Gem* temp = grid[a.y][a.x];
	grid[a.y][a.x] = grid[b.y][b.x];
	grid[b.y][b.x] = temp;
	grid[a.y][a.x]->setTargetPosition(a.x * 64, a.y * 64);
	grid[b.y][b.x]->setTargetPosition(b.x * 64, b.y * 64);
}
vector<Vector2i> Board::findMatches() {
	vector<Vector2i>matches;
	for (int y = 0; y < height; y++) {
		int count = 1;
		for (int x = 1; x < width; x++) {
			int current = grid[y][x]->getType();
			int previous = grid[y][x - 1]->getType();
			if (current == previous && current != -1) {
				count++;
				continue;
			}
			if (count >= 3) {
				for (int k = 0; k < count; k++)
					matches.push_back({ x - 1 - k,y });
			}
			count = 1;
		}
		if (count >= 3) {
			for (int k = 0; k < count; k++)
				matches.push_back({ width - 1 - k,y });
		}
	}
	for (int x = 0; x < width; x++) {
		int count = 1;
		for (int y = 1; y < height; y++) {
			int current = grid[y][x]->getType();
			int previous = grid[y - 1][x]->getType();
			if (current == previous && current != -1) {
				count++;
				continue;
			}
			if (count >= 3) {
				for (int k = 0; k < count; k++)
					matches.push_back({ x,y - 1 - k });
			}
			count = 1;
		}
		if (count >= 3) {
			for (int k = 0; k < count; k++)
				matches.push_back({ x,height - 1 - k });
		}
	}
	return matches;
}
void Board::removeMatches(const vector<Vector2i>& matches) {
	for (auto& cell : matches) {
		grid[cell.y][cell.x]->setType(-1);
	}
}
void Board::dropGems() {
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

void Board::update() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j]->update();
		}
	}
}

bool Board::isMoving() {
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