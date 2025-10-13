#include "BoardRender.h"

using namespace std;

void BoardRender::loadTextures() {
	for (int i = 0; i < 5; i++) {
		string path = "imagenes/gem" + to_string(i) + ".png";
		if (!textures[i].loadFromFile(path)) {
			cout << "No se pudo cargar " << path << ", usando color sólido\n";
			Image img; img.create(64, 64, sf::Color(50 * (i + 1), 80 * (i + 1), 100));
			textures[i].loadFromImage(img);
		}
	}
}
void BoardRender::draw(RenderWindow& window, BoardLogic& logic) {
	for (int i = 0; i < logic.getHeight(); i++) {
		for (int j = 0; j < logic.getWitdht(); j++) {
			Gem* g = logic.get(j, i);
			int type = g->getType();
			if (type == -1)continue;
			Sprite sprite;
			sprite.setTexture(textures[type]);
			sprite.setPosition((float)g->getX(),(float)g->getY());
			window.draw(sprite);
		}
	}
}