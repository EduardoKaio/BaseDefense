#include "../include/base.h"
#include "../include/projetil_inimigo.h"
#include "../include/inimigo.h"
#include <algorithm>
#include <iostream>

Base::Base() : health(100) {
    if (!texture.loadFromFile("../assets/images/base.png")) {
        std::cerr << "Erro ao carregar a textura da base!" << std::endl;
        // Trate o erro adequadamente, talvez definir uma textura padrão
    }
    
    sprite.setTexture(texture);
    sprite.setScale(0.7f, 0.7f); // Ajuste a escala conforme necessário
    
    if (!font.loadFromFile("../assets/fonts/oficial.ttf")) { // Certifique-se de que o caminho está correto
        std::cerr << "Erro ao carregar a fonte!" << std::endl;
    }
    lossText.setFont(font);
    lossText.setCharacterSize(24);
    lossText.setFillColor(sf::Color(255, 0, 0, 128));
    lossText.setStyle(sf::Text::Bold);
    
    lossText.setPosition(400, 300);

}

template <typename T>
T clampe(T value, T min, T max) {
    return std::max(min, std::min(value, max));
}

bool isCircleCollidingWithRectangle(float circleX, float circleY, float circleRadius,
                                     float rectX, float rectY, float rectWidth, float rectHeight) {
    // Encontra o ponto mais próximo no retângulo ao centro do círculo
    float closestX = std::max(rectX, std::min(circleX, rectX + rectWidth));
    float closestY = std::max(rectY, std::min(circleY, rectY + rectHeight));

    // Calcula a distância entre o ponto mais próximo e o centro do círculo
    float dx = circleX - closestX;
    float dy = circleY - closestY;
    float distanceSquared = dx * dx + dy * dy;

    return distanceSquared <= circleRadius * circleRadius;
}

void Base::update(std::list<ProjetilInimigo>& projeteis, std::list<Inimigo>& inimigos) {
    // Verificar colisões com projéteis
    for (auto it = projeteis.begin(); it != projeteis.end();) {
        if (it->isActive()) {
            auto projShape = it->getSprite();
            float projX = projShape.getPosition().x;
            float projY = projShape.getPosition().y;
            float projRadius = projShape.getGlobalBounds().width/2;

            // Debug: imprimir posição do projétil
            std::cout << "Projétil posição: (" << projX << ", " << projY << ") com raio: " << projRadius << std::endl;

            if (isCircleCollidingWithRectangle(
                    projX,
                    projY,
                    projRadius,
                    sprite.getPosition().x,
                    sprite.getPosition().y,
                    sprite.getGlobalBounds().width,
                    sprite.getGlobalBounds().height)) {
                int damage = 2; // Reduz a vida da base
                health -= damage;
                showLossText = true;
                lossString = "-" + std::to_string(damage);
                lossText.setString(lossString);
                lossText.setOrigin(lossText.getLocalBounds().width / 2, lossText.getLocalBounds().height / 2);
                lossText.setPosition(400, 300); // Ajuste a posição conforme necessário
                lossClock.restart(); // Reinicia o cronômetro para exibir o texto por um período
                it = projeteis.erase(it); // Remove o projétil
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    // Verificar colisões com inimigos
    for (auto it = inimigos.begin(); it != inimigos.end();) {
        if (it->isAliveStatus()) {
            auto inimigoSprite = it->getSprite();
            float inimigoX = inimigoSprite.getPosition().x;
            float inimigoY = inimigoSprite.getPosition().y;
            float inimigoWidth = inimigoSprite.getGlobalBounds().width;
            float inimigoHeight = inimigoSprite.getGlobalBounds().height;
            float inimigoRadius = std::min(inimigoWidth, inimigoHeight) / 2;

            if (isCircleCollidingWithRectangle(
                    inimigoX + inimigoRadius,
                    inimigoY + inimigoRadius,
                    inimigoRadius,
                    sprite.getPosition().x,
                    sprite.getPosition().y,
                    sprite.getGlobalBounds().width,
                    sprite.getGlobalBounds().height)) {
                 int damage = 5; // Reduz a vida da base
                health -= damage;
                showLossText = true;
                lossString = "-" + std::to_string(damage);
                lossText.setString(lossString);
                lossText.setOrigin(lossText.getLocalBounds().width / 2, lossText.getLocalBounds().height / 2);
                lossText.setPosition(400, 300); // Ajuste a posição conforme necessário
                lossClock.restart(); // Reinicia o cronômetro para exibir o texto por um período
                it = inimigos.erase(it); // Remove o inimigo da lista
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    if (health <= 0) {
        health = 0; // Garante que a vida não fique negativa
    }
    if (showLossText && lossClock.getElapsedTime().asSeconds() > 1.0f) { // Exibe o texto por 1 segundo
        showLossText = false;
    }
    // Ajusta a largura da barra de vida
    float maxHealth = 100.0f;
    float barWidth = (health / maxHealth) * (sprite.getGlobalBounds().width - 32); // Largura proporcional
    lifeBar.setSize(sf::Vector2f(barWidth, 6)); // Atualiza a largura da barra

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

    // Atualiza a posição da barra de vida
    lifeBar.setPosition(sprite.getPosition().x + 16, sprite.getPosition().y - 10);
}

void Base::setPosition(const sf::Vector2f &position) {
    // shape.setPosition(position);
    sprite.setPosition(position);
}

int Base::getHealth() const {
    return health;
}


void Base::reduceHealth(int reduce) {
    health = health-reduce;
}

sf::Sprite& Base::getSprite() { 
    return sprite; 
}

bool Base::isAliveStatus() const {
    return health > 0;
}
sf::FloatRect Base::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Base::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // target.draw(shape, states);
    target.draw(sprite, states);
    target.draw(lifeBar, states); 
    if (showLossText) {
        target.draw(lossText, states);
    }
}
void Base::reset() {

    health = 100;

}

void Base::regenHealth() {
    // Recupera vida ao longo do tempo
    health++;
    if (health > 100) {
        health = 100;
    }
}