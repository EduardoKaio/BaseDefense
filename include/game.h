#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "player.h"
#include "inimigo.h"
#include "projetil.h"
#include "base.h"
#include "projetil_inimigo.h"


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
        list<ProjetilInimigo> projeteisInimigos;
        std::vector<Inimigo> inimigos;
        float spawnTimer; // Temporizador para o surgimento dos inimigos
        const float spawnInterval;
        bool gameOver;
        Music backgroundMusic; 
        SoundBuffer heroShootBuffer;
        Sound heroShootSound;
        SoundBuffer enemyShootBuffer;
        Sound enemyShootSound;
        
    public:
        Game();
        void run();
};