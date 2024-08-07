#include "../include/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Base Defense", sf::Style::Titlebar | sf::Style::Close), 
    projeteis(),
    player(projeteis), 
    base(),
    spawnInterval(3.0f),
    gameOver(false) {

    // Define o tamanho da janela como fixo
    window.setSize(sf::Vector2u(800, 600));

    // Define o modo de redimensionamento como fixo
    window.setPosition(sf::Vector2i(100, 100));  // Posição inicial da janela

    // Evento para garantir que a janela não seja redimensionada
    window.setVerticalSyncEnabled(true);

    // Ajuste a posição do jogador para o centro da tela
    sf::Vector2f center(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    player.getShape().setPosition(center);

    // Ajuste a posição da base para o centro da tela
    sf::Vector2f basePosition(window.getSize().x / 2.0f - base.getShape().getSize().x / 2.0f,
                            window.getSize().y / 2.0f - base.getShape().getSize().y / 2.0f);
    base.setPosition(basePosition);

    if (!backgroundMusic.openFromFile("../assets/sounds/boss_battle_#2.WAV")) {
        std::cerr << "Não foi possível carregar a música de fundo!" << std::endl;
        // Gerenciar erro, talvez encerrar o jogo
    }

    // Configurar a música para tocar em loop
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(40); 
    backgroundMusic.play();

        // Carregar som do tiro do herói
    if (!heroShootBuffer.loadFromFile("../assets/sounds/tiro_heroi.wav")) {
        std::cerr << "Não foi possível carregar o som do tiro do herói!" << std::endl;
    }
    heroShootSound.setBuffer(heroShootBuffer);

    std::string enemyShootSoundFile = "../assets/sounds/tiro_inimigo.wav";
    for (auto& inimigo : inimigos) {
        inimigo.loadEnemyShootSound(enemyShootSoundFile);
    }
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
            if (event.mouseButton.button == sf::Mouse::Left && !gameOver) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                player.shoot(mousePosF);

                // Tocar som do tiro do herói
                heroShootSound.play();
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (gameOver) return; // Não atualiza o jogo se estiver em game over

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
    
    base.update(projeteisInimigos, inimigos);

    // Verifica se a vida do jogador chegou a 0
    if (player.getHealth() <= 0 || base.getHealth() <= 0) {
            gameOver = true; // Define o estado do jogo como game over
    }

    for (auto it = inimigos.begin(); it != inimigos.end();) {
        it->update(deltaTime, player.getShape().getPosition());

        if (!it->isAliveStatus()) {
            it = inimigos.erase(it);
        } else {
            ++it;
        }
    }

    // Atualiza e verifica projéteis do jogador
    for (auto it = projeteis.begin(); it != projeteis.end();) {
        it->update(deltaTime);

        // Verifica colisões com inimigos
        for (auto enemyIt = inimigos.begin(); enemyIt != inimigos.end(); ++enemyIt) {
            if (enemyIt->isAliveStatus() && it->isActive() &&
                it->iscolliding(it->getShape().getPosition().x, it->getShape().getPosition().y, it->getShape().getRadius(),
                                enemyIt->getShape().getPosition().x, enemyIt->getShape().getPosition().y, enemyIt->getShape().getRadius())) {
                enemyIt->reduceHealth();
                it->setActive(false);
                break; // Só precisa verificar a colisão com um inimigo
            }
        }

        // Remove projéteis que saíram da tela
        if (it->isOutOfWindow(window) || !it->isActive()) {
            it = projeteis.erase(it); // Remove projéteis fora da tela ou se colidiram com algo
        } else {
            ++it;
        }
    }

    // Atualiza e remove projéteis dos inimigos
    for (auto it = inimigos.begin(); it != inimigos.end();) {
        for (auto projIt = it->getProjeteis().begin(); projIt != it->getProjeteis().end();) {
            projIt->update(deltaTime);
            enemyShootSound.play();
            // Verifica colisões com o jogador
            if (player.isAliveStatus() && projIt->isActive() &&
                projIt->iscolliding(projIt->getShape().getPosition().x, projIt->getShape().getPosition().y, projIt->getShape().getRadius(),
                                    player.getShape().getPosition().x, player.getShape().getPosition().y, player.getShape().getRadius())) {
                player.reduceHealth(5);
                projIt->setActive(false);
                // O projétil deve ser removido da lista de projéteis do inimigo
                projIt = it->getProjeteis().erase(projIt);
            
            } else if (projIt->isActive() &&
                       projIt->iscollidingBase(projIt->getShape().getPosition().x, projIt->getShape().getPosition().y,
                                           base.getShape().getPosition().x, base.getShape().getPosition().y,
                                           base.getShape().getSize().x, base.getShape().getSize().y)) {
                base.reduceHealth(2);
                projIt->setActive(false);
                projIt = it->getProjeteis().erase(projIt);
            } else {
                ++projIt;
            }
        }

        // Remove inimigos que saíram da tela
        if (it->isOutOfWindow(window)) {
            it = inimigos.erase(it);
        } else {
            ++it;
        }
    }
}


void Game::render() {
    sf::Color backgroundColor(200, 200, 200); // Cor de fundo cinza claro
    window.clear(backgroundColor);

    // Desenha a base e o player
    window.draw(base); 
    window.draw(player);

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
    
    sf::RectangleShape infoBox(sf::Vector2f(150, 80)); // Tamanho da caixa ajustado
    infoBox.setFillColor(sf::Color::White); // Cor da caixa
    infoBox.setOutlineColor(sf::Color::Black); // Cor da borda
    infoBox.setOutlineThickness(2); // Espessura da borda
    infoBox.setPosition(window.getSize().x - 160, 10); // Posição no canto superior direito

    sf::Text infoText;
    infoText.setFont(font); // Fonte carregada anteriormente
    infoText.setString("Municao: " + std::to_string(player.getProjeteisDisponiveis()) + "\n" +
                       "Vida: " + std::to_string(player.getHealth()) + "\n" +
                       "Vida Base: " + std::to_string(base.getHealth()));
    infoText.setCharacterSize(20); // Tamanho da fonte menor
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(window.getSize().x - 150, 20); // Posição do texto na caixa
    
    // Desenha a caixa e o texto
    window.draw(infoBox); // Desenha a caixa de informações
    window.draw(infoText); // Desenha o texto com munição e vida

    // Desenha a mensagem de Game Over se o jogo estiver terminado
   if (gameOver) {
        sf::RectangleShape darkOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        darkOverlay.setFillColor(sf::Color(75, 75, 75, 150)); // Cinza escuro com opacidade
        window.draw(darkOverlay);

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition((window.getSize().x - gameOverText.getLocalBounds().width) / 2,
                                 (window.getSize().y - gameOverText.getLocalBounds().height) / 2);
        window.draw(gameOverText);
    }

    window.display();
}