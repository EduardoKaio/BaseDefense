#include "../include/player.h"



Player::Player(list<Projetil>& projeteis) : projeteis(projeteis) {
    texture.loadFromFile("path_to_player_texture.png"); // Substituir pelo caminho correto
    sprite.setTexture(texture);
    sprite.setPosition(400, 300); // Posição inicial
    speed = 200.0f;
    health = 100;
}

Player::Player() : projeteis(*(new list<Projetil>())) { // Inicialize com uma lista vazia ou configure de outra forma
    // Configurações padrão, se necessário
    texture.loadFromFile("path_to_player_texture.png");
    sprite.setTexture(texture);
    sprite.setPosition(400, 300);
    speed = 200.0f;
    health = 100;
}

void Player::handleInput() {
    Vector2f direction(0, 0);
    if (Keyboard::isKeyPressed(Keyboard::W)) direction.y -= 1;
    if (Keyboard::isKeyPressed(Keyboard::S)) direction.y += 1;
    if (Keyboard::isKeyPressed(Keyboard::A)) direction.x -= 1;
    if (Keyboard::isKeyPressed(Keyboard::D)) direction.x += 1;

    sprite.move(direction * speed * sf::seconds(1.f).asSeconds());

    if (Keyboard::isKeyPressed(Keyboard::Q)) {
        shoot(sf::Vector2f(400, 300)); // Substituir pelo alvo real
    }
}

void Player::update() {
    // Atualizações do jogador
}

void Player::draw(RenderTarget& target, RenderStates states) const {
    target.draw(sprite, states);
}

void Player::shoot(Vector2f target) {
    Projetil newProjetil(sprite.getPosition(), target);
    projeteis.push_back(newProjetil);
}

int Player::getHealth() const {
    return health;
}

void Player::reduceHealth(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}