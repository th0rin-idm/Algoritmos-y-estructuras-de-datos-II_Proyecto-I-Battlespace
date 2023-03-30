#ifndef principal_hpp
#define principal_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include </home/vboxuser/projects/sdl2_demo/game.hpp>

const char* WINDOW_TITLE = "Mi ventana";

//int main(int argc, char* argv[]) {
int principal(){
    SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Fallo al inicializar SDL: %s", SDL_GetError());
        //return 1;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Fallo al crear la ventana: %s", SDL_GetError());
        SDL_Quit();
        //return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Fallo al crear el renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        //return 1;
    }

    SDL_Texture* button_easyTexture = IMG_LoadTexture(renderer, "/home/vboxuser/projects/sdl2_demo/sprites/easy.png");
    SDL_Texture* button_normalTexture = IMG_LoadTexture(renderer, "/home/vboxuser/projects/sdl2_demo/sprites/normal.png");
    SDL_Texture* button_hardTexture = IMG_LoadTexture(renderer, "/home/vboxuser/projects/sdl2_demo/sprites/hard.png");

    if (!button_easyTexture || !button_normalTexture|| !button_normalTexture){
        SDL_Log("Fallo al cargar la textura: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        //return 1;
    }

    SDL_Rect button_easyRect = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/7 - 25, 50, 50 };
    SDL_Rect button_normalRect = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/3 - 25, 50, 50 };
    SDL_Rect button_hardRect = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 25, 50, 50 };

    bool replay,quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (mouseX >= button_easyRect.x && mouseX < button_easyRect.x + button_easyRect.w &&
                        mouseY >= button_easyRect.y && mouseY < button_easyRect.y + button_easyRect.h) {
                        game();
                    }else if (mouseX >= button_normalRect.x && mouseX < button_normalRect.x + button_normalRect.w &&
                        mouseY >= button_normalRect.y && mouseY < button_normalRect.y + button_normalRect.h) {
                        game();
                    }else if (mouseX >= button_hardRect.x && mouseX < button_hardRect.x + button_hardRect.w &&
                        mouseY >= button_hardRect.y && mouseY < button_hardRect.y + button_hardRect.h) {
                        game();
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, button_easyTexture, nullptr, &button_easyRect);
        SDL_RenderCopy(renderer, button_normalTexture, nullptr, &button_normalRect);
        SDL_RenderCopy(renderer, button_hardTexture, nullptr, &button_hardRect);
        SDL_RenderPresent(renderer);

        /*if(replay==true){
        principal();
        }*/   
    }
    
    SDL_DestroyTexture(button_easyTexture);
    SDL_DestroyTexture(button_normalTexture);
    SDL_DestroyTexture(button_hardTexture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#endif
