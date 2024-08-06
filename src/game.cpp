#include "../include/game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Base Defense", sf::Style::Titlebar | sf::Style::Close), 
    projeteis(),
    player(projeteis), 
    base(),
    spawnInterval(3.0f) {
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
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0.0f;

        // Posições aleatórias nas bordas do mapa
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1);

        sf::Vector2f startPosition;
        sf::Vector2f playerPosition = player.getShape().getPosition() + sf::Vector2f(player.getShape().getRadius(), player.getShape().getRadius());

        if (dist(gen) == 0) {
            // Em uma borda vertical
            startPosition.x = (dist(gen) == 0) ? 0 : window.getSize().x;
            startPosition.y = std::uniform_real_distribution<>(0, window.getSize().y)(gen);
        } else {
            // Em uma borda horizontal
            startPosition.x = std::uniform_real_distribution<>(0, window.getSize().x)(gen);
            startPosition.y = (dist(gen) == 0) ? 0 : window.getSize().y;
        }

        inimigos.emplace_back(startPosition, playerPosition, &window);
    }

    player.update(deltaTime);

    for (auto it = inimigos.begin(); it != inimigos.end();) {
        it->update(deltaTime, player.getShape().getPosition());

        if (!it->isAliveStatus()) {
            it = inimigos.erase(it);
        } else {
            it++;
        }
        
    }

    for (auto it = projeteis.begin(); it != projeteis.end();) {
        it->update(deltaTime);

        for (Inimigo& enemy : inimigos) {  
            sf::Vector2f projectilePosition = it->getShape().getPosition();            
            sf::Vector2f enemyPosition = enemy.getShape().getPosition();           

            if (enemy.isAliveStatus() && it->isActive() && it->iscolliding(projectilePosition.x, projectilePosition.y, it->getShape().getRadius(),
                                                                           enemyPosition.x, enemyPosition.y, enemy.getShape().getRadius())) {
                enemy.reduceHealth();
                it->setActive(false);
            }
        }

        if (it->isActive()) {
            ++it;
        } else {
            it = projeteis.erase(it);
        }  

        if (it->isOutOfWindow(window)) {
            it = projeteis.erase(it); // Remove projéteis fora da tela
        } else {
            ++it;
        }
    }

    // Atualiza e remove projéteis dos inimigos
    for (auto it = inimigos.begin(); it != inimigos.end();) {
        for (auto projIt = it->getProjeteis().begin(); projIt != it->getProjeteis().end();) {
            projIt->update(deltaTime);
            
            sf::Vector2f projectilePosition = projIt->getShape().getPosition();            
            sf::Vector2f playerPosition = player.getShape().getPosition();           

            if (player.isAliveStatus() && projIt->isActive() && projIt->iscolliding(projectilePosition.x, projectilePosition.y, projIt->getShape().getRadius(),
                                                                                    playerPosition.x, playerPosition.y, player.getShape().getRadius())) {
                player.reduceHealth(5);
                projIt->setActive(false);
            }
            
            
            if (projIt->isOutOfWindow(window)) {
                projIt = it->getProjeteis().erase(projIt); // Remove projéteis fora da tela
            } else {
                ++projIt;
            }
        }

        // Remover inimigo se necessário
        if (it->isOutOfWindow(window)) {
            it = inimigos.erase(it); // Remove inimigo fora da tela
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

    for (const auto& inimigo : inimigos) {
        window.draw(inimigo); // Desenha os inimigos
        for (const auto& projetil : inimigo.getProjeteis()) {
            window.draw(projetil); // Desenha projéteis dos inimigos
        }
    }

    sf::Font font;
    if (!font.loadFromFile("../assets/fonts/pixel.ttf")) { // Certifique-se de fornecer um caminho para a fonte
        std::cerr << "Não foi possível carregar a fonte!" << std::endl;
    }
     sf::RectangleShape projeteisBox(sf::Vector2f(60, 50)); // Tamanho da caixa
    projeteisBox.setFillColor(sf::Color::White); // Cor da caixa
    projeteisBox.setOutlineColor(sf::Color::Black); // Cor da borda
    projeteisBox.setOutlineThickness(2); // Espessura da borda
    projeteisBox.setPosition(window.getSize().x - 80, 10); // Posição no canto superior direito

    sf::Text projeteisText;
    projeteisText.setFont(font); // Fonte carregada anteriormente
    projeteisText.setString(to_string(player.getProjeteisDisponiveis()));
    projeteisText.setCharacterSize(26);
    projeteisText.setFillColor(sf::Color::Black);
    projeteisText.setPosition(window.getSize().x - 70, 20); // Posição do texto na caixa

    window.draw(projeteisBox); // Desenha a caixa
    window.draw(projeteisText);

    window.display();
}

