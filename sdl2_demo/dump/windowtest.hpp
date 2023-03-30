#ifndef windowtest_hpp
#define windowtest_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "movement.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int WindowGame()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Battlespace",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Cargar nave
    SDL_Surface* surface = IMG_Load("/home/vboxuser/projects/sdl2_demo/image.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Cargar disparo
    SDL_Surface* surface2 = IMG_Load("/home/vboxuser/projects/sdl2_demo/image2.png");
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);

    int x = 0, y = 50, x2, y2;
    bool quit,fire = false;

    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_UP && y>0) {
                    y -= 10; // Mover la imagen 10 unidades hacia arriba
                }  
                else if (event.key.keysym.sym == SDLK_DOWN && y<380) {
                    y += 10; // Mover la imagen 10 unidades hacia arriba
                }
                else if (event.key.keysym.sym==SDLK_LEFT){
                        fire=true;
                    }   
            }
        }
        
        if(fire){
            x2 += speed(x);
            y2 = y;
            SDL_RenderClear(renderer);
            SDL_Rect rect2 = { x2, y2, 25, 25};
            SDL_RenderCopy(renderer, texture2, NULL, &rect2);

            SDL_Rect rect = { x, y, 100, 100 };
            SDL_RenderCopy(renderer, texture, NULL, &rect);

            SDL_RenderPresent(renderer);

        }else{
            SDL_RenderClear(renderer);
            SDL_Rect rect = { x, y, 100, 100 };
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_RenderPresent(renderer);
        }
        
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
#endif