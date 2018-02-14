/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: pato-lt
 *
 * Created on 14 de febrero de 2018, 12:45
 */

#ifndef PLAYER_H
#define PLAYER_H

class Player{
    private:
        int x;
        int y;
        sf::Sprite sprite;
        sf::Color color;
    public:
        Player(char []);
        void movimiento_automatico();
        void movimiento_controlado();
        sf::Sprite getSprite();
};

Player::Player(char *r_textura, sf::Color _color, int nx_sprite , int ny_sprite){
    x = rand() % W;
    y = rand() % H;
    color = _color;
    
    sf::Texture tex;
    if (!tex.loadFromFile(*r_textura))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    sprite(tex);
    sprite.setOrigin(32/2,32/2);
    sprite.setTextureRect(sf::IntRect(nx_sprite*32,ny_sprite*32,32,32));
    sprite.setPosition(x,y);
}

Player::movimiento_controlado(sf::Event event,sf::RenderWindow window){
//Verifico si se pulsa alguna tecla de movimiento
    switch(event.key.code) {
                        
        //Mapeo del cursor
        case sf::Keyboard::Right:
            sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
            //Escala por defecto
            sprite.setScale(1,1);
            sprite.move(kVel,0);
        break;

        case sf::Keyboard::Left:
            sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
            //Reflejo vertical
            sprite.setScale(-1,1);
            sprite.move(-kVel,0); 
        break;
                        
        case sf::Keyboard::Up:
            sprite.setTextureRect(sf::IntRect(0*75, 3*75, 75, 75));
            sprite.move(0,-kVel); 
        break;
                        
        case sf::Keyboard::Down:
            sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
            sprite.move(0,kVel); 
        break;
                        
                        
        //Tecla ESC para salir
        case sf::Keyboard::Escape:
            window.close();
        break;
                        
        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
            std::cout << event.key.code << std::endl;
        break;                  
    }
}

Player::getSprite(){
    return sprite;
}

#endif /* PLAYER_H */

