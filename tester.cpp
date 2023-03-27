#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
#include "/home/vboxuser/projects/sdl2_demo/ship.hpp"
#include "/home/vboxuser/projects/sdl2_demo/bullet.hpp"

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Battlespace", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;
    bool quit = false;
    
    Ship ship(renderer, "sprites/ship.png", 50, SCREEN_HEIGHT / 2 - 32);
    std::vector<Bullet> bullets;
    
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
                            break;
                    }
                    break;
            }
        }
        
        SDL_RenderClear(renderer);
        ship.draw(renderer);
        for (auto& bullet : bullets) {
            bullet.move();
            bullet.draw(renderer);
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
    
    return 0;
}
