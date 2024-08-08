#include "../include/player.h"
#include "../include/utils.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Player::Player(std::list<Projetil>& projeteis) 
    : projeteis(projeteis), shooting(false), speed(300.0f), isAlive(true), health(100), projeteisDisponiveis(100) {

        if (!texture.loadFromFile("../assets/images/playerShip1_blue.png")) {
    // Erro ao carregar a textura
    std::cerr << "Erro ao carregar a textura do herói!" << std::endl;
    } else {
        sprite.setTexture(texture);
        // Ajuste o tamanho e a posição inicial do sprite, se necessário
        sprite.setPosition(400, 300); 
        // Ajuste a posição inicial do herói
    }
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
    sprite.move(direction * speed * deltaTime); // Mudança aqui

    // Obter a posição atual do jogador
    sf::Vector2f position = sprite.getPosition(); // Mudança aqui
    sf::Vector2f size(sprite.getLocalBounds().width, sprite.getLocalBounds().height); // Mudança aqui

    // Verificar e ajustar os limites da tela
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + size.x > 800) position.x = 800 - size.x;
    if (position.y + size.y > 600) position.y = 600 - size.y;

    // Atualizar a posição do jogador
    sprite.setPosition(position); // Mudança aqui

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //     if (!shooting && projeteisDisponiveis > 0) {
    //         sf::Vector2i mousePos = sf::Mouse::getPosition();
    //         shoot(sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
    //         shooting = true;
    //     }
    // } else {
    //     shooting = false;
    // }
}

void Player::shoot(sf::Vector2f target) {
    if (projeteisDisponiveis > 0) {
        // Obter a posição central do shape do jogador
        sf::Vector2f startPosition = sprite.getPosition() + sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        Projetil newProjetil(startPosition, target);
        projeteis.push_back(newProjetil);
        projeteisDisponiveis--; // Decrementar o número de projéteis disponíveis
    }
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

int Player::getHealth() const {
    return health;
}

int Player::getProjeteisDisponiveis(){
    return projeteisDisponiveis;
};

void Player::reduceHealth(int amount) {
    health -= amount;
    cout << health << endl;
    if (health <= 0) {
        isAlive = false;
        cout << "O player morreu" << endl;
    };
}
sf::Sprite& Player::getSprite() { 
    return sprite; // Mudança aqui
}
void Player::setSize(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Player::reset() {
    health = 100;
    sprite.setPosition(400, 300); // Mudança aqui
    projeteisDisponiveis = 100;
}
sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

bool Player::isAliveStatus() const { return isAlive; }
