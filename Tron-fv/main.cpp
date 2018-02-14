#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>

#define kVel 5
const int W = 640;
const int H = 480;

#include "Player.h"




int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(W, H), "P0. Fundamentos de los Videojuegos. DCCIA");

    //Cargo la imagen donde reside la textura del sprite
    Player p1("sprites.png",sf::Color::Blue,0,0);
    

    //Bucle del juego
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    p1.movimiento_controlado(event,window);
                    break;              
                 
            }
            
        }
        
        window.clear();
        window.draw(p1.getSprite());
        window.display();
    }

    return 0;
}