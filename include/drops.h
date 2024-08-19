#ifndef DROPS_HPP
#define DROPS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "texture_manager.h"
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
        virtual void draw(RenderTarget& target, RenderStates states) const override;
        
        Sprite sprite;
        Texture* texture;
        DropsType type;
        Vector2f position;
        bool active;
        float lifetime;

    public:
        Drops(DropsType type, const Vector2f& position, TextureManager& textureManager, float lifetime);
        DropsType getType() const;
        void setPosition(const Vector2f& newPosition);
        Vector2f getPosition() const;
        bool loadTexture(const std::string& filepath);
        bool iscolliding(float x1, float y1, float r1, float x2, float y2, float r2);
        void applyEffect(Player& player);
        void setActive(bool isActive);
        bool isActive() const;
        Sprite getSprite() const;
        bool loadTexture(TextureManager& textureManager);
        void updadeDrops(float deltaTime);
};

#endif