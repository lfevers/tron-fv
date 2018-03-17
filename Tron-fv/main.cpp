#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <sstream> 

#define W 600
#define H 480
#define kVel 4
#define ancho_morro 10
#define largo_morro 14

#include "Coche.h"

int main()
{
    // Creamos el texto que muestra la puntuacion
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text time("Tiempo: " ,font);
    time.setCharacterSize(20);
    time.setStyle(sf::Text::Bold);
    time.setColor(sf::Color::Red);
    time.setPosition(5,10);
    
    sf::Text tiempo_acumulado("0" ,font);
    tiempo_acumulado.setCharacterSize(20);
    tiempo_acumulado.setStyle(sf::Text::Bold);
    tiempo_acumulado.setColor(sf::Color::Red);
    tiempo_acumulado.setPosition(90,10);
    
    sf::Clock clock;
    sf::Clock clock_total;
    
    //DECLARAMOS LOS COCHES
    Coche coche1 = Coche(0);
    Coche coche2 = Coche(1);
    
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
                mapa_rastro[mx][my].setOrigin(2,2);
                mapa_rastro[mx][my].setPosition(mx*4,my*4);
            }
    }
    
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(W, H), "T.R.O.N");
    
    sf::Texture tex2;
    tex2.loadFromFile("resources/background.jpg");
    
    //Y creo el spritesheet a partir de la imagen anterior

    sf::Sprite s_background(tex2);

    //Bucle del juego
    while (window.isOpen())
    {
        std::stringstream ss;
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
                            if(coche1.get_dirx() == -1 && coche1.get_diry() == 0){}
                            else{
                                coche1.set_dir(1,0);
                                coche1.cambiar_posicion_sprite(1,1);
                            }
                        break;

                        case sf::Keyboard::Left:
                            if(coche1.get_dirx() == 1 && coche1.get_diry() == 0){}
                            else{
                                coche1.set_dir(-1,0);
                                coche1.cambiar_posicion_sprite(1,-1);
                            }
                            //Reflejo vertical
                            
                        break;
                        
                        case sf::Keyboard::Up:
                            if(coche1.get_dirx() == 0 && coche1.get_diry() == 1){}
                            else{
                                coche1.set_dir(0,-1);
                                coche1.cambiar_posicion_sprite(0,1);
                            }
                            
                        break;
                        
                        case sf::Keyboard::Down:
                            if(coche1.get_dirx() == 0 && coche1.get_diry() == -1){}
                            else{
                                coche1.set_dir(0,1); 
                                coche1.cambiar_posicion_sprite(0,-1);
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
        
        coche1.movimiento_controlado();
        coche1.situar_morro();
        
        coche2.movimiento_automatico(mapa);
        coche2.situar_morro();
        
        mapa[coche1.get_x()][coche1.get_y()] = 1;
        mapa[coche2.get_x()][coche2.get_y()] = 2;
        
        window.clear();
        window.draw(s_background);
        
        
         for(int mx = 0; mx < W;mx++){
            for(int my = 0; my < H;my++){
                if(mapa[mx][my] == 1){
                    
                    if(coche1.getMorro().getGlobalBounds().intersects(mapa_rastro[mx/4][my/4].getGlobalBounds())){
                        std::cout << "HAS PERDIDO :( \n" ;
                        window.close();
                        break;
                    }
                    
                    else if(coche2.getMorro().getGlobalBounds().intersects(mapa_rastro[mx/4][my/4].getGlobalBounds())){
                        std::cout << "HAS GANADO :) \n" ;
                        window.close();
                        break;
                    }
                    
                    else{
                        mapa_rastro[mx/4][my/4].setFillColor(coche1.getColor());
                        window.draw(mapa_rastro[mx/4][my/4]); 
                        //std::cout << "Pos rastro:" << mapa_rastro[mx/4][my/4].getPosition().x << "," << mapa_rastro[mx/4][my/4].getPosition().y << "\n";
                    }
                    
                }
                
                if(mapa[mx][my] == 2){
                    
                    if(coche2.getMorro().getGlobalBounds().intersects(mapa_rastro[mx/4][my/4].getGlobalBounds())){
                        std::cout << "HAS GANADO :) \n" ;
                        window.close();
                        break;
                    }
                    
                    else if(coche1.getMorro().getGlobalBounds().intersects(mapa_rastro[mx/4][my/4].getGlobalBounds())){
                        std::cout << "HAS PERDIDO :( \n" ;
                        window.close();
                        break;
                    }
                    else{
                        mapa_rastro[mx/4][my/4].setFillColor(coche2.getColor());
                        window.draw(mapa_rastro[mx/4][my/4]);
                    }
                }
                
            }
        }
         
        //sf::Sprite *sprite = coche1.getSprite(); 
        //window.draw(*sprite);
        
        window.draw(coche1.getSprite());
        //window.draw(coche1.getMorro()); //VER COLISIONADOR DEL COCHE
        
        window.draw(coche2.getSprite());
        //window.draw(coche2.getMorro()); //VER COLISIONADOR DEL COCHE
        
        sf::Time times = sf::seconds(0);
        times = clock_total.getElapsedTime();
        ss<<static_cast<int>(times.asSeconds());
        tiempo_acumulado.setString(ss.str());
        
        window.draw(time);
        window.draw(tiempo_acumulado);
        
        window.display();
        
        //std::cout << "----------------------- \n";
        
        sf::Time tiempo = sf::milliseconds(0);
        sf::Time tiempo_max = sf::milliseconds(30);
        while (tiempo < tiempo_max){
            tiempo = clock.getElapsedTime();
        }
       
    }
    
    return 0;
}

