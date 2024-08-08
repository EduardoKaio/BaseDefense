#include "../include/projetil_inimigo.h"
#include <cmath> // Necessário para std::sqrt

using namespace std;
using namespace sf;

ProjetilInimigo::ProjetilInimigo(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition)
    : position(startPosition), speed(50.0f), active(true) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color(138, 43, 226));
    shape.setPosition(position);

    // Calcula a direção
    direction = targetPosition - startPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length; // Normaliza o vetor
    }
}
template <typename T>
T clampe(T value, T min, T max) {
    return std::max(min, std::min(value, max));
}

void ProjetilInimigo::update(float deltaTime) {
    position += direction * speed * deltaTime;
    shape.setPosition(position);
}

bool ProjetilInimigo::isOutOfWindow(const sf::RenderWindow& window) const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    sf::FloatRect viewport(window.getViewport(window.getView()));
    return !viewport.intersects(bounds);
}

void ProjetilInimigo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
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
    return distance < shape.getRadius();
}

CircleShape ProjetilInimigo::getShape() const { 
    return shape; 
}

void ProjetilInimigo::setActive(bool isActive) { 
    active = isActive; 
}
sf::FloatRect ProjetilInimigo::getGlobalBounds() const {
    return shape.getGlobalBounds();
}
bool ProjetilInimigo::isActive() const { return active; }