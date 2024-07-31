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

        std::list<Projetil>& projeteis;
        sf::CircleShape shape;
        bool shooting;
        float speed;
        int health;
        int projeteisDisponiveis;
    
    public:
        Player(list<Projetil>& projeteis);

        void update(float deltaTime);
        void shoot(sf::Vector2f target);
        int getHealth() const;
        void reduceHealth(int amount);
        int getProjeteisDisponiveis();
        CircleShape& getShape();

};
#endif