#include "../include/inimigo.h"
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;
using namespace sf;

Inimigo::Inimigo(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::RenderWindow* win)
: position(startPosition), direction(targetPosition - startPosition), health(2), isAlive(true), speed(30.0f), window(win) {

    // Inicializa fireRate com uma variação aleatória
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.5, 2.5); // Variação da taxa de disparo entre 0.5 e 2.5 segundos
    fireRate = dist(gen);
    fireTimer = 0.0f;
    
    
    if (!texture.loadFromFile("../assets/images/enemyBlack1.png")) {
        std::cerr << "Erro ao carregar a textura do inimigo!" << std::endl;
    } else {
        sprite.setTexture(texture);
        sprite.setPosition(startPosition);
        sprite.setScale(0.5f, 0.5f);
    }

    if (!enemyShootBuffer.loadFromFile("../assets/sounds/sfx_laser2.ogg")) {
        std::cerr << "Não foi possível carregar o som do tiro do inimigo!" << std::endl;
    }
    enemyShootSound.setBuffer(enemyShootBuffer);
}

void Inimigo::updateDirection(const sf::Vector2f& playerPosition) {
    sf::Vector2f newDirection = playerPosition - position;
    float length = std::sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
    if (length != 0) {
        newDirection /= length; // Normaliza o vetor
    }
    direction = newDirection;
}

void Inimigo::update(float deltaTime, const sf::Vector2f& playerPosition, bool audioEnabled) {
    // Atualiza a direção e move o inimigo
    updateDirection(playerPosition);
    sprite.move(direction * speed * deltaTime);
    
    // Atualiza o temporizador de disparo
    fireTimer += deltaTime;
    if (fireTimer >= fireRate) {
        fireTimer = 0.0f; // Reseta o temporizador
        fire(playerPosition, audioEnabled); // Dispara um projétil
    }

    // Atualiza projéteis
    for (auto& projetil : projeteis) {
        projetil.update(deltaTime);
    }
    
    // Remove projéteis fora da tela
    projeteis.erase(std::remove_if(projeteis.begin(), projeteis.end(),
        [&](const ProjetilInimigo& projetil) {
            return projetil.isOutOfWindow(*window);
        }), projeteis.end());
}

void Inimigo::fire(const sf::Vector2f& playerPosition, bool audioEnabled) {
    // Calcula a posição do projétil a partir da posição do inimigo
    sf::Vector2f projecaoPos = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    ProjetilInimigo newProjetil(projecaoPos, playerPosition);
    projeteis.push_back(newProjetil);

    if (audioEnabled && enemyShootSound.getStatus() != sf::Sound::Playing) {
        enemyShootSound.play();
    }
}

bool Inimigo::iscolliding(float x, float y, float radius) const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float centerX = bounds.left + bounds.width / 2;
    float centerY = bounds.top + bounds.height / 2;

    float dx = x - centerX;
    float dy = y - centerY;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = radius + std::min(bounds.width / 2, bounds.height / 2);

    return distanceSquared <= radiusSum * radiusSum;
}

bool Inimigo::isOutOfWindow(const sf::RenderWindow& window) const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::FloatRect viewport(window.getViewport(window.getView()));
    return !viewport.intersects(bounds);
}

void Inimigo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

std::vector<ProjetilInimigo>& Inimigo::getProjeteis() {
    return projeteis;
}

const std::vector<ProjetilInimigo>& Inimigo::getProjeteis() const {
    return projeteis;
}

void Inimigo::reduceHealth() {
    health = health - 1;
    if (health <= 0) isAlive = false;
}

void Inimigo::loadEnemyShootSound(const std::string& filepath) {
    if (!enemyShootBuffer.loadFromFile(filepath)) {
        std::cerr << "Não foi possível carregar o som do tiro do inimigo!" << std::endl;
    }
    enemyShootSound.setBuffer(enemyShootBuffer);
}
sf::FloatRect Inimigo::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

sf::Sprite& Inimigo::getSprite() { 
    return sprite; // Mudança aqui
}
void Inimigo::setSize(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

bool Inimigo::isAliveStatus() const { return isAlive; }