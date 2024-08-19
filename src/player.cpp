#include "../include/player.h"
#include "../include/utils.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Player::Player(std::list<Projetil>& projeteis, TextureManager& textureManager) 
    : projeteis(projeteis), shooting(false), speed(300.0f), isAlive(true), health(100), projeteisDisponiveis(50), maxHealth(100),
    maxAmmo(50), textureManager(textureManager) {

    if (!texture.loadFromFile("../assets/images/playerShip1_blue.png")) {
    // Erro ao carregar a textura
        std::cerr << "Erro ao carregar a textura do herói!" << std::endl;
    } else {
        sprite.setTexture(texture);
        // Ajuste o tamanho e a posição inicial do sprite, se necessário
        sprite.setPosition(400, 300); 
        // Ajuste a posição inicial do herói
    }
    
    if (!font.loadFromFile("../assets/fonts/oficial.ttf")) { // Substitua o caminho pela localização da sua fonte
        std::cerr << "Erro ao carregar a fonte!" << std::endl;
    }
    lifeEffectText.setFont(font);
    lifeEffectText.setString("+5");
    lifeEffectText.setCharacterSize(16); // Tamanho do texto
    lifeEffectText.setFillColor(sf::Color::Green); // Cor do texto
   

    ammoBonusText.setFont(font); // Certifique-se de que o font está carregado
    ammoBonusText.setString("+3");
    ammoBonusText.setCharacterSize(15);
    ammoBonusText.setFillColor(sf::Color::Yellow);
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
    if (position.x + (size.x)/2 > 800) position.x = 800 - (size.x)/2;
    if (position.y + (size.y)/2 > 600) position.y = 600 - (size.y)/2;

    // Atualizar a posição do jogador
    sprite.setPosition(position); // Mudança aqui
    lifeBar.setPosition(position.x + 3, position.y -10);
}

void Player::shoot(sf::Vector2f target) {
    if (projeteisDisponiveis > 0) {
        // Obter a posição central do shape do jogador
        sf::Vector2f startPosition = sprite.getPosition() + sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        Projetil newProjetil(startPosition, target, textureManager); // Passe o TextureManager para Projetil
        projeteis.push_back(newProjetil);
        projeteisDisponiveis--; // Decrementar o número de projéteis disponíveis
    }
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
    float maxHealth = 100.0f;
    float barWidth = (health / maxHealth) * (sprite.getGlobalBounds().width - 6); // Largura proporcional
    lifeBar.setSize(sf::Vector2f(barWidth, 2.5f)); // Atualiza a largura da barra

    // Atualiza a cor da barra de vida com base na vida
    if (health > 75) {
        lifeBar.setFillColor(sf::Color::Green);
    } else if (health > 50) {
        lifeBar.setFillColor(sf::Color::Yellow);
    } else if (health > 25) {
        lifeBar.setFillColor(sf::Color(255, 165, 0)); // Laranja
    } else {
        lifeBar.setFillColor(sf::Color::Red);
    }
    if (showLifeEffect) {
        lifeEffectTimer += deltaTime;
        if (lifeEffectTimer > 1.0f) { // O efeito dura 1 segundo
            showLifeEffect = false;
            lifeEffectTimer = 0;
        }
    }
    lifeEffectText.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y + 40);
    // ammoEffectText.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y - 20);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    target.draw(lifeBar, states);   
    if (showLifeEffect) {
        target.draw(lifeEffectText, states);
    }
}

int Player::getHealth() const {
    return health;
}
int Player::getMaxHealth(){
    return maxHealth;
}

int Player::getProjeteisDisponiveis(){
    return projeteisDisponiveis;
};

void Player::reduceHealth(int amount) {
    health -= amount;
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

void Player::increaseHealth(int amount) {
 if (health < maxHealth) {
        health += amount;
        showLifeEffect = true; // Ativa o efeito visual
        lifeEffectTimer = 0; // Reinicia o temporizador
    }
}

void Player::increaseAmmo(int amount) {
    if (projeteisDisponiveis < maxAmmo) {
        projeteisDisponiveis += amount;
        ammoBonusVisible = true;     // Ativa o efeito visual
        // Reinicia o temporizador
    }
}

int Player::getMaxAmmo(){
    return maxAmmo;
}
void Player::hideAmmoBonus() {
    ammoBonusVisible = false;
}
bool Player::getAmmoBonusVisible(){
    return ammoBonusVisible;
}