#ifndef PROJETIL_HPP
#define PROJETIL_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Projetil : public Drawable{
    
    private:
        CircleShape forma;
        Vector2f velocidade;
        virtual void draw(RenderTarget& target, RenderStates states) const override;
    public:
        Projetil(); 
        Projetil(Vector2f position, Vector2f direction);
        void update();
        void desenhar(RenderWindow& janela);
        FloatRect getBounds() const;
    };

#endif