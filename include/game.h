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
        void processEvents();
        void update(float deltaTime);
        void render();
        // void spawnInimigos();
        // void handleCollisions();

        sf::RenderWindow window;
        Player player;
        Base base;
        list<Projetil> projeteis;
        std::vector<Inimigo> inimigos;
        float spawnTimer; // Temporizador para o surgimento dos inimigos
        const float spawnInterval;

    public:
        Game();
        void run();
};