Coche::Coche(int _njugador){
    int dir_aux = 1;
    
    n_jugador = _njugador;
    
    morro = sf::RectangleShape(sf::Vector2f(ancho_morro, 1));
    morro.setOrigin(ancho_morro/2,0);
    morro.setFillColor(sf::Color::Red);
    
        
    //Cargo la imagen donde reside la textura del sprite
    if (!tex.loadFromFile("resources/sprites-tron-sf2.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sprite = sf::Sprite(tex);
    
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(32/2,32/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*32, n_jugador*32, 32, 32));
    
    if(n_jugador == 0){
        color = sf::Color::Cyan;
        posx =320;
        posy =440;
        dirx = 0;
        diry = -1;
        cord_morrox = posx;
        cord_morroy = posy -16;
    
    }
    else{
        color = sf::Color::Yellow;
        posx =320;
        posy =44;
        dirx = 0;
        diry = 1;
        cord_morrox = posx;
        cord_morroy = posy +16;
        dir_aux = -1;
    }
    
    
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(posx, posy);
    sprite.setScale(1,dir_aux); 
    
}


void Coche::cambiar_posicion_sprite(int _posicion, int _direccion){
    //_posicion     0 == UP/DOWN     1 == RIGHT/LEFT 
     
    //_direccion    1 == RIGHT/UP   -1 == LEFT/DOWN 
     
    sprite.setTextureRect(sf::IntRect(_posicion*32, n_jugador*32, 32, 32));
    
    if(_posicion == 0){ 
        sprite.setScale(1,_direccion); 
    } 
     
    if(_posicion == 1){ 
        sprite.setScale(_direccion,1); 
    } 
    //Escala por defecto 
     
}

void Coche::movimiento_controlado(){
    
        posx = posx + kVel * dirx;
        posy = posy + kVel * diry;

        if(posx < 0){ posx = W-4; }
        if(posx > W-1){ posx = 0; }
        if(posy < 0){ posy = H-4; }
        if(posy > H-1){ posy = 0; }
        
        sprite.setPosition(posx,posy);
}

void Coche::movimiento_automatico(int _mapa[W][H]){
    int pos_sx = posx + 20*dirx;
    int pos_sy = posy + 20*diry;
    
    if(pos_sx < 0){ pos_sx = W-pos_sx;}
    if(pos_sx > W-1){ pos_sx = 0 + (pos_sx - W); }
    if(pos_sy < 0){ pos_sy = H-pos_sx;}
    if(pos_sy > H-1){ pos_sy = 0 + (pos_sy - H); }
    
    if(_mapa[pos_sx][pos_sy] == 1 || _mapa[pos_sx][pos_sy] == 2){
        
        bool libres[4]; // 0 derecha // 1 izquierda // 2 abajo // 3 arriba
        for (int n = 0 ; n < 4; n++){
            libres[n] = true;
        }
        
        int pos_sx;
        int pos_sy;
        
        for(int p = 4; p <= 20; p = p+4){
            pos_sx = posx + p; 
            pos_sy = posy;
            
            if(pos_sx < 0){ pos_sx = W-p;}
            if(pos_sx > W-1){ pos_sx = 0 + (pos_sx - W); }
            if(pos_sy < 0){ pos_sy = H-p;}
            if(pos_sy > H-1){ pos_sy = 0 + (pos_sy - H); }
            
            if(_mapa[pos_sx][pos_sy] == 1 || _mapa[pos_sx][pos_sy] == 2){
                std::cout << "Derecha ocupada \n";
                libres[0] = false;
            } 
            
            pos_sx = posx - p; 
            pos_sy = posy;
            
            if(pos_sx < 0){ pos_sx = W-p;}
            if(pos_sx > W-1){ pos_sx = 0 + (pos_sx - W); }
            if(pos_sy < 0){ pos_sy = H-p;}
            if(pos_sy > H-1){ pos_sy = 0 + (pos_sy - H); }
            
            if(_mapa[pos_sx][pos_sy] == 1 || _mapa[posx - p][pos_sy] == 2){
                std::cout << "Izquierda ocupada \n";
                libres[1] = false;
            }
            
            pos_sx = posx; 
            pos_sy = posy + p;
            
            if(pos_sx < 0){ pos_sx = W-p;}
            if(pos_sx > W-1){ pos_sx = 0 + (pos_sx - W); }
            if(pos_sy < 0){ pos_sy = H-p;}
            if(pos_sy > H-1){ pos_sy = 0 + (pos_sy - H); }
            
            if(_mapa[pos_sx][pos_sy] == 1 || _mapa[pos_sx][pos_sy] == 2){
                std::cout << "Abajo ocupada \n";
                libres[2] = false;
            }
            
            pos_sx = posx; 
            pos_sy = posy - p;
            
            if(pos_sx < 0){ pos_sx = W-p;}
            if(pos_sx > W-1){ pos_sx = 0 + (pos_sx - W); }
            if(pos_sy < 0){ pos_sy = H-p;}
            if(pos_sy > H-1){ pos_sy = 0 + (pos_sy - H); }
                       
            if(_mapa[pos_sx][pos_sy] == 1 || _mapa[pos_sx][pos_sy] == 2){
                std::cout << "Arriba ocupada \n";
                libres[3] = false;
            }
        }
        
        for (int n2 = 0 ; n2 < 4 ; n2++){
            if(libres[n2] == true){
                std::cout << n2 << "\n";
                switch (n2){
                    case 0:
                        std::cout << "Derecha libre \n";
                        set_dir(1,0);
                        cambiar_posicion_sprite(1,1);
                        break;
                        
                    case 1:
                        std::cout << "Izquierda libre \n";
                        set_dir(-1,0);
                        cambiar_posicion_sprite(1,-1);
                        break;
                        
                    case 2:
                        std::cout << "Abajo libre \n";
                        set_dir(0,1);
                        cambiar_posicion_sprite(0,-1);
                        break;
                        
                    case 3:
                        std::cout << "Arriba libre \n";
                        set_dir(0,-1);
                        cambiar_posicion_sprite(0,1);
                        break;
                }
                
                break;
            }
        }
        
    }
    
    posx = posx + kVel * dirx;
    posy = posy + kVel * diry;
    
    if(posx < 0){ posx = W-4; }
    if(posx > W){ posx = 0; }
    if(posy < 0){ posy = H-4; }
    if(posy > H){ posy = 0; }
        
    sprite.setPosition(posx,posy);
    
    //std::cout << "Pos coche:" << posx << "," << posy << "\n";
}

void Coche::situar_morro(){
            
        if(dirx == 1){//derecha
           cord_morrox = posx+16; 
           cord_morroy = posy;
           morro.setOrigin(largo_morro,ancho_morro/2);
           morro.setSize(sf::Vector2f(largo_morro, ancho_morro));
           morro.setPosition(cord_morrox,cord_morroy);
          
           
        }
        if(dirx == -1){//izquierda
           cord_morrox = posx-16; 
           cord_morroy = posy;
           morro.setOrigin(0,ancho_morro/2);
           morro.setSize(sf::Vector2f(largo_morro, ancho_morro));
           morro.setPosition(cord_morrox,cord_morroy);
           
           
        }
        if(diry == 1){//abajo
           cord_morrox = posx; 
           cord_morroy = posy +16;
           morro.setOrigin(ancho_morro/2,largo_morro);
           morro.setSize(sf::Vector2f(ancho_morro, largo_morro));
           morro.setPosition(cord_morrox,cord_morroy);
           
        }
        if(diry == -1){//arriba
           cord_morrox = posx; 
           cord_morroy = posy -16;
           morro.setOrigin(ancho_morro/2,0);
           morro.setSize(sf::Vector2f(ancho_morro, largo_morro));
           morro.setPosition(cord_morrox,cord_morroy);   
        }
}

void Coche::set_dir(int _dirx, int _diry){
    dirx = _dirx;
    diry = _diry;
}

/*sf::Sprite* Coche::getSprite(){
    return &sprite;
}*/

sf::Sprite Coche::getSprite(){
    return sprite;
}

sf::RectangleShape Coche::getMorro(){
    return morro;
}

sf::Color Coche::getColor(){
    return color;
}

int Coche::get_dirx(){
    return dirx;
}

int Coche::get_diry(){
    return diry;
}

int Coche::get_x(){
    return posx;
}

int Coche::get_y(){
    return posy;
}