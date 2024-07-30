#include "../include/game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Base Defense", sf::Style::Titlebar | sf::Style::Close), 
    projeteis(),
    player(projeteis), 
    base() {
        // Define o tamanho da janela como fixo
        window.setSize(sf::Vector2u(800, 600));

        // Define o modo de redimensionamento como fixo
        window.setPosition(sf::Vector2i(100, 100));  // Posição inicial da janela

        // Evento para garantir que a janela não seja redimensionada
        window.setVerticalSyncEnabled(true);
    }

void Game::run() {
    sf::Clock clock; // Mova o relógio para fora do loop
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart(); // Calcula o deltaTime
        processEvents();
        update(deltaTime.asSeconds());
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                player.shoot(mousePosF);
            }
        }
    }
}

void Game::update(float deltaTime) {
    player.update(deltaTime);

    for (auto it = projeteis.begin(); it != projeteis.end();) {
        it->update(deltaTime);
        if (it->isOutOfWindow(window)) {
            it = projeteis.erase(it); // Remove projéteis fora da tela
        } else {
            ++it;
        }
    }
}

void Game::render() {
    sf::Color backgroundColor(200, 200, 200); // Cor de fundo cinza claro
    window.clear(backgroundColor);
    window.draw(base); // Desenha a base
    window.draw(player); // Desenha o player

    for (const auto& projetil : projeteis) {
        window.draw(projetil); // Desenha os projéteis
    }

    window.display();
}

