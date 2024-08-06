#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
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

    public:
        Inimigo(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::RenderWindow* window);

        void update(float deltaTime, const Vector2f& playerPosition);
        void fire(const sf::Vector2f& playerPosition);
        bool isOutOfWindow(const sf::RenderWindow& window) const;
        void updateDirection(const sf::Vector2f& playerPosition);

        std::vector<ProjetilInimigo>& getProjeteis();
        const std::vector<ProjetilInimigo>& getProjeteis() const;
        CircleShape& getShape();
        void reduceHealth();
        bool isAliveStatus() const;
};

#endif
