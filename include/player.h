#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <list>
#include "projetil.h"
#include "texture_manager.h"

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
        int kill;
        int maxHealth;
        int maxAmmo;
        TextureManager& textureManager;
        sf::RectangleShape lifeBar; 
        sf::Text lifeEffectText; // Texto para o efeito visual de vida
        sf::Font font; // Fonte para o texto
        bool showLifeEffect; // Flag para mostrar o efeito
        float lifeEffectTimer;
        sf::Text ammoEffectText; // Texto para o efeito visual de munição
        bool ammoBonusVisible;  // Adicione essa linha
        
    public:
        sf::Text ammoBonusText;
        Player(list<Projetil>& projeteis, TextureManager& textureManager);
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
        void increaseHealth(int amount);
        void increaseAmmo(int amount);
        int getMaxHealth();
        int getMaxAmmo();
        void hideAmmoBonus();
        bool getAmmoBonusVisible();

};
#endif