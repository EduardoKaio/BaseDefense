#include "../include/player.h"
#include "../include/utils.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player(std::list<Projetil>& projeteis) 
    : projeteis(projeteis), shooting(false), speed(300.0f), health(100) {

    shape.setRadius(15);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(400, 300);
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f direction(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction.x += 1;

    if (direction != sf::Vector2f(0, 0)) {
        direction = normalize(direction);
    }

    shape.move(direction * speed * deltaTime);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Dispara um projétil apenas se não houver disparo em andamento
        if (!shooting) {
            // shoot(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
            shooting = true;
        }
    } else {
        shooting = false; // Permite disparar novamente quando o botão for solto
    }
}

void Player::shoot(sf::Vector2f target) {
    Projetil newProjetil(shape.getPosition(), target);
    projeteis.push_back(newProjetil);
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

int Player::getHealth() const {
    return health;
}

void Player::reduceHealth(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}