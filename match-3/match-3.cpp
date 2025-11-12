#include <SFML/Graphics.hpp>
#include "Game.h"


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
}
