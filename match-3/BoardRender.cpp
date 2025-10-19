#include "BoardRender.h"

using namespace std;

void BoardRender::loadTextures() {
	for (int i = 0; i < 5; i++) {
		string path = "imagenes/gem" + to_string(i) + ".png";
		if (!textures[i].loadFromFile(path)) {
			Image img; img.create(64, 64, Color(50 * (i + 1), 80 * (i + 1), 100));
			textures[i].loadFromImage(img);
		}
	}
	if (!textures[5].loadFromFile("imagenes/gem_bomb.png")) {
		sf::Image img; img.create(64, 64, Color(255, 100, 100));
		textures[5].loadFromImage(img);
	}
	if (!textures[5].loadFromFile("imagenes/gem_ice.png")) {
		Image img; img.create(64, 64, Color(120, 230, 255, 160));
		textures[6].loadFromImage(img);
	}
}
void BoardRender::draw(RenderWindow& window, BoardLogic& logic) {
	const int H = logic.getHeight();
	const int W = logic.getWidht();
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			Gem* g = logic.get(j, i);
			if (!g) continue;
			 const int type = g->getType();

			if (type<0||type>4)continue;
			Sprite sprite;
			if (dynamic_cast<BombGem*>(g)) {
				sprite.setTexture(textures[5]);
			}
			else {
				sprite.setTexture(textures[type]);
			}
			sprite.setPosition((float)g->getX(),(float)g->getY());
			window.draw(sprite);
			IceGem* ig = dynamic_cast<IceGem*>(g);
			if (!ig)continue;
			if (!ig->isFrozen())continue;
			Sprite overlay;
			overlay.setTexture(textures[6]);
			overlay.setPosition((float)g->getX(), (float)g->getY());
			window.draw(overlay);
		}
	}
}