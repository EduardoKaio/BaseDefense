#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "player.h"
#include "inimigo.h"
#include "projetil.h"
#include "base.h"
#include "projetil_inimigo.h"
#include <sstream> 


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
        list<Inimigo> inimigos;
        float spawnTimer; // Temporizador para o surgimento dos inimigos
        const float spawnInterval;
        bool gameOver;
        Music backgroundMusic; 
        SoundBuffer heroShootBuffer;
        Sound heroShootSound;
        SoundBuffer enemyShootBuffer;
        Sound enemyShootSound;
        bool gameStarted;
        void setupButton(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, const sf::Vector2f& position);
        void resetGame();
        void toggleAudio(bool enable);

        sf::RectangleShape startButton;
        sf::Text startButtonText;
        sf::RectangleShape restartButton;
        sf::Text restartButtonText;
        sf::RectangleShape backButton;
        sf::Text backButtonText;

        RectangleShape infoButton;
        Text infoButtonText;
        sf::Font font;
        std::vector<sf::RectangleShape> buttons;
        std::vector<sf::Text> buttonTexts;
        bool audioEnabled;
        bool victory; 
        float totalTime; // Tempo total em segundos
        float remainingTime; // Tempo restante em segundos
        sf::Text timerText;
        void resetTimer();
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        bool isShooting;
        Text titleText;
        bool infoScreenActive;
        
    public:
        Game();
        void run();
};