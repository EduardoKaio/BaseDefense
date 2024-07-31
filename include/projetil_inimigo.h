#ifndef PROJETIL_INIMIGO_HPP
#define PROJETIL_INIMIGO_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class ProjetilInimigo : public Drawable {
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Vector2f position;
    Vector2f direction;
    float speed;
    CircleShape shape;

public:
    ProjetilInimigo(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition);
    
    void update(float deltaTime);
    bool isOutOfWindow(const sf::RenderWindow& window) const;
};

#endif // PROJETIL_INIMIGO_HPP