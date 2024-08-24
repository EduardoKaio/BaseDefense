#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

namespace Config {

    // Configurações da Janela
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    const sf::String WINDOW_TITLE = "Base Defense";
    const sf::Uint32 WINDOW_STYLE = sf::Style::Titlebar | sf::Style::Close;

    // Configurações do Jogo
    const float SPAWN_INTERVAL = 3.0f;
    const float TOTAL_TIME = 60.0f;
    const bool AUDIO_ENABLED = true;

    // Configurações do Player
    const float PLAYER_SPEED = 300.0f;
    const int PLAYER_HEALTH = 100;
    const int PLAYER_MAX_HEALTH = 100;
    const int PLAYER_MAX_AMMO = 70;
    const int PLAYER_PROJETEIS_DISPONIVEIS = 70;

    // Configurações do Inimigo
    const float ENEMY_SPEED = 30.0f;
    const int ENEMY_HEALTH = 3;

    // Configurações do Projetil do Inimigo
    const float PROJETIL_INIMIGO_SPEED = 50.0f;

    // Configurações do Projetil do Jogador
    const float PROJETIL_SPEED = 500.0f;

    // Configurações do Drop

    // Configurações da Base
    const int BASE_HEALTH = 100;

    const sf::Vector2f BASE_POSITION = {400, 300};

}

#endif // CONFIG_H