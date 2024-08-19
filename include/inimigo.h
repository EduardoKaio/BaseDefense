#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "projetil_inimigo.h"
#include "drops.h"
#include "texture_manager.h"

using namespace std;
using namespace sf;

class Inimigo : public Drawable{
 
    private:
        virtual void draw(RenderTarget& target, RenderStates states) const override;
        
        Vector2f position;
        Texture texture;
        Sprite sprite;
        Vector2f direction;
        int health;
        bool isAlive;
        float speed;
        list<ProjetilInimigo> projeteis;
        list<Drops> possibleDrops;
        float fireRate; // Tempo entre disparos
        float fireTimer;
        const RenderWindow* window;
        SoundBuffer enemyShootBuffer; // Buffer para o som
        Sound enemyShootSound;
        TextureManager& textureManager; 

    public:
        Inimigo(const Vector2f& startPosition, const Vector2f& targetPosition, const RenderWindow* window, TextureManager& textureManager);
        void update(float deltaTime, const Vector2f& playerPosition, bool audioEnabled);
        void fire(const Vector2f& playerPosition, bool audioEnabled);
        bool isOutOfWindow(const RenderWindow& window) const;
        void updateDirection(const Vector2f& playerPosition);
        list<ProjetilInimigo>& getProjeteis();
        const list<ProjetilInimigo>& getProjeteis() const;
        void reduceHealth();
        bool isAliveStatus() const;
        void loadEnemyShootSound(const std::string& filepath); 
        bool iscolliding(float x, float y, float radius) const;
        FloatRect getGlobalBounds() const;
        void setSize(float scaleX, float scaleY);
        Sprite& getSprite();
        Drops dropItem();
};

#endif
