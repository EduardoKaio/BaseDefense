#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <list>
#include "projetil.h"

using namespace std;
using namespace sf;


class Player : public Drawable {
    private:
        Sprite sprite; // usado para representar visualmente o jogador no jogo.
        Texture texture; 
        
        /*
        armazena a imagem que será associada ao sprite. O sprite usa essa textura 
        para desenhar a imagem na tela. Geralmente, você carrega uma imagem em uma 
        texture a partir de um arquivo e depois atribui essa texture ao sprite.
        */
        
        float speed;
        int health;
        list<Projetil>& projeteis; // Referência para a lista de projéteis no jogo

        virtual void draw(RenderTarget& target, RenderStates states) const override;

    public:
        Player();
        Player(list<Projetil>& projeteis);
        void handleInput();
        void update();
        void draw(RenderWindow& window);
        void shoot(Vector2f target);
        int getHealth() const;
        void reduceHealth(int amount);
};

#endif