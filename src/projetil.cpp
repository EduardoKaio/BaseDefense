#include "../include/projetil.h"

using namespace std;
using namespace sf;

Projetil::Projetil(){}

Projetil::Projetil(Vector2f position, Vector2f direction) {
    forma.setRadius(5.0f);
    forma.setFillColor(Color::Yellow);
    forma.setPosition(position);
    velocidade = direction * 0.5f; // Velocidade do projétil
}

void Projetil::update() {
    forma.move(velocidade);  // Mover o projétil baseado na velocidade
}

FloatRect Projetil::getBounds() const {
    return forma.getGlobalBounds();
}

void Projetil::draw(RenderTarget& target, RenderStates states) const {
    target.draw(forma, states);
}