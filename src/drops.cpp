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

Drops::Drops(DropsType type, const sf::Vector2f& position)
    : type(type), position(position), active(true) {  
    // Configurando o círculo que representa o item
    circle.setRadius(15.0f); // Define o raio do círculo
    circle.setPosition(position); // Define a posição do item na tela
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    // Carregar a textura apropriada para o tipo de item
    switch (type) {
        case DropsType::Health:
            circle.setFillColor(sf::Color::Green);
            break;
        case DropsType::Ammo:
            circle.setFillColor(sf::Color::Red);
            break;
    }
}

Drops::DropsType Drops::getType() const {
    return type;
}

void Drops::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    circle.setPosition(position);
}

sf::Vector2f Drops::getPosition() const {
    return position;
}

bool Drops::loadTexture(const std::string& filepath) {
    if (!texture.loadFromFile(filepath)) {
        std::cerr << "Erro ao carregar a textura do item: " << filepath << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

void Drops::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(circle, states);
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
            player.increaseHealth(5); // Supondo que o Player tenha esse método
            break;
        case DropsType::Ammo:
            player.increaseAmmo(3); // Supondo que o Player tenha esse método
            break;
    }
}

CircleShape Drops::getShape() const{
    return circle;
}

bool Drops::isActive() const { return active; }

void Drops::setActive(bool isActive) { 
    this->active = isActive;
}