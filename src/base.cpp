#include "../include/base.h"

using namespace std;
using namespace sf;

Base::Base() {
    texture.loadFromFile("../assets/images/teste.jpeg"); // Substituir pelo caminho correto
    sprite.setTexture(texture);
    sprite.setPosition(400, 300); // Posição inicial
    maxHealth = 200;
    health = maxHealth;
}

void Base::update() {
    // Lógica de regeneração ou outras atualizações
    regenerateHealth();
}

void Base::draw(RenderTarget& target, RenderStates states) const {
    target.draw(sprite, states);
}

int Base::getHealth() const {
    return health;
}

void Base::reduceHealth(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Base::regenerateHealth() {
    // Lógica de regeneração de saúde
    if (health < maxHealth) {
        health += 1; // Ajustar a taxa de regeneração conforme necessário
    }
}

Vector2f Base::getPosition() const {
    return sprite.getPosition();
}
