#include "../include/projetil_inimigo.h"
#include <cmath> // Necessário para std::sqrt

using namespace std;
using namespace sf;

ProjetilInimigo::ProjetilInimigo(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition)
    : position(startPosition), speed(50.0f) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);

    // Calcula a direção
    direction = targetPosition - startPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length; // Normaliza o vetor
    }
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