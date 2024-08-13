#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "projetil_inimigo.h"
#include "inimigo.h"

class Base : public sf::Drawable {

    private:
        int health;
        sf::RectangleShape shape;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    public:
        Base();

        void update(list<ProjetilInimigo>& projeteis, list<Inimigo>& inimigos);
        int getHealth() const;
        bool isAliveStatus() const;
        int reduceHealth(int reduce);
        void setPosition(const sf::Vector2f &position);
        sf::RectangleShape getShape() const;
        void reset();

};

#endif // BASE_H