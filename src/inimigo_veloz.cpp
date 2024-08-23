#include "../include/inimigo_veloz.h"
#include "../include/config.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

InimigoVeloz::InimigoVeloz(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::RenderWindow* win, TextureManager& textureManager)
    : Inimigo(startPosition, targetPosition, win, textureManager) {
    // Configure a textura e outros atributos específicos, se necessário
}

void InimigoVeloz::fire(const sf::Vector2f& playerPosition, bool audioEnabled) {
    // Calcula a posição do projétil a partir da posição do inimigo
    sf::Vector2f projecaoPos = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    // Atira projéteis na base (não no jogador)
    ProjetilInimigo newProjetil(projecaoPos, Vector2f(position.x, 0), textureManager); // Ataque na base (exemplo)
    projeteis.push_back(newProjetil);

    if (audioEnabled && enemyShootSound.getStatus() != sf::Sound::Playing) {
        enemyShootSound.play();
    }
}