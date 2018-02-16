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
#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player{
    private:
        int x;
        int y;
        sf::Sprite sprite;
        sf::Color color;
    public:
        Player(sf::Color, int, int);
        void movimiento_automatico();
        void movimiento_controlado(sf::Event *event,sf::RenderWindow *window);
        sf::Sprite getSprite();
};

Player::Player(sf::Color _color, int nx_sprite , int ny_sprite){
    x = rand() % W;
    y = rand() % H;
    color = _color;
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprites-tron-sf.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    sprite = sf::Sprite(tex);
    sprite.setOrigin(32/2,32/2);
    sprite.setTextureRect(sf::IntRect(nx_sprite*32,ny_sprite*32,32,32));
    sprite.setPosition(x,y);
}

void Player::movimiento_controlado(sf::Event *event,sf::RenderWindow *window){
//Verifico si se pulsa alguna tecla de movimiento
    switch(*event->key.code) {
                        
        //Mapeo del cursor
        case sf::Keyboard::Right:
            sprite.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
            //Escala por defecto
            sprite.setScale(1,1);
            sprite.move(kVel,0);
        break;

        case sf::Keyboard::Left:
            sprite.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
            //Reflejo vertical
            sprite.setScale(-1,1);
            sprite.move(-kVel,0); 
        break;
                        
        case sf::Keyboard::Up:
            sprite.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
            sprite.move(0,-kVel); 
        break;
                        
        case sf::Keyboard::Down:
            sprite.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
            sprite.setScale(1,-1);
            sprite.move(0,kVel); 
        break;
                              
                        
        //Tecla ESC para salir
        case sf::Keyboard::Escape:
            *window->close();
        break;
                        
        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
            std::cout << *event->key.code << std::endl;
        break;                  
    }
}

sf::Sprite Player::getSprite(){
    return sprite;
}

#endif /* PLAYER_H */

