#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Base : public Drawable {
private:
    Sprite sprite;
    Texture texture;
    int health;
    int maxHealth;
    virtual void draw(RenderTarget& target, RenderStates states) const override;

public:
    Base();
    void update();
    int getHealth() const;
    void reduceHealth(int amount);
    void regenerateHealth();
    Vector2f getPosition() const; 

};

#endif