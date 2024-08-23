#ifndef INIMIGO_TANQUE_HPP
#define INIMIGO_TANQUE_HPP

#include "inimigo.h"

class InimigoTanque : public Inimigo {
private:
    // Sobrescreve a função da classe base
    virtual void fire(const sf::Vector2f& targetPosition, bool audioEnabled) override;

public:
    InimigoTanque(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const sf::RenderWindow* win, TextureManager& textureManager);
};

#endif

