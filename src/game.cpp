#include "../include/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream> 
#include <iomanip>
#include <random>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Base Defense", sf::Style::Titlebar | sf::Style::Close), 
    projeteis(),
    player(projeteis), 
    base(),
    spawnInterval(3.0f),
    gameOver(false),
    victory(false),
    gameStarted(false),
    audioEnabled(true),
    totalTime(60.0f),
    isShooting(false), // Exemplo: 1 minuto (60 segundos)
    remainingTime(totalTime),
    infoScreenActive(false) { // Adicione a variável gameStarted
    
    // Configura a janela e outros elementos iniciais
    window.setSize(sf::Vector2u(800, 600));
    window.setPosition(sf::Vector2i(100, 100));
    window.setVerticalSyncEnabled(true);

    // Ajuste a posição do jogador e base
    sf::Vector2f center(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    player.getSprite().setPosition(center);
    sf::Vector2f basePosition(window.getSize().x / 2.0f - base.getShape().getSize().x / 2.0f,
                            window.getSize().y / 2.0f - base.getShape().getSize().y / 2.0f);
    base.setPosition(basePosition);

    // if (!backgroundTexture.loadFromFile("../assets/images/black.png")) {
    //     std::cerr << "Não foi possível carregar background" << std::endl;
    // }
    
    // backgroundSprite.setTexture(backgroundTexture);

    // Carregar recursos de áudio
    if (!backgroundMusic.openFromFile("../assets/sounds/boss_battle_#2.WAV")) {
        std::cerr << "Não foi possível carregar a música de fundo!" << std::endl;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(10); 
    backgroundMusic.play();

    if (!heroShootBuffer.loadFromFile("../assets/sounds/sfx_laser1.ogg")) {
        std::cerr << "Não foi possível carregar o som do tiro do herói!" << std::endl;
    }
    heroShootSound.setBuffer(heroShootBuffer);

    std::string enemyShootSoundFile = "../awindow.draw(heroSprite);ssets/sounds/sfx_laser2.ogg";
    for (auto& inimigo : inimigos) {
        inimigo.loadEnemyShootSound(enemyShootSoundFile);
    }

    // Configura os botões
    if (!font.loadFromFile("../assets/fonts/oficial.ttf")) {
        std::cerr << "Não foi possível carregar a fonte!" << std::endl;
    }

    setupButton(startButton, startButtonText, "START", sf::Vector2f(window.getSize().x / 2.0f - 75, window.getSize().y / 2.0f - 25 + 20.0f));
    setupButton(infoButton, infoButtonText, "INFO", sf::Vector2f(window.getSize().x / 2.0f - 75, window.getSize().y / 2.0f - 25 + 80.0f));
    setupButton(backButton, backButtonText, "BACK", sf::Vector2f(window.getSize().x / 2.0f - 75, window.getSize().y / 2.0f - 25 + 190.0f));
    setupButton(restartButton, restartButtonText, "HOME", sf::Vector2f(window.getSize().x / 2.0f - 75, window.getSize().y / 2.0f + 40.0f));

    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 10);
    timerText.setCharacterSize(15);

    titleText.setFont(font);
    titleText.setString("Base Defense");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition((window.getSize().x - titleText.getLocalBounds().width) / 2, 150);
}

void Game::setupButton(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, const sf::Vector2f& position) {
    button.setSize(sf::Vector2f(150, 50));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(position);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    // Centraliza o texto dentro do botão
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(position.x + button.getSize().x / 2.0f, position.y + button.getSize().y / 2.0f);
}

void Game::run() {
    sf::Clock clock; 
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (gameStarted && !gameOver) {
            update(deltaTime.asSeconds());
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::M) {
                toggleAudio(!audioEnabled);
            } else if (event.key.code == sf::Keyboard::P) {
                if (gameStarted && !gameOver && !victory) {
                    gameStarted = false; // Pausa o jogo
                } else if (!gameStarted && !gameOver && !victory) {
                    gameStarted = true; // Retoma o jogo
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                // Adicione mensagens de debug para verificar as coordenadas
                // std::cout << "Mouse Position: " << mousePosF.x << ", " << mousePosF.y << std::endl;
                // std::cout << "Start Button Bounds: " << startButton.getGlobalBounds().left << ", " << startButton.getGlobalBounds().top << std::endl;
                // std::cout << "Info Button Bounds: " << infoButton.getGlobalBounds().left << ", " << infoButton.getGlobalBounds().top << std::endl;
                // std::cout << "Back Button Bounds: " << backButton.getGlobalBounds().left << ", " << backButton.getGlobalBounds().top << std::endl;
                // std::cout << "Restart Button Bounds: " << restartButton.getGlobalBounds().left << ", " << restartButton.getGlobalBounds().top << std::endl;

                if (!gameStarted) {
                    if (startButton.getGlobalBounds().contains(mousePosF)) {
                        gameStarted = true;
                    } else if (infoButton.getGlobalBounds().contains(mousePosF)) {
                        infoScreenActive = true;
                    }
                } 
                if (gameOver || victory) {
                    if (restartButton.getGlobalBounds().contains(mousePosF)) {
                        resetGame();
                    }
                } else if (infoScreenActive) {
                    if (backButton.getGlobalBounds().contains(mousePosF)) {
                        infoScreenActive = false; // Volta para a tela inicial
                    }
                } else if (!isShooting && gameStarted) {
                    player.shoot(mousePosF);
                    if (audioEnabled && player.getProjeteisDisponiveis()>0) {
                        heroShootSound.play();
                    }
                    isShooting = true;
                }
                
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isShooting = false; // Permite que o jogador atire novamente após soltar o botão
            }
        }
    }
}

