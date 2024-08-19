#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "player.h"
#include "inimigo.h"
#include "projetil.h"
#include "base.h"
#include "projetil_inimigo.h"
#include "texture_manager.h" 
#include "drops.h"
#include <sstream> 


using namespace std;
using namespace sf;

class Game {
    private:
        void processEvents();
        void update(float deltaTime);
        void render();
        void setupButton(RectangleShape& button, Text& buttonText, const string& text, const Vector2f& position);
        void resetGame();
        void toggleAudio(bool enable);

        RenderWindow window;
        Player player;
        Base base;
        list<Projetil> projeteis;
        list<ProjetilInimigo> projeteisInimigos;
        list<Inimigo> inimigos;
        list<Drops> activeDrops;
        float spawnTimer; // Temporizador para o surgimento dos inimigos
        float spawnInterval;
        bool gameOver;
        Music backgroundMusic; 
        SoundBuffer heroShootBuffer;
        Sound heroShootSound;
        SoundBuffer enemyShootBuffer;
        Sound enemyShootSound;
        bool gameStarted;
        RectangleShape startButton;
        Text startButtonText;
        RectangleShape restartButton;
        Text restartButtonText;
        RectangleShape backButton;
        Text backButtonText;
        RectangleShape infoButton;
        Text infoButtonText;
        Font font;
        vector<RectangleShape> buttons;
        vector<Text> buttonTexts;
        bool audioEnabled;
        bool victory; 
        float totalTime; // Tempo total em segundos
        float remainingTime; // Tempo restante em segundos
        Text timerText;
        void resetTimer();
        Texture backgroundTexture;
        Sprite backgroundSprite;
        bool isShooting;
        Text titleText;
        bool infoScreenActive;
        int killCount;
        TextureManager textureManager;
        float deltaTime;
        bool isPaused = false;
        Clock clock;
        
    public:
        Game();
        void run();
};