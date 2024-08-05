#include "../include/base.h"

using namespace std;
using namespace sf;

Base::Base() {
    shape.setSize(sf::Vector2f(300, 150));  // Define o tamanho do retângulo
    shape.setOutlineThickness(8);  // Define a espessura das bordas
    shape.setOutlineColor(sf::Color(34, 139, 34));  // Define a cor das bordas
    shape.setFillColor(sf::Color::Transparent);  // Define a cor de preenchimento como transparente
    shape.setOrigin(shape.getSize() / 2.0f);  // Define a origem no centro do retângulo
    shape.setPosition(300, 150);  // Define a posição central da base
}

void Base::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);  // Atualiza a posição do retângulo
}

void Base::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);  // Desenha o retângulo na janela
}

// void Base::update() {
//     // Lógica de regeneração ou outras atualizações
//     regenerateHealth();
// }

// void Base::draw(RenderTarget& target, RenderStates states) const {
//     target.draw(sprite, states);
// }

// int Base::getHealth() const {
//     return health;
// }

// void Base::reduceHealth(int amount) {
//     health -= amount;
//     if (health < 0) health = 0;
// }

// void Base::regenerateHealth() {
//     // Lógica de regeneração de saúde
//     if (health < maxHealth) {
//         health += 1; // Ajustar a taxa de regeneração conforme necessário
//     }
// }

// Vector2f Base::getPosition() const {
//     return sprite.getPosition();
// }
