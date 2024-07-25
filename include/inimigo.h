#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Inimigo : public Drawable{

    private:
        Sprite sprite;
        float speed = 50.0f; 
        virtual void draw(RenderTarget& target, RenderStates states) const override;

    public:
        Inimigo(Texture& texture, float x, float y);
        
        void update(float deltaTime, const Vector2f& targetPosition);
        void draw(RenderWindow& window);
        Vector2f getPosition() const;

};

#endif
