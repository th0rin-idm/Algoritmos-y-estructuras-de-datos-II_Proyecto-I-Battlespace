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
#include </home/vboxuser/Downloads/Battlespace/mobs/spawner.hpp>


#include </home/vboxuser/Downloads/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/vboxuser/Downloads/Battlespace/game/collisions.hpp>

/*#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/alien.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/bullet.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/ship.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/oleadas.hpp>

#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/game/collisions.hpp>
*/

void game(int n){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Battlespace", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;
    
    Ship ship(renderer, "sprites/ship.png", 50, SCREEN_HEIGHT / 2 - 32);
    std::vector<Bullet> bullets;
    std::vector<Alien> aliens;
    
    int bullets_count = 0;
    int refract,d = 1; //dificultad= d
    bool quit,replay = false;
    Uint32 lastAlienTime= SDL_GetTicks();

    int array[3];
    array[0] = n;
    array[1] = bullets_count;
    array[2] = 0;

    // Se necesita el nullprt para que la primer bala recuperada se guarde correctamente
    node *BulletsList= nullptr;
    node *RecoveryList= nullptr;//crear RecoveryList, las balas recuperadas

    //llamar funcion bullets y crear BulletsList(numero varia segun dificultad)
    BulletsList=createBullets(20/d,BulletsList,d);
    //Se necesita el = para que una vez que entre por primera vez se pueda guardar globalmente +la variable y no siga entrando a cambiar la primera posicion de balas recuperdas
    RecoveryList=RecoveryBullets(0,RecoveryList,d);

    int lista[n];
    for (int i = 0; i < array[0]; i++) {
        int randomy = rand() % 437 + 2; // Genera un número aleatorio entre 1 y 100
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
        
        /*if(array[0]==35 && SDL_GetTicks() - lastAlienTime >= array[0]*35){
            lastAlienTime = SDL_GetTicks();
            //aliencreator(aliens,array[1],array[2]);
            if(array[1]>=array[2] && array[2]<5){
                aliencreator(aliens,array[1],array[2]);
                array[2]++;
            }        
        }*/
        if(n==35 && SDL_GetTicks() - lastAlienTime >= n*15){
                lastAlienTime = SDL_GetTicks();
                for(int i = 0; i < 5 && i < aliens.size(); i++){//oleada 1
                    aliens[i].move();
                }
                if(bullets_count>3){ 
                    for(int i = 4; i < 10 && i < aliens.size(); i++){//oleada 2
                        aliens[i].move();
                    }if(bullets_count>6){ 
                        for(int i = 9; i < 15 && i < aliens.size(); i++){//oleada 2
                            aliens[i].move();
                        }if(bullets_count>9){ 
                            for(int i = 14; i < 20 && i < aliens.size(); i++){//oleada 2
                                aliens[i].move();
                            }if(bullets_count>12){ 
                                for(int i = 19; i < 25 && i < aliens.size(); i++){//oleada 2
                                    aliens[i].move();
                                }
                            }
                        }
                    }
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
