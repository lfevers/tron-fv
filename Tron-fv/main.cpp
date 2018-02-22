#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#define W 600
#define H 480
#define kVel 4
#define ancho_morro 20

int main()
{
    sf::Clock clock;
    
    int posx =W/2;
    int posy =H/2;
    
    int posr_x;
    int posr_y;
    
    int cord_morrox;
    int cord_morroy;
    
    int dirx = 0;
    int diry = -1;
    
    int mapa[W][H];
    for(int mx = 0; mx < W;mx++){
            for(int my = 0; my < H;my++){
                mapa[mx][my] = 0;
            }
    }
    
    sf::RectangleShape mapa_rastro[W/4][H/4];
    for(int mx = 0; mx < W/4;mx++){
            for(int my = 0; my < H/4;my++){
                mapa_rastro[mx][my] = sf::RectangleShape(sf::Vector2f(4, 4));
                mapa_rastro[mx][my].setFillColor(sf::Color::Cyan);
                mapa_rastro[mx][my].setOrigin(2,2);
                mapa_rastro[mx][my].setPosition(mx*4,my*4);
            }
    }
    
    
    //MORRO
    sf::RectangleShape morro = sf::RectangleShape(sf::Vector2f(ancho_morro, 1));
    morro.setOrigin(ancho_morro/2,1);
    morro.setFillColor(sf::Color::Red);
    
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(W, H), "T.R.O.N");
    
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprites-tron-sf2.png"))
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
        clock.restart();
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
                            if(dirx == -1 && diry == 0){}
                            else{
                                 sprite.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                                //Escala por defecto
                                sprite.setScale(1,1);
                                dirx = 1;
                                diry = 0;  
                            }
                        break;

                        case sf::Keyboard::Left:
                            if(dirx == 1 && diry == 0){}
                            else{
                                sprite.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                                sprite.setScale(-1,1);
                                dirx = -1;
                                diry = 0;
                            }
                            //Reflejo vertical
                            
                        break;
                        
                        case sf::Keyboard::Up:
                            if(dirx == 0 && diry == 1){}
                            else{
                                sprite.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                                dirx = 0;
                                diry = -1; 
                            }
                            
                        break;
                        
                        case sf::Keyboard::Down:
                            if(dirx == 0 && diry == -1){}
                            else{
                                sprite.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                                sprite.setScale(1,-1);
                                dirx = 0;
                                diry = 1;  
                            }
                            
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
        
        
        
        
        
        
        
        posx = posx + kVel * dirx;
        posy = posy + kVel * diry;

        if(posx < 0){ posx = W; }
        if(posx > W){ posx = 0; }
        if(posy < 0){ posy = H; }
        if(posy > H){ posy = 0; }
        
        sprite.setPosition(posx,posy);
        
        if(dirx == 1){//derecha
           cord_morrox = posx+16; 
           cord_morroy = posy;
           morro.setOrigin(1,ancho_morro/2);
           morro.setSize(sf::Vector2f(1, ancho_morro));
           morro.setPosition(cord_morrox,cord_morroy);
          
           
        }
        if(dirx == -1){//izquierda
           cord_morrox = posx-16; 
           cord_morroy = posy;
           morro.setOrigin(1,ancho_morro/2);
           morro.setSize(sf::Vector2f(1, ancho_morro));
           morro.setPosition(cord_morrox,cord_morroy);
           
           
        }
        if(diry == 1){//abajo
           cord_morrox = posx; 
           cord_morroy = posy +16;
           morro.setOrigin(ancho_morro/2,1);
           morro.setSize(sf::Vector2f(ancho_morro, 1));
           morro.setPosition(cord_morrox,cord_morroy);
           
        }
        if(diry == -1){//arriba
           cord_morrox = posx; 
           cord_morroy = posy -16;
           morro.setOrigin(ancho_morro/2,1);
           morro.setSize(sf::Vector2f(ancho_morro, 1));
           morro.setPosition(cord_morrox,cord_morroy);   
        }
        
        
        
        
        mapa[posx][posy] = 1;
        
        
        window.clear();
        window.draw(s_background);
        
        
         for(int mx = 0; mx < W;mx++){
            for(int my = 0; my < H;my++){
                if(mapa[mx][my] == 1){
                    
                    if(morro.getGlobalBounds().intersects(mapa_rastro[mx/4][my/4].getGlobalBounds())){
                        std::cout << "HAS PERDIDO :( \n" ;
                        window.close();
                        break;
                    }
                    window.draw(mapa_rastro[mx/4][my/4]);
                }
            }
        }
         
        
        window.draw(sprite);
        //window.draw(morro); VER COLISIONADOR DEL COCHE
        window.display();
        
        sf::Time tiempo = sf::milliseconds(0);
        sf::Time tiempo_max = sf::milliseconds(30);
        while (tiempo < tiempo_max){
            tiempo = clock.getElapsedTime();
        }
       
    }
    
    return 0;
}