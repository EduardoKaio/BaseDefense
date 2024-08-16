#include "../include/projetil.h"
#include <cmath>
#include <iostream>
#include "../include/utils.h"

using namespace std;
using namespace sf;

Projetil::Projetil(sf::Vector2f startPosition, sf::Vector2f targetPosition, TextureManager& textureManager)
    : speed(500.0f), active(true) {

    sf::Texture* texture = textureManager.getTexture("projectile");
    if (texture) {
        sprite.setTexture(*texture); // Use o operador * para obter o objeto sf::Texture
        sprite.setPosition(startPosition);

        // Ajuste o tamanho do sprite, se necessário
        sprite.setScale(0.55f, 0.55f); // Ajuste o tamanho do projétil se necessário
    } else {
        // Caso a textura não esteja carregada, configure um fallback
        cout << "Erro ao careregar textura do projetil" << endl;
    }

    // Calcula a direção do projétil
    direction = targetPosition - startPosition;
    direction = normalize(direction);
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;

        // Define o ponto de origem da rotação para o centro do sprite
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setRotation(angle);  
}

void Projetil::update(float deltaTime) {
    sprite.move(direction * speed * deltaTime);
}

bool Projetil::isOutOfWindow(const sf::RenderWindow& window) const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return bounds.left + bounds.width < 0 || bounds.top + bounds.height < 0 ||
        bounds.left > window.getSize().x || bounds.top > window.getSize().y;
}

void Projetil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Projetil::iscolliding(float x1, float y1, float r1, float x2, float y2, float r2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = r1 + r2;
    return distanceSquared <= radiusSum * radiusSum;
}

sf::FloatRect Projetil::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
    
bool Projetil::isActive() const { return active; }
void Projetil::setActive(bool isActive) { active = isActive; }
Sprite& Projetil::getSprite(){return sprite;}