#ifndef PROJETIL_HPP
#define PROJETIL_HPP

#include <SFML/Graphics.hpp>
#include "texture_manager.h"

using namespace std;
using namespace sf;

class Projetil : public Drawable{
    
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        Sprite sprite;
        Vector2f direction;  // Direção do projétil
        float speed;
        bool active;

        
     
    public:
        Projetil(Vector2f position, Vector2f target, TextureManager& textureManager);
        void update(float deltaTime);
        bool isOutOfWindow(const RenderWindow& window) const;
        bool iscolliding(float x1, float y1, float r1, float x2, float y2, float r2);
        Sprite& getSprite();
        void setActive(bool isActive);
        bool isActive() const;
        FloatRect getGlobalBounds() const;
};

#endif