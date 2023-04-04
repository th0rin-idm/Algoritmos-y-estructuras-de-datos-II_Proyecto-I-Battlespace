#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
//#include "/home/vboxuser/projects/sdl2_demo/mobs/ship.hpp"
//#include "/home/vboxuser/projects/sdl2_demo/mobs/bullet.hpp"
//#include "/home/vboxuser/projects/sdl2_demo/mobs/alien.hpp"

#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/ship.hpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/bullet.hpp"
#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/alien.hpp"

bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
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
    for (int i = 0; i < 20; i++) {
        aliens.emplace_back(renderer, SCREEN_WIDTH + (i * 100), SCREEN_HEIGHT / 3 - 32);
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
                            bullets.emplace_back(renderer, 
                                ship.getRect().x + 64, 
                                ship.getRect().y + 32);
                            break;
                        case SDLK_DOWN:
                            ship.moveDown();
                            bullets.emplace_back(renderer, 
                                ship.getRect().x + 64, 
                                ship.getRect().y + 32);
                            //aliens.emplace_back(renderer,100,123);
                            break;
                        case SDLK_LEFT:
                            quit = true;
                            break;
                        break;
                    }
            }
        }
        if(SDL_GetTicks() - lastAlienTime >= 1000){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
            }
        }

        SDL_RenderClear(renderer);
        ship.draw(renderer);
        for(auto& alien : aliens){
            alien.draw(renderer);
        }



        for (auto& bullet : bullets) {
            bullet.move();
            bullet.draw(renderer);
            //verifica si una bala colisiono con un alien
            for (auto& bullet : bullets) {
                for (auto& aliens : aliens) {
                    if (CheckCollision(bullet.getRect(), aliens.getRect())) {
                    // La bala ha golpeado un alien
                    // Hacer algo aquí, como reducir la vida del alien, etc.
                    printf("La bala golpeo un alien");
      }
    }
  }
        }
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
            return bullet.isOffScreen();
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
