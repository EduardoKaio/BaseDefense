#include "../include/player.h"
#include "../include/utils.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player(std::list<Projetil>& projeteis) 
    : projeteis(projeteis), shooting(false), speed(300.0f), health(100), projeteisDisponiveis(100) {

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

    // Move o jogador
    shape.move(direction * speed * deltaTime);

    // Obter a posição atual do jogador
    sf::Vector2f position = shape.getPosition();
    sf::Vector2f size(shape.getRadius() * 2, shape.getRadius() * 2);

    // Verificar e ajustar os limites da tela
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + size.x > 800) position.x = 800 - size.x;
    if (position.y + size.y > 600) position.y = 600 - size.y;

    // Atualizar a posição do jogador
    shape.setPosition(position);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Dispara um projétil apenas se não houver disparo em andamento
        if (!shooting && projeteisDisponiveis > 0) {
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            // shoot(sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
            shooting = true;
        }
        } else {
            shooting = false; // Permite disparar novamente quando o botão for solto
        }
}

void Player::shoot(sf::Vector2f target) {
if (projeteisDisponiveis > 0) {
        // Obter a posição central do shape do jogador
        sf::Vector2f startPosition = shape.getPosition() + sf::Vector2f(shape.getRadius(), shape.getRadius());
        Projetil newProjetil(startPosition, target);
        projeteis.push_back(newProjetil);
        projeteisDisponiveis--; // Decrementar o número de projéteis disponíveis
    }
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

int Player::getProjeteisDisponiveis(){
    return projeteisDisponiveis;
};

void Player::reduceHealth(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

CircleShape& Player::getShape() { 
    return shape; 
}