#include "../include/game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Base Defense") {
    // Configuração inicial do jogo
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    player.handleInput();
}

void Game::update() {
    sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();

    player.update();
    base.update();
    sf::Vector2f targetPosition = base.getPosition();  // Posição da base como alvo

    for (auto& inimigo : inimigos) {
        inimigo.update(deltaTime, targetPosition);  // Passa o deltaTime e a posição alvo
    }

    for (auto& projetil : projeteis) {
        projetil.update();  // Assumindo que update() existe em Projetil
    }

    handleCollisions();
}


void Game::render() {
    window.clear();
    window.draw(player);
    window.draw(base);
    
    for (const auto& inimigo : inimigos)
        window.draw(inimigo);
    
    for (const auto& projetil : projeteis)
        window.draw(projetil);
    window.display();
}

void Game::spawnInimigos() {
    // Lógica para spawn de inimigos
}

void Game::handleCollisions() {
    // Lógica de colisão
}