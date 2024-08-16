#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "projetil_inimigo.h"
#include "inimigo.h"

class Base : public sf::Drawable {

    private:
        int health;
        // sf::RectangleShape shape;
        sf::Sprite sprite; // Mude de RectangleShape para Sprite
        sf::Texture texture;
        sf::RectangleShape lifeBar;
        sf::Font font;
        sf::Text lossText;
        bool showLossText;
        std::string lossString;
        sf::Clock lossClock; 
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    public:
        Base();

        void update(list<ProjetilInimigo>& projeteis, list<Inimigo>& inimigos);
        int getHealth() const;
        bool isAliveStatus() const;
        void reduceHealth(int reduce);
        void setPosition(const sf::Vector2f &position);
        // sf::RectangleShape getShape() const;
        sf::Sprite& getSprite(); 
        void reset();
        sf::FloatRect getGlobalBounds() const;

};

#endif // BASE_H