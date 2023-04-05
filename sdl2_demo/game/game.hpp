#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
//#include "/home/vboxuser/projects/sdl2_demo/mobs/ship.hpp"
//#include "/home/vboxuser/projects/sdl2_demo/mobs/bullet.hpp"
//#include "/home/vboxuser/projects/sdl2_demo/mobs/alien.hpp"
//#include "/home/nacho/Proyecto-I-Battlespace/LinkedList_P1_Bullets/Bullets.cpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/ship.hpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/bullet.hpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/alien.hpp"

bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

bool collision(std::vector<Bullet>& bullets, std::vector<Alien>& aliens) {
    for(int i=0;i < bullets.size();i++){
        for (int j = 0; j < aliens.size(); j++) {
            if (CheckCollision(bullets[i].getRect(),aliens[j].getRect())) {
                printf("La bala golpeo un alien");
                cout<<"la bala golpeo un alien";
                bullets.erase(bullets.begin()+i);
                aliens.erase(aliens.begin()+j);
                return true;
            }
        }
        }
    return false;
}



//int main(int argc, char* args[]) {
void game(){
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
    int n=15;
    int lista[n];
    int bullets_count = 0;
    int refract = 1;

   for (int i = 0; i < n; i++) {
        int randomy = rand() % 447 + 2; // Genera un número aleatorio entre 1 y 100
        lista[i] = randomy;
        aliens.emplace_back(renderer, SCREEN_WIDTH+(i*15), lista[i]);
    }
    
    bool replay=false;
    Uint32 lastAlienTime= SDL_GetTicks();

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
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32);
                            }
                            break;
                       case SDLK_DOWN:
                            ship.moveDown();
                            if(bullets_count < n*200 && bullets.size()<refract){
                                bullets_count++;
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
        if(SDL_GetTicks() - lastAlienTime >= n*50){
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
                    printf("La bala golpeo un alien");
                    //bullets.erase(bullets.begin());
                    //aliens.erase(aliens.begin());
                    //alien.health -= bullet.dmg
                    }
                    }
                    if(bullet.isOffScreen()){
                    bullets.erase(bullets.begin());
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
