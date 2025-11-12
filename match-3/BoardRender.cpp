#include "BoardRender.h"
#include "BombGem.h"
#include "IceGem.h"
<<<<<<< HEAD
=======
#include <string>

>>>>>>> 2175d52 (Agregar archivos de proyecto.)
using namespace std;

void BoardRender::loadTextures() {
	for (int i = 0; i < 5; i++) {
		string path = "imagenes/gem" + to_string(i) + ".png";
		if (!gemTextures[i].loadFromFile(path)) {
			Image img;
			unsigned r = 50u * (i + 1); if (r > 255u) r = 255u;
			unsigned g = 80u * (i + 1); if (g > 255u) g = 255u;
			img.create(64, 64, Color(r, g, 100));
			gemTextures[i].loadFromImage(img);
		}
	}
	if (!gemTextures[5].loadFromFile("imagenes/gem_bomb.png")) {
		Image img; img.create(64, 64, Color(255, 100, 100));
		gemTextures[5].loadFromImage(img);
	}
<<<<<<< HEAD
	if (!gemTextures[6].loadFromFile("imagenes/gem_ice.png")) {
=======
	if (!gemTextures[6].loadFromFile("imagenes/gemice.png")) {
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
		Image img; img.create(64, 64, Color(120, 230, 255, 160));
		gemTextures[6].loadFromImage(img);
	}
}
void BoardRender::draw(RenderWindow& window, BoardLogic& boardLogic) {
    const int H = boardLogic.getHeight();
<<<<<<< HEAD
    const int W = boardLogic.getWidht();
=======
    const int W = boardLogic.getWidth();
>>>>>>> 2175d52 (Agregar archivos de proyecto.)

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            Gem* g = boardLogic.get(j, i);
            if (!g) continue;

            const int type = g->getType();
            if (type == -1) continue;

            int texIndex = -1;
            if (dynamic_cast<BombGem*>(g)) {
                texIndex = 5;
            }
            else if (type >= 0 && type <= 4) {
                texIndex = type;
            }
            else {
                continue;
            }

            Sprite sprite;
            sprite.setTexture(gemTextures[texIndex]);
            sprite.setPosition((float)g->getX(), (float)g->getY());
            sprite.setColor(Color(255, 255, 255, static_cast<Uint8>(g->getAlpha())));
            window.draw(sprite);

            IceGem* ice = dynamic_cast<IceGem*>(g);
            if (ice && ice->isFrozen()) {
                Sprite overlay;
                overlay.setTexture(gemTextures[6]);
                overlay.setPosition((float)g->getX(), (float)g->getY());
                window.draw(overlay);
            }
        }
    }
}

