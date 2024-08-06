#include "../include/projetil.h"
#include <cmath>
#include "../include/utils.h"

using namespace std;
using namespace sf;

Projetil::Projetil(sf::Vector2f startPosition, sf::Vector2f targetPosition)
    : speed(500.0f), active(true) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Black); // Define a cor preta
    shape.setPosition(startPosition);

    // Calcula a direção do projétil
    direction = targetPosition - startPosition;
    direction = normalize(direction);
}

void Projetil::update(float deltaTime) {
    shape.move(direction * speed * deltaTime);
}

bool Projetil::isOutOfWindow(const sf::RenderWindow& window) const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    return bounds.left + bounds.width < 0 || bounds.top + bounds.height < 0 ||
           bounds.left > window.getSize().x || bounds.top > window.getSize().y;
}

void Projetil::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

bool Projetil::iscolliding(float x1, float y1, float r1, float x2, float y2, float r2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = r1 + r2;
    return distanceSquared <= radiusSum * radiusSum;
}

CircleShape& Projetil::getShape() { 
    return shape; 
}

void Projetil::setActive(bool isActive) { 
    active = isActive; 
}
    
bool Projetil::isActive() const { return active; }