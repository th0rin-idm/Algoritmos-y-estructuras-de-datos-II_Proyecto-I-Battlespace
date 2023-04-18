#ifndef game_hpp
#define game_hpp

//#include "/home/nacho/Proyecto-I-Battlespace/Battlespace/third-party/include/serial/serial.h"
#include "third-party/include/serial/serial.h"
//#include <Arduino.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
//#include "/home/nacho/Proyecto-I-Battlespace/Battlespace/third-party/Firmata-2.5.9/Firmata.h"

#include "controller.cpp"
using std::cin;
using std::cout;
/*
#include </home/vboxuser/Downloads/Battlespace/mobs/alien.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/bullet.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/ship.hpp>
#include </home/vboxuser/Downloads/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/spawner.hpp>
*/
/*
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/alien.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/bullet.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/ship.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/spawner.hpp>
*/
#include </home/nacho/Proyecto-I-Battlespace/Battlespace/mobs/alien.hpp>
#include </home/nacho/Proyecto-I-Battlespace/Battlespace/mobs/bullet.hpp>
#include </home/nacho/Proyecto-I-Battlespace/Battlespace/mobs/ship.hpp>
#include </home/nacho/Proyecto-I-Battlespace/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/nacho/Proyecto-I-Battlespace/Battlespace/mobs/spawner.hpp>
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

char data[128]; // Arreglo para almacenar los datos recibidos

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

    printf("puerto");
    serial::Serial my_serial("/dev/ttyUSB0",9600,serial::Timeout::simpleTimeout(3000));
    if(my_serial.isOpen()){
        std::cout<<"port opened succesfully"<<std::endl;
        printf("puerto abierto");
    }else{
        std::cout<<"port failed to open"<<std::endl;
        printf("fallo al abrir el puerto");
    }
    printf("puerto2");
    serial::Serial my_serial("/dev/ttyUSB0",9600,serial::Timeout::simpleTimeout(3000));
    if(my_serial.isOpen()){
        std::cout<<"port opened succesfully"<<std::endl;
        printf("puerto abierto");
    }else{
        std::cout<<"port failed to open"<<std::endl;
        printf("fallo al abrir el puerto");
    }
    my_serial.flushOutput();

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
        // Leer los datos del puerto serial
        //std::string;
        my_serial.flushInput();
        std::string data = my_serial.read(6);
        std::cout<<"Arduino:"<<data<<std::endl;
        printf("%d",data);

        // Analizar los datos recibidos
        int x = 0, y = 0, button = 0;
            // Utilizar los valores recibidos para controlar la nave
        if (y < 512) {
            // Mover la nave hacia arriba
            ship.moveUp();
        } else if (y > 512) {
            // Mover la nave hacia abajo
            ship.moveDown();
        }
        if (button == 0) {
            // Disparar la bala
            if(bullets_count < n*200 && bullets.size()<refract){
                                bullets_count++;
                                //shotBullet(BulletsList);
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32);
            }
        }

        

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
                    // La bala ha golpeado un alien
                    // Hacer algo aquí, como reducir la vida del alien, etc.
                    printf("La bala golpeo un alien111");
                    //bullets.erase(bullets.begin());
                    //aliens.erase(aliens.begin());
                    //alien.health -= bullet.dmg
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
