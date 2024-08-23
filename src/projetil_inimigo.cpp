#include "../include/projetil_inimigo.h"
#include <cmath> // Necessário para std::sqrt
#include <iostream>
#include "config.h"
using namespace std;
using namespace sf;

ProjetilInimigo::ProjetilInimigo(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, TextureManager& textureManager)
    : position(startPosition), 
    speed(Config::PROJETIL_INIMIGO_SPEED), 
    active(true) {
    
    sf::Texture* texture = textureManager.getTexture("projectile_inimigo");
    if (texture) {
        sprite.setTexture(*texture); // Use o operador * para obter o objeto sf::Texture
        sprite.setPosition(startPosition);

        // Ajuste o tamanho do sprite, se necessário
        sprite.setScale(0.55f, 0.55f); // Ajuste o tamanho do projétil se necessário
    } else {
        // Caso a textura não esteja carregada, configure um fallback
        cout << "Erro ao carregar textura do projétil" << endl;
    }

    direction = targetPosition - startPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length; // Normaliza o vetor
    }

    // Calcula o ângulo da direção em relação ao eixo X
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;

    // Define o ponto de origem da rotação para o centro do sprite
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setRotation(angle);
}

template <typename T>
T clampe(T value, T min, T max) {
    return std::max(min, std::min(value, max));
}

void ProjetilInimigo::update(float deltaTime) {
    position += direction * speed * deltaTime;
    sprite.setPosition(position);
}

bool ProjetilInimigo::isOutOfWindow(const sf::RenderWindow& window) const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return !window.getView().getViewport().intersects(bounds);
}

void ProjetilInimigo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool ProjetilInimigo::iscolliding(float x1, float y1, float r1, float x2, float y2, float r2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = r1 + r2;
    return distanceSquared <= radiusSum * radiusSum;
}

bool ProjetilInimigo::iscollidingBase(float projX, float projY, float baseX, float baseY, float baseWidth, float baseHeight) const {
    // Calcula o ponto mais próximo no retângulo
    float closestX = clampe(projX, baseX, baseX + baseWidth);
    float closestY = clampe(projY, baseY, baseY + baseHeight);

    // Calcula a distância entre o projétil e o ponto mais próximo no retângulo
    float distX = projX - closestX;
    float distY = projY - closestY;
    float distance = std::sqrt(distX * distX + distY * distY);

    // Verifica se a distância é menor que o raio do projétil
    return distance < (sprite.getGlobalBounds().width / 2); // Ajuste se necessário
}

Sprite& ProjetilInimigo::getSprite() { 
    return sprite; 
}

void ProjetilInimigo::setActive(bool isActive) { 
    active = isActive; 
}

sf::FloatRect ProjetilInimigo::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

bool ProjetilInimigo::isActive() const { 
    return active; 
}
