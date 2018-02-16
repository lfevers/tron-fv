#include <iostream>
#include <SFML/Graphics.hpp>


#define W 600
#define H 480
#define kVel 1

#include "Player.h"

int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(W, H), "T.R.O.N");
    
    //LLAMAR CONSTRUCTOR PLAYER
    Player p1(0,sf::Color::Cyan);
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex2;
    tex2.loadFromFile("resources/background.jpg");
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite s_background(tex2);

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
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            p1.cambiar_posicion_sprite(1,1);
                            p1.set_dir(1,0);
                        break;

                        case sf::Keyboard::Left:                      
                            p1.cambiar_posicion_sprite(1,-1);
                            p1.set_dir(-1,0);
                        break;
                        
                        case sf::Keyboard::Up:
                            p1.cambiar_posicion_sprite(0,1);
                            
                            p1.set_dir(0,-1);
                        break;
                        
                        case sf::Keyboard::Down:
                            p1.cambiar_posicion_sprite(0,-1);
                            p1.set_dir(0,1);
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
            
        }
        
        
        p1.movimiento_controlado();

        window.clear();
        window.draw(s_background);
        
        int mapa_rastro[W][H];
        for(int mx = 0; mx < W;mx++){
            for(int my = 0; my < H;my++){
                mapa_rastro[mx][my] = p1.getMapa_rastro(mx,my);
            }
        }
        
        for(int mx = 0; mx < W;mx++){
            for(int my = 0; my < H;my++){
                if(mapa_rastro[mx][my] == 1){
                    sf::CircleShape rastro(2.f);
                    rastro.setFillColor(sf::Color::Cyan);
                    rastro.setOrigin(2.f,2.f);
                    rastro.setPosition(mx,my);
                    window.draw(rastro);
                }
            }
        }
        
        window.draw(p1.getSprite());  
        window.display();
    }

    return 0;
}