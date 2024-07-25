#include <SFML/Graphics.hpp>
#include <list>
#include "player.h"
#include "inimigo.h"
#include "projetil.h"
#include "base.h"

using namespace std;
using namespace sf;

class Game {
    private:
        RenderWindow window;
        Player player;
        Base base;
        list<Inimigo> inimigos;
        list<Projetil> projeteis;

        void processEvents();
        void update();
        void render();
        void spawnInimigos();
        void handleCollisions();

    public:
        Game();
        void run();
};