#include <iostream>
#include <SFML/Graphics.hpp>

#define kVel 0

int main()
{
    float posx =300;
    float posy =240;
    
    int dirx = 0;
    int diry = 1;
    
    int mapa[600][480];
    for(int mx = 0; mx < 600;mx++){
            for(int my = 0; my < 480;my++){
                mapa[mx][my] = 0;
            }
    }
    
    
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(600, 480), "T.R.O.N");
    
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprites-tron-sf.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    sf::Texture tex2;
    tex2.loadFromFile("resources/background.jpg");
    
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    sf::Sprite s_background(tex2);
    
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(32/2,32/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(posx, posy);
    

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
                            sprite.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                            //Escala por defecto
                            sprite.setScale(1,1);
                            dirx = 1;
                            diry = 0;
                        break;

                        case sf::Keyboard::Left:
                            sprite.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                            //Reflejo vertical
                            sprite.setScale(-1,1);
                            dirx = -1;
                            diry = 0;
                        break;
                        
                        case sf::Keyboard::Up:
                            sprite.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                            dirx = 0;
                            diry = -1; 
                        break;
                        
                        case sf::Keyboard::Down:
                            sprite.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                            sprite.setScale(1,-1);
                            dirx = 0;
                            diry = 1;  
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
        mapa[(int)posx][(int)posy] = 1;
        mapa[(int)posx][(int)posy] = 1;
        
        
        posx = posx + kVel * dirx;
        posy = posy + kVel * diry;
        
        if(posx < 0){ posx = 600; }
        if(posx > 600){ posx = 0; }
        if(posy < 0){ posy = 480; }
        if(posy > 480){ posy = 0; }
        
        sprite.setPosition(posx,posy);

        window.clear();
        window.draw(s_background);
        
        
         for(int mx = 0; mx < 600;mx++){
            for(int my = 0; my < 480;my++){
                if(mapa[mx][my] == 1){
                    //window.draw(mapa_rastro[mx][my]);
                }
            }
        }
         
        
        window.draw(sprite);  
        window.display();
    }

    return 0;
}