/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Coche.h
 * Author: pato-pc
 *
 * Created on 22 de febrero de 2018, 19:33
 */

#ifndef COCHE_H
#define COCHE_H

class Coche{
private:
    int n_jugador;
    sf::Texture tex;
    sf::Sprite sprite;
    int posx;
    int posy;
    sf::RectangleShape morro;
    int cord_morrox;
    int cord_morroy;
    int dirx;
    int diry;
    sf::Color color;
    
public:
    Coche(int);
    void restart(int);
    void cambiar_posicion_sprite(int,int);
    void movimiento_controlado();
    void movimiento_automatico(int[W][H]);
    void situar_morro();
    void set_dir(int,int);
    //sf::Sprite* getSprite();
    sf::Sprite getSprite();
    sf::RectangleShape getMorro();
    sf::Color getColor();
    int get_dirx();
    int get_diry();
    int get_x();
    int get_y();
};


#endif /* COCHE_H */

