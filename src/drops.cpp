#include "../include/drops.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include "player.h"

using namespace std;
using namespace sf;

Drops::Drops(DropsType type, const sf::Vector2f& position, TextureManager& textureManager, float lifetime)
    : type(type), position(position), active(true), texture(nullptr), lifetime(lifetime) {
    // Configurar o sprite e a textura do item
    loadTexture(textureManager);
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

Drops::DropsType Drops::getType() const {
    return type;
}

void Drops::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    sprite.setPosition(position);
    
}

sf::Vector2f Drops::getPosition() const {
    return position;
}

bool Drops::loadTexture(TextureManager& textureManager) {
    switch (type) {
        case DropsType::Health:
            texture = textureManager.getTexture("health");
            sprite.setScale(0.06f, 0.06f);

            if (!texture) {
                std::cerr << "Falha ao obter a textura de saúde" << std::endl;
                return false;
            }
            break;
        case DropsType::Ammo:
            texture = textureManager.getTexture("ammo");
            sprite.setScale(0.1f, 0.1f);

            if (!texture) {
                std::cerr << "Falha ao obter a textura de munição" << std::endl;
                return false;
            }
            break;
    }
    sprite.setTexture(*texture);
    return true;
}

void Drops::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (active) {
        target.draw(sprite, states);
    }
}

bool Drops::iscolliding(float x1, float y1, float r1, float x2, float y2, float r2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = r1 + r2;
    return distanceSquared <= radiusSum * radiusSum;
}

void Drops::applyEffect(Player& player) {
    // Aplica o efeito dependendo do tipo de item
    switch (type) {
        case DropsType::Health:
            player.increaseHealth(5);
            break;
        case DropsType::Ammo:
            player.increaseAmmo(3);
            break;
    }
}

bool Drops::isActive() const { return active; }

void Drops::setActive(bool isActive) { 
    this->active = isActive;
}
sf::Sprite Drops::getSprite() const{
    return sprite;
}

void Drops::updadeDrops(float deltaTime) {
    lifetime = lifetime - 0.01f;

    if (lifetime <= 0.0f) {
        setActive(false);
    }
}