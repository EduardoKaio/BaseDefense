#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <list>
#include "projetil.h"

using namespace std;
using namespace sf;


class Player : public Drawable {
    private:
        void handleInput(float deltaTime);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::Texture texture;
        sf::Sprite sprite;
        std::list<Projetil>& projeteis;
        bool shooting;
        float speed;
        bool isAlive;
        int health;
        int projeteisDisponiveis;
        
    
    public:
        Player(list<Projetil>& projeteis);
        sf::Sprite& getSprite();
        void update(float deltaTime);
        void shoot(sf::Vector2f target);
        int getHealth() const;
        void reduceHealth(int amount);
        int getProjeteisDisponiveis();

        bool isAliveStatus() const;
        void reset();
        FloatRect getGlobalBounds() const;
        void setSize(float scaleX, float scaleY);

};
#endif