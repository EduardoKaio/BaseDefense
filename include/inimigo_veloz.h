#ifndef INIMIGO_VELOZ_HPP
#define INIMIGO_VELOZ_HPP

#include "inimigo.h"

class InimigoVeloz : public Inimigo {
private:
    virtual void fire(const sf::Vector2f& playerPosition, bool audioEnabled) override; // Sobrescrevendo o método fire

public:
    InimigoVeloz(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::RenderWindow* win, TextureManager& textureManager);
    // Outros métodos específicos para o InimigoVeloz, se necessário
};

#endif