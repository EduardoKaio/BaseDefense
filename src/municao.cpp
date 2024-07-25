#include "../include/municao.h"

using namespace std;
using namespace sf;

Municao::Municao(Vector2f position) {
    forma.setSize(Vector2f(20, 20));
    forma.setFillColor(Color::Green);
    forma.setPosition(position);
}

void Municao::desenhar(RenderWindow& janela) {
    janela.draw(forma);
}

FloatRect Municao::getBounds() const {
    return forma.getGlobalBounds();
}