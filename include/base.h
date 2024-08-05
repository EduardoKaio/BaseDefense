#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Base : public Drawable {
private:
    // Sprite sprite;
    // Texture texture;
    // int health;
    // int maxHealth;
    RectangleShape shape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    

public:
    Base();
    void setPosition(const sf::Vector2f& position);

    // void update();
    // int getHealth() const;
    // void reduceHealth(int amount);
    // void regenerateHealth();
    // Vector2f getPosition() const; 

};

#endif