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
        float posx;
        float posy;
        int dirx;
        int diry;
        int mapa_rastro[W][H];
        sf::Sprite sprite;
        sf::Color color;
    public:
        Player(int, sf::Color);
        void movimiento_automatico();
        void cambiar_posicion_sprite(int,int);
        void movimiento_controlado();
        void set_dir(int,int);
        int getMapa_rastro(int,int);
        sf::Sprite getSprite();
};

Player::Player(int _pos_sprite, sf::Color _color){
    
    posx =300;
    posy =240;
    dirx = 0;
    diry = 1;
    
    for(int mx = 0; mx < W;mx++){
            for(int my = 0; my < H;my++){
                mapa_rastro[mx][my] = 0;
            }
    }
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprites-tron-sf.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sprite = sf::Sprite(tex);
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(32/2,32/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*32, _pos_sprite*32, 32, 32));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(posx, posy);
    
    
}

void Player::cambiar_posicion_sprite(int _posicion, int _direccion){
    //_posicion     0 == UP/DOWN     1 == RIGHT/LEFT
    
    //_direccion    1 == RIGHT/UP   -1 == LEFT/DOWN
    
    sprite.setTextureRect(sf::IntRect(_posicion*32, 0*32, 32, 32));
    //Escala por defecto
    
    if(_posicion == 0){
        sprite.setScale(1,_direccion);
    }
    
    if(_posicion == 1){
        sprite.setScale(_direccion,1);
    }
    
}


void Player::movimiento_controlado(){
        mapa_rastro[(int)posx][(int)posy] = 1;
        mapa_rastro[(int)posx][(int)posy] = 1;
        
        posx = posx + kVel * dirx;
        posy = posy + kVel * diry;
        
        if(posx < 0){ posx = W; }
        if(posx > 600){ posx = 0; }
        if(posy < 0){ posy = H; }
        if(posy > 480){ posy = 0; }
        
        sprite.setPosition(posx,posy);
}

void Player::set_dir(int _dirx,int _diry){
    dirx = _dirx;
    diry = _diry;
}

int Player::getMapa_rastro(int _x, int _y){
    return mapa_rastro[_x][_y];
}

sf::Sprite Player::getSprite(){
    return sprite;
}

#endif /* PLAYER_H */

