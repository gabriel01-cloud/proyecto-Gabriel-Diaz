#include <SFML/Graphics.hpp>
#include "Game.h"

<<<<<<< HEAD
int main() {
    srand(time(NULL));
    Game* game = new Game();
    game->run();
    delete game;
    return 0;
=======

int main() {
    try {
        srand(time(NULL));
        Game game;
        game.run();
        return 0;
    }
    catch (const exception& e) {
        cerr << "Fatal: " << e.what() << "\n";
        return 1;
    }
    catch(...){
        cout << "FATAL: error desconocido\n";
        return 1;
    }
>>>>>>> 2175d52 (Agregar archivos de proyecto.)
}
