//#include </home/vboxuser/Downloads/Battlespace/game/builder.hpp>
//#include "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/game/builder.hpp"

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <iostream>
#include </home/vboxuser/Downloads/Battlespace/game/window.hpp>
//#include </home/nacho/Proyecto-I-Battlespace/sdl2_demo/game/game.hpp>

int main(int argc, char* argv[]){
    try {
        Window window;
        
        SDL_Texture* buttonTexture1 = IMG_LoadTexture(window.getRenderer(), "/home/vboxuser/Downloads/Battlespace/sprites/easy.png");
        SDL_Texture* buttonTexture2 = IMG_LoadTexture(window.getRenderer(), "/home/vboxuser/Downloads/Battlespace/sprites/normal.png");
        SDL_Texture* buttonTexture3 = IMG_LoadTexture(window.getRenderer(), "/home/vboxuser/Downloads/Battlespace/sprites/hard.png");
        /*
        SDL_Texture* buttonTexture1 = IMG_LoadTexture(window.getRenderer(), "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/sprites/easy.png");
        SDL_Texture* buttonTexture2 = IMG_LoadTexture(window.getRenderer(), "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/sprites/normal.png");
        SDL_Texture* buttonTexture3 = IMG_LoadTexture(window.getRenderer(), "/home/nacho/Proyecto-I-Battlespace/sdl2_demo/sprites/hard.png");
        */


        if (!buttonTexture1 || !buttonTexture2 || !buttonTexture3) {
            SDL_Log("Fallo al cargar la textura: %s", SDL_GetError());
            throw std::runtime_error("Fallo al cargar la textura");
        }

        while (!window.isQuit()) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                window.handleEvent(event);
            }

            window.drawButton(buttonTexture1, window.buttonRect_1);
            window.drawButton(buttonTexture2, window.buttonRect_2);
            window.drawButton(buttonTexture3, window.buttonRect_3);

            window.present();
        }

        SDL_DestroyTexture(buttonTexture1);
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture3);

        return 0;
    } catch (const std::exception& ex) {
        SDL_Log("%s", ex.what());
        return 1;
    }
}