void Game::update(float deltaTime) {
     // Não atualize o jogo se a tela de "informações estiver ativa"
    
    if (gameOver || victory) return; // Não atualiza o jogo se estiver em game over ou vitória
    
    if (infoScreenActive) {
        // Atualização da tela de informações se necessário
        // Adicione qualquer lógica específica para a tela de informações aqui
        return;
    }
    if (remainingTime > 0) {
        remainingTime -= deltaTime;
        if (remainingTime < 0) {
            remainingTime = 0;
            victory = true; // O jogador vence quando o tempo acaba
        }
    }

    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0.0f;

        // Posições aleatórias nas bordas do mapa
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1);

        sf::Vector2f startPosition;
        sf::Vector2f playerPosition = player.getSprite().getPosition() + sf::Vector2f(player.getSprite().getLocalBounds().width / 2, player.getSprite().getLocalBounds().height / 2);

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

    // Atualiza os inimigos e remove os que não estão mais vivos
    for (auto it = inimigos.begin(); it != inimigos.end();) {
        it->update(deltaTime, player.getSprite().getPosition(), audioEnabled);

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
                                enemyIt->getSprite().getPosition().x, enemyIt->getSprite().getPosition().y, enemyIt->getSprite().getLocalBounds().width / 2)) {
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

            // Verifica colisões com o jogador
            if (player.isAliveStatus() && projIt->isActive() &&
                projIt->iscolliding(projIt->getShape().getPosition().x, projIt->getShape().getPosition().y, projIt->getShape().getRadius(),
                                    player.getSprite().getPosition().x, player.getSprite().getPosition().y, player.getSprite().getLocalBounds().width / 2)) {
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

    std::ostringstream timeStream;
    int minutes = static_cast<int>(remainingTime) / 60;
    int seconds = static_cast<int>(remainingTime) % 60;
    timeStream << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    timerText.setString(timeStream.str());
}



void Game::render() {
    sf::Vector2u windowSize = window.getSize();
    // sf::Vector2u textureSize = backgroundTexture.getSize();
    // float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    // float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    // backgroundSprite.setScale(scaleX, scaleY);

    window.clear(); // Limpa a janela com a cor padrão
    // window.draw(backgroundSprite); // Desenha o fundo
    sf::RectangleShape galaxyBackground(sf::Vector2f(window.getSize().x, window.getSize().y));
    galaxyBackground.setFillColor(sf::Color::Black);
    window.draw(galaxyBackground);

    // Adiciona estrelas ou efeitos de nebulosa
    sf::CircleShape star(0.5);
        star.setFillColor(sf::Color::White);
        for (int i = 0; i < 5; ++i) {
            star.setPosition(rand() % windowSize.x, rand() % windowSize.y);
            window.draw(star);
        }

    if (infoScreenActive) { // Verifica se a tela de informações está ativa
        window.clear(); // Limpa a janela com a cor padrão
        sf::RectangleShape galaxyBackground(sf::Vector2f(window.getSize().x, window.getSize().y));
            galaxyBackground.setFillColor(sf::Color::Black);
            window.draw(galaxyBackground);

            // Adiciona estrelas ou efeitos de nebulosa
            sf::CircleShape star(0.5);
            star.setFillColor(sf::Color::White);
            for (int i = 0; i < 5; ++i) {
                star.setPosition(rand() % windowSize.x, rand() % windowSize.y);
                window.draw(star);
            }
        
        sf::Text infoText;
        sf::Text titleInfoText;

        titleInfoText.setFont(font);
        infoText.setFont(font);
        
        titleInfoText.setString("Informações do Jogo");
        titleInfoText.setCharacterSize(24);
        titleInfoText.setFillColor(sf::Color::White);
        titleInfoText.setPosition(window.getSize().x / 2.0f - 160, window.getSize().y / 2.0f - 260);

        infoText.setString("Objetivo do Jogo\n\n"
                           "Seu objetivo é proteger a base do ataque dos inimigos durante 1 minuto.\n"
                            "O jogo termina quando o herói é derrotado ou a base é destruída.\n\n"
                           "Como Jogar\n\n"
                           "Movimentação:\n"
                           "Use as teclas 'W', 'A', 'S' e 'D' para mover o herói para cima, esquerda, baixo\ne direita.\n\n"
                           "Atirar:\n"
                           "Clique com o botão esquerdo do mouse para disparar projéteis contra\nos inimigos.\n\n"
                           "Controle de Áudio:\n"
                           "Pressione a tecla 'M' para ativar ou desativar os sons do jogo.\n\n"
                           "Pausar o Jogo:\n"
                           "Pressione a tecla 'P' para pausar o jogo.\n\n");
        infoText.setCharacterSize(14);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(window.getSize().x / 2.0f - 360, window.getSize().y / 2.0f - 190);
        
        window.draw(titleInfoText);
        window.draw(infoText);
        window.draw(backButton);
        window.draw(backButtonText);

    } else {
        if (gameOver) {
            // Tela de Derrota
            sf::RectangleShape darkOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));
            darkOverlay.setFillColor(sf::Color(0, 0, 0, 180)); 
            window.draw(darkOverlay);

            // Cria um gradiente de vermelho para a tela de derrota
            sf::VertexArray gradient(sf::TrianglesStrip, 4);
            gradient[0].position = sf::Vector2f(0, 0);
            gradient[0].color = sf::Color(255, 0, 0, 150);
            gradient[1].position = sf::Vector2f(windowSize.x, 0);
            gradient[1].color = sf::Color(255, 0, 0, 150);
            gradient[2].position = sf::Vector2f(0, windowSize.y);
            gradient[2].color = sf::Color(150, 0, 0, 150);
            gradient[3].position = sf::Vector2f(windowSize.x, windowSize.y);
            gradient[3].color = sf::Color(150, 0, 0, 150);
            window.draw(gradient);

            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER");
            gameOverText.setCharacterSize(60);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setStyle(sf::Text::Bold);
            gameOverText.setPosition((window.getSize().x - gameOverText.getLocalBounds().width) / 2, 180);
            window.draw(gameOverText);

            window.draw(restartButton);
            window.draw(restartButtonText); // Certifique-se de desenhar o texto do botão
        } else if (victory) {
            // Tela de Vitória
            sf::RectangleShape darkOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));
            darkOverlay.setFillColor(sf::Color(0, 0, 0, 180)); 
            window.draw(darkOverlay);

            // Cria um gradiente de verde para a tela de vitória
            sf::VertexArray gradient(sf::TrianglesStrip, 4);
            gradient[0].position = sf::Vector2f(0, 0);
            gradient[0].color = sf::Color(0, 255, 0, 150);
            gradient[1].position = sf::Vector2f(windowSize.x, 0);
            gradient[1].color = sf::Color(0, 255, 0, 150);
            gradient[2].position = sf::Vector2f(0, windowSize.y);
            gradient[2].color = sf::Color(0, 200, 0, 150);
            gradient[3].position = sf::Vector2f(windowSize.x, windowSize.y);
            gradient[3].color = sf::Color(0, 200, 0, 150);
            window.draw(gradient);

            sf::Text victoryText;
            victoryText.setFont(font);
            victoryText.setString("YOU WIN!");
            victoryText.setCharacterSize(60);
            victoryText.setFillColor(sf::Color::White);
            victoryText.setStyle(sf::Text::Bold);
            victoryText.setPosition((window.getSize().x - victoryText.getLocalBounds().width) / 2, 180);
            window.draw(victoryText);

            window.draw(restartButton);
            window.draw(restartButtonText); // Certifique-se de desenhar o texto do botão
        } else if (!gameStarted) {
            sf::RectangleShape galaxyBackground(sf::Vector2f(window.getSize().x, window.getSize().y));
            galaxyBackground.setFillColor(sf::Color::Black);
            window.draw(galaxyBackground);

            // Adiciona estrelas ou efeitos de nebulosa
            sf::CircleShape star(0.5);
            star.setFillColor(sf::Color::White);
            for (int i = 0; i < 5; ++i) {
                star.setPosition(rand() % windowSize.x, rand() % windowSize.y);
                window.draw(star);
            }
            window.draw(titleText); // Desenha o texto do título
            window.draw(startButton);
            window.draw(startButtonText); // Certifique-se de desenhar o texto do botão
            window.draw(infoButton);
            window.draw(infoButtonText);
        } else {
            sf::RectangleShape galaxyBackground(sf::Vector2f(window.getSize().x, window.getSize().y));
            galaxyBackground.setFillColor(sf::Color::Black);
            window.draw(galaxyBackground);

            // Adiciona estrelas ou efeitos de nebulosa
            sf::CircleShape star(0.5);
            star.setFillColor(sf::Color::White);
            for (int i = 0; i < 10; ++i) {
                star.setPosition(rand() % windowSize.x, rand() % windowSize.y);
                window.draw(star);
            }
            window.draw(base); 
            window.draw(player.getSprite());
            player.setSize(0.5f, 0.5f);

            for (const auto& projetil : projeteis) {
                window.draw(projetil);
            }
            
            for (const auto& inimigo : inimigos) {
                window.draw(inimigo);
                for (const auto& projetil : inimigo.getProjeteis()) {
                    window.draw(projetil);
                }
            }

            sf::Text infoText;
            infoText.setFont(font);
            infoText.setString("Municao: " + std::to_string(player.getProjeteisDisponiveis()) + "\n" +
                            "Vida: " + std::to_string(player.getHealth()) + "\n" +
                            "Vida Base: " + std::to_string(base.getHealth()));
            infoText.setCharacterSize(15);
            infoText.setFillColor(sf::Color::White);
            infoText.setPosition(window.getSize().x - 150, 20);
            
            window.draw(infoText);
            window.draw(timerText);
        }
    }

    window.display();
}


void Game::resetGame() {
    // Resetar estado do jogo
    resetTimer();
    gameOver = false;
    victory = false; // Resetar o estado de vitória
    gameStarted = false;

    player.reset();
    base.reset();
    window.draw(player.getSprite());
    projeteis.clear();
    inimigos.clear();
}

void Game::toggleAudio(bool enable) {
    audioEnabled = enable;
    backgroundMusic.setVolume(audioEnabled ? 10 : 0);
    if (audioEnabled) {
        backgroundMusic.play();
    } else {
        backgroundMusic.pause();
    }
    
    // Ajuste o volume dos sons de tiro
    heroShootSound.setVolume(audioEnabled ? 100 : 0);
    enemyShootSound.setVolume(audioEnabled ? 100 : 0);

    // Atualize o estado de áudio dos inimigos
}
void Game::resetTimer() {
    remainingTime = totalTime;
}
