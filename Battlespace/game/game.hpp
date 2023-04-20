#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using std::cin;
using std::cout;

/*
#include </home/vboxuser/Downloads/Battlespace/mobs/alien.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/bullet.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/ship.hpp>
#include </home/vboxuser/Downloads/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/spawner.hpp>
*/


#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/alien.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/bullet.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/ship.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/spawner.hpp>

//Para comprobar que hay colision entre la bala y alien
bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

//para comprobar que alguna bala colisiono con alguna nave y
bool collision(std::vector<Bullet>& bullets, std::vector<Alien>& aliens) {
    for(int i=0;i < bullets.size();i++){
        for (int j = 0; j < aliens.size(); j++) {
            if (CheckCollision(bullets[i].getRect(),aliens[j].getRect())) { 
                int damage=bullets[i].dmg;
                bullets.erase(bullets.begin()+i);
                aliens[j].health -= damage;
                if(aliens[j].health <= 0){
                aliens.erase(aliens.begin()+j);
                return true;
                }
                return true;
            }
        }
        }
    return false;
}



//int main(int argc, char* args[]) {
void game(int n){

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Battlespace", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;
    bool quit = false;
    
    Ship ship(renderer, "sprites/ship.png", 50, SCREEN_HEIGHT / 2 - 32);
    std::vector<Bullet> bullets;
    std::vector<Alien> aliens;
    
    int lista[n];
    int bullets_count = 0;
    int refract = 1;

    int d =1; //variable de la dificultad por ahora
    //Para llamar a la funcion bullets y crear la lista de balas(EL numero varia segun la dificultad)
    node *BulletsList= nullptr;
    BulletsList=createBullets(20/d,BulletsList,d);
    // Para crear la Lista de RecoveryList, las balas recuperadas
    // Se necesita el nullprt para que la primer bala recuperada se guarde correctamente
    node *RecoveryList= nullptr;
    //Se necesita el = para que una vez que entre por primera vez se pueda guardar globalmente +la variable y no siga entrando a cambiar la primera posicion de balas recuperdas
    RecoveryList=RecoveryBullets(0,RecoveryList,d);

   for (int i = 0; i < n; i++) {
        int randomy = rand() % 447 + 2; // Genera un número aleatorio entre 1 y 100
        lista[i] = randomy;
        aliens.emplace_back(renderer, SCREEN_WIDTH+(i*15), lista[i]);
    }
    
    bool replay=false;
    Uint32 lastAlienTime= SDL_GetTicks();
       using namespace LibSerial ;

    // Instantiate a Serial Port and a Serial Stream object.
             SerialPort serial_port;
             SerialStream serial_stream;

    try
    {
        // Abrir el puerto para el Serial_Stream donde esta conectado el arduino
        serial_stream.Open("/dev/ttyUSB0") ;
    }
    catch (const OpenFailed&)
    {
        std::cerr << "The serial port did not open correctly." << std::endl ;
    }
serial_stream.SetBaudRate(LibSerial::BaudRate::BAUD_9600);
serial_stream.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
serial_stream.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);

// Variables para almacenar los datos recibidos
    int lecturaX, lecturaY, bt, lecturaPot;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            ship.moveUp();
                            if(bullets_count < n*200 && bullets.size()<refract){
                                bullets_count++;
                                //shotBullet(BulletsList);
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32);
                            }
                            break;
                       case SDLK_DOWN:
                            ship.moveDown();
                            if(bullets_count < n*200 && bullets.size()<refract){
                                bullets_count++;
                                //shotBullet(BulletsList);
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32);
                            }
                            break;
                         case SDLK_LEFT:
                            if(refract>=2){
                                refract-=1;
                                }
                            break;
                        case SDLK_RIGHT:
                            refract+=1;
                            break;
                        break;
                    }
            }
        }
        // Leer los datos desde Arduino
        std::string data;
        std::getline(serial_stream, data);

        // Analizar los datos recibidos
        sscanf(data.c_str(), "%d,%d,%d,%d", &lecturaX, &lecturaY, &bt, &lecturaPot);

        // Imprimir los datos recibidos
        /*
        std::cout << "LecturaX: " << lecturaX << std::endl;
        std::cout << "LecturaY: " << lecturaY << std::endl;
        std::cout << "BT: " << bt << std::endl;
        std::cout << "LecturaPot: " << lecturaPot << std::endl;
        */
        // Enviar datos a Arduino para encender el siete segmentos, buzzer y led
        int sieteSegmentos = 0;
        int buzzer = 0;
        int led = 0;
        serial_stream << sieteSegmentos << "," << buzzer << "," << led << std::endl;
        // Esperar un tiempo antes de leer los datos de nuevo
        //SDL_Delay(50);
        //Movimiento de la nave con el arduino
        if(lecturaY>600){ship.moveUp();}else if(lecturaY<400){ship.moveDown();}else{}
        //Disparo con el arduino
        if(bt==0){if(bullets_count < n*200 && bullets.size()<refract){
                                bullets_count++;
                                //shotBullet(BulletsList);
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32);}else{serial_stream << sieteSegmentos << "," << buzzer << "," << led << std::endl;}
        }
        //Velocidad de disparo con el arduino, en progreso
        //if(){}

        //alienGenerator(n,lastAlienTime,aliens);
        if(n==15 && SDL_GetTicks() - lastAlienTime >= n*35){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
            }
        }else if(n==25 && SDL_GetTicks() - lastAlienTime >= n*25){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
            }
        }else if(n==35 && SDL_GetTicks() - lastAlienTime >= n*15){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
            }
        }

        SDL_RenderClear(renderer);
        ship.draw(renderer);

        for(auto& alien : aliens){
            int enemy=0;
            if(enemy ==0){
            alien.draw(renderer);
            enemy++;
            }
        }


        //creacion de balas,movimiento,colision con alines y eliminacion de bala o recuperacion
        for (auto& bullet : bullets) {
            bullet.move();
            bullet.draw(renderer);
            //verifica si una bala colisiono con un alien
                for (auto& alien : aliens) {
                    /**/
                    if (collision(bullets, aliens)) {
                        int buzzer=1;
                        serial_stream << sieteSegmentos << "," << buzzer << "," << led << std::endl;
                    }
                    }
                    if(bullet.isOffScreen()){
                    //RecoveryBullets(bullet.dmg,RecoveryList,d);
                    //bullets.erase(bullets.begin());
                    //addBullets(BulletsList,RecoveryList);
        }
        }
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
            return bullet.getRecty()<0;
        }), bullets.end());



        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
    //return 0;
}

#endif
