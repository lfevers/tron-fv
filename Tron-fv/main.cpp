#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>

#define kVel 1
#define W 640
#define H 480

int main()
{
    float posx = W / 2;
    float posy = H / 2;
    
    int dirx = 0;
    int diry = 1;
    
    int mapa[W / 32][H / 32];
    
    for(int mx = 0; mx < W / 32 ;mx++){
            for(int my = 0; my < H / 32;my++){
                mapa[mx][my] = 0;
            }
    }
    
    
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
    sf::Sprite coche(tex);
    sf::Sprite s_background(tex2);
    
    //Le pongo el centroide donde corresponde
    coche.setOrigin(32/2,32/2);
    //Cojo el sprite que me interesa por defecto del sheet
    coche.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
    coche.setScale(1,-1);
    
    // Lo dispongo en el centro de la pantalla
    coche.setPosition(posx, posy);
    
    //sprites rastros
    sf::Sprite rastro[W/32][H/32];
//    
    for(int mx = 0; mx < W / 32 ;mx++){
           for(int my = 0; my < H / 32;my++){
               rastro[mx][my]= sf::Sprite(tex);
               rastro[mx][my].setOrigin(32/2,32/2);
               rastro[mx][my].setPosition(mx*32,my*32);
           }
   }
   
    
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
                            coche.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                            //Escala por defecto
                            coche.setScale(1,1);
                            dirx = 1;
                            diry = 0;
                        break;

                        case sf::Keyboard::Left:
                            coche.setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
                            //Reflejo vertical
                            coche.setScale(-1,1);
                            dirx = -1;
                            diry = 0;
                        break;
                        
                        case sf::Keyboard::Up:
                            coche.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                            dirx = 0;
                            diry = -1; 
                        break;
                        
                        case sf::Keyboard::Down:
                            coche.setTextureRect(sf::IntRect(0*32, 0*32, 32, 32));
                            coche.setScale(1,-1);
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
        
        std::cout << "posx: " << posx << "\n";
        std::cout << "posy: " << posy << "\n";
           
        //if (posx % 32 == 0 && posy % 32 == 0){
            if(dirx == 1 && diry == 0 || dirx == -1 && diry == 0 ){
                //derecha izquierda
                mapa[(int)posx / 32][(int)posy / 32] = 1;
                mapa[(int)posx / 32][(int)posy / 32] = 1;
            }
        
            if(dirx == 0 && diry == 1 || dirx == 0 && diry == -1 ){
                //arriba abajo
                mapa[(int)posx / 32][(int)posy / 32] = 2;
                mapa[(int)posx / 32][(int)posy / 32] = 2;
            }
        
        //}
        
        
        
        
        
        
        window.clear();
        window.draw(s_background);
        
        
         for(int mx = 0; mx < W/32;mx++){
            for(int my = 0; my < H/32;my++){
                if(mapa[mx][my] == 1){
                    //DERECHA IZQUIERDA
                    rastro[mx][my].setTextureRect(sf::IntRect(3*32,1*32,32,32));
                    window.draw(rastro[mx][my]);
                    
                    std::cout << "rastrox: " <<rastro[mx][my].getPosition().x<< "\n";
                    std::cout << "rastroy: " <<rastro[mx][my].getPosition().y<< "\n";
                    
                }
                if(mapa[mx][my] == 2){
//                    //ARRIBA ABAJO 
                    rastro[mx][my].setTextureRect(sf::IntRect(3*32,0*32,32,32));
                    window.draw(rastro[mx][my]);
                    std::cout << "rastrox: " <<rastro[mx][my].getPosition().x<< "\n";
                    std::cout << "rastroy: " <<rastro[mx][my].getPosition().y<< "\n";
                }
            }
        }
         
        posx = posx + kVel * dirx;
        posy = posy + kVel * diry;
        
        if(posx < 0){ posx = 600; }
        if(posx > 600){ posx = 0; }
        if(posy < 0){ posy = 480; }
        if(posy > 480){ posy = 0; }
        
        coche.setPosition(posx,posy);
        
        window.draw(coche);  
        window.display();
       
        std::cout << "-------------------------" << "\n"; 
        std::cout << "\n"; 
        
    }

    return 0;
}