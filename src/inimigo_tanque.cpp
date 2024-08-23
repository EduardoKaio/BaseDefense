#include "../include/inimigo_tanque.h"
#include "../include/config.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

InimigoTanque::InimigoTanque(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::RenderWindow* win, TextureManager& textureManager)
    : Inimigo(startPosition, targetPosition, win, textureManager) {
    // Configura atributos específicos para o tanque
    health = Config::ENEMY_TANQUE_HEALTH; // Mais vida
    speed = Config::ENEMY_TANQUE_SPEED;   // Menos velocidade, ou configure conforme necessário

    if (!texture.loadFromFile("../assets/images/enemyTank.png")) {
        std::cerr << "Erro ao carregar a textura do inimigo tanque!" << std::endl;
    } else {
        sprite.setTexture(texture);
        sprite.setPosition(startPosition);
        sprite.setScale(0.5f, 0.5f);
    }
}

void InimigoTanque::fire(const sf::Vector2f& targetPosition, bool audioEnabled) {
    // Calcula a posição do projétil a partir da posição do inimigo
    sf::Vector2f projecaoPos = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    // Ataque ao jogador
    ProjetilInimigo newProjetil(projecaoPos, targetPosition, textureManager);
    projeteis.push_back(newProjetil);

    if (audioEnabled && enemyShootSound.getStatus() != sf::Sound::Playing) {
        enemyShootSound.play();
    }
}