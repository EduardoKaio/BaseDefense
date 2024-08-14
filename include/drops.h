#ifndef DROPS_HPP
#define DROPS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"

using namespace std;
using namespace sf;

class Drops : public Drawable {
    //Tipos de itens
    public:
        enum class DropsType {
            Health, 
            Ammo
        };

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        sf::Sprite sprite;
        sf::Texture texture;
        DropsType type;
        sf::Vector2f position;
        sf::CircleShape circle;
        bool active;

    public:
        Drops(DropsType type, const sf::Vector2f& position);
        DropsType getType() const;
        void setPosition(const sf::Vector2f& newPosition);
        sf::Vector2f getPosition() const;

        // Método para carregar a textura do item
        bool loadTexture(const std::string& filepath);
        bool iscolliding(float x1, float y1, float r1, float x2, float y2, float r2);
        void applyEffect(Player& player);
        CircleShape getShape() const;
        void setActive(bool isActive);
        bool isActive() const;
};

#endif