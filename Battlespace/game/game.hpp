#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;

#include </home/vboxuser/Downloads/Battlespace/mobs/alien.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/bullet.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/ship.hpp>
#include </home/vboxuser/Downloads/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>

/*#include "/home/nacho/Proyecto-I-Battlespace/LinkedList_P1_Bullets/Bullets.cpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/ship.hpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/bullet.hpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/alien.hpp"*/

int strike = 0;

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
                strike++;
                return true;
                }
                return true;
            }
        }
        }
    return false;
}


void game(int n){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Battlespace", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    bool quit,replay = false;
    Uint32 lastAlienTime= SDL_GetTicks();
    
    Ship ship(renderer, "sprites/ship.png", 50, SCREEN_HEIGHT / 2 - 32);
    std::vector<Bullet> bullets;
    std::vector<Alien> aliens;
    
    int refract, d =1; //variable de la dificultad por ahora
    int bullets_count = 0;

    int array[2];
    array[0] = n;
    array[1] = bullets_count;

    int lista[array[0]];

    //Para llamar a la funcion bullets y crear la lista de balas(EL numero varia segun la dificultad)
    node *BulletsList= nullptr;
    BulletsList=createBullets(20/d,BulletsList,d);
    // Para crear la Lista de RecoveryList, las balas recuperadas
    // Se necesita el nullprt para que la primer bala recuperada se guarde correctamente
    node *RecoveryList= nullptr;
    //Se necesita el = para que una vez que entre por primera vez se pueda guardar globalmente +la variable y no siga entrando a cambiar la primera posicion de balas recuperdas
    RecoveryList=RecoveryBullets(0,RecoveryList,d);

   for (int i = 0; i < array[0]; i++) {
        int randomy = rand() % 427 + 2; // Genera un número aleatorio entre 1 y 100
        lista[i] = randomy;
        aliens.emplace_back(renderer, SCREEN_WIDTH+(i*15), lista[i]);
    }

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
                            if(array[1] < array[0]*200 && bullets.size()<refract){
                                array[1]++;
                                //shotBullet(BulletsList);
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32);
                            }
                            break;
                       case SDLK_DOWN:
                            ship.moveDown();
                            if(array[1] < array[0]*200 && bullets.size()<refract){
                                array[1]++;
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
        if(array[0]==35 && SDL_GetTicks() - lastAlienTime >= array[0]*35){
            lastAlienTime = SDL_GetTicks();
            for(int i = 0; i < 5 && i < aliens.size(); i++){//oleada 1
                    aliens[i].move();
                }
            if(array[1]>1){
                for(int i = 5; i < 10 && i < aliens.size(); i++){//oleada 2
                    aliens[i].move();
                }
                if(array[1]>2){
                    for(int i = 10; i < 15 && i < aliens.size(); i++){//oleada 3
                        aliens[i].move();
                    }
                    if(strike<1){
                        quit=true;
                    }
                    if(array[1]>3){
                        for(int i = 15; i < 20 && i < aliens.size(); i++){//oleada 4
                            aliens[i].move();
                        }
                        if(strike<3){
                        quit=true;
                    }
                        if(array[1]>4){
                            for(int i = 20; i < 25 && i < aliens.size(); i++){//oleada 5
                                aliens[i].move();
                            }
                            if(strike<5){
                                quit=true;
                            }
                        }
                    }
                }
            }
        }else if(array[0]==45 && SDL_GetTicks() - lastAlienTime >= array[0]*25){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
            }
        }else if(array[0]==55 && SDL_GetTicks() - lastAlienTime >= array[0]*15){
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
    
}

#endif
