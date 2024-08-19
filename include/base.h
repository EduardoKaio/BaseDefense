#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "projetil_inimigo.h"
#include "inimigo.h"

using namespace std;
using namespace sf;

class Base : public Drawable {

    private:
        int health;
        Sprite sprite; // Mude de RectangleShape para Sprite
        Texture texture;
        RectangleShape lifeBar;
        Font font;
        Text lossText;
        bool showLossText;
        string lossString;
        Clock lossClock; 
        void draw(RenderTarget& target, RenderStates states) const override;
    
    public:
        Base();

        void update(list<ProjetilInimigo>& projeteis, list<Inimigo>& inimigos);
        int getHealth() const;
        bool isAliveStatus() const;
        void reduceHealth(int reduce);
        void setPosition(const Vector2f &position);
        Sprite& getSprite(); 
        void reset();
        FloatRect getGlobalBounds() const;
        void regenHealth();
};

#endif // BASE_H