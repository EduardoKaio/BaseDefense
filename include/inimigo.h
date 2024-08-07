#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "projetil_inimigo.h" 

using namespace std;
using namespace sf;

class Inimigo : public Drawable{
 
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        Vector2f position;
        CircleShape shape;
        Vector2f direction;
        int health;
        bool isAlive;
        float speed;
        std::vector<ProjetilInimigo> projeteis;
        float fireRate; // Tempo entre disparos
        float fireTimer;
        const sf::RenderWindow* window;
        sf::SoundBuffer enemyShootBuffer; // Buffer para o som
        sf::Sound enemyShootSound;


    public:
        Inimigo(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::RenderWindow* window);

        void update(float deltaTime, const Vector2f& playerPosition, bool audioEnabled);
        void fire(const sf::Vector2f& playerPosition, bool audioEnabled);
        bool isOutOfWindow(const sf::RenderWindow& window) const;
        void updateDirection(const sf::Vector2f& playerPosition);

        std::vector<ProjetilInimigo>& getProjeteis();
        const std::vector<ProjetilInimigo>& getProjeteis() const;
        CircleShape getShape() const;
        void reduceHealth();
        bool isAliveStatus() const;
        void loadEnemyShootSound(const std::string& filepath); 
        bool iscolliding(float x, float y, float radius) const;
    
};

#endif
