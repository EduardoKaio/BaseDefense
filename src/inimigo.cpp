#include "../include/inimigo.h"
#include <cmath> // Necessário para std::sqrt

using namespace std;
using namespace sf;

Inimigo::Inimigo(Texture& texture, float x, float y) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Inimigo::update(float deltaTime, const Vector2f& targetPosition) {
    // Calcula o vetor direção para o alvo subtraindo a posição atual do inimigo da posição do alvo
    Vector2f direction = targetPosition - sprite.getPosition();
    
    // Calcula o comprimento (distância) do vetor direção
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    
    // Normaliza o vetor direção (torna seu comprimento igual a 1) para obter apenas a direção
    if (length != 0) {
        direction /= length;
    }
    
    // Move o inimigo na direção normalizada, multiplicando pela velocidade e pelo deltaTime
    sprite.move(direction * speed * deltaTime);
}

void Inimigo::draw(RenderTarget& target, RenderStates states) const {
    target.draw(sprite, states);
}

Vector2f Inimigo::getPosition() const {
    return sprite.getPosition();
}