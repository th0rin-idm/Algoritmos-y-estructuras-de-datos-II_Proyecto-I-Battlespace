#ifndef window_hpp
#define window_hpp


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include </home/vboxuser/projects/sdl2_demo/game/game.hpp>

/*const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;*/
const char* WINDOW_TITLE = "Mi ventana";

class Window {
public:
    Window() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("Fallo al inicializar SDL: %s", SDL_GetError());
            throw std::runtime_error("Fallo al inicializar SDL");
        }

        window_ = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window_) {
            SDL_Log("Fallo al crear la ventana: %s", SDL_GetError());
            SDL_Quit();
            throw std::runtime_error("Fallo al crear la ventana");
        }

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer_) {
            SDL_Log("Fallo al crear el renderer: %s", SDL_GetError());
            SDL_DestroyWindow(window_);
            SDL_Quit();
            throw std::runtime_error("Fallo al crear el renderer");
        }
    }

    ~Window() {
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void drawButton(SDL_Texture* texture, SDL_Rect rect) {
        SDL_RenderCopy(renderer_, texture, nullptr, &rect);
    }

    void present() {
        SDL_RenderPresent(renderer_);
    }

    bool isQuit() {
        return quit_;
    }
    SDL_Rect buttonRect_1 = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/7 - 25, 50, 50 };
    SDL_Rect buttonRect_2 = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/3 - 25, 50, 50 };
    SDL_Rect buttonRect_3 = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 25, 50, 50 };

    void handleEvent(const SDL_Event& event) {
        switch (event.type) {
            case SDL_QUIT:
                quit_ = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= buttonRect_1.x && mouseX < buttonRect_1.x + buttonRect_1.w &&
                    mouseY >= buttonRect_1.y && mouseY < buttonRect_1.y + buttonRect_1.h) {
                    
                    SDL_DestroyRenderer(renderer_);
                    SDL_DestroyWindow(window_);
                    game();

                }else if (mouseX >= buttonRect_2.x && mouseX < buttonRect_2.x + buttonRect_2.w &&
                    mouseY >= buttonRect_2.y && mouseY < buttonRect_2.y + buttonRect_2.h) {
                    
                    SDL_DestroyRenderer(renderer_);
                    SDL_DestroyWindow(window_);
                    game();
                }else if (mouseX >= buttonRect_3.x && mouseX < buttonRect_3.x + buttonRect_3.w &&
                    mouseY >= buttonRect_3.y && mouseY < buttonRect_3.y + buttonRect_3.h) {
                    
                    SDL_DestroyRenderer(renderer_);
                    SDL_DestroyWindow(window_);
                    game();
                }
                break;
        }
    }

    SDL_Renderer* getRenderer() {
        return renderer_;
    }

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    bool quit_ = false;

    //SDL_Rect buttonRect_ = { SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 25, 100, 50 };
};

//int main(int argc, char* argv[]) {
int builder(){
    try {
        Window window;

        SDL_Texture* buttonTexture1 = IMG_LoadTexture(window.getRenderer(), "/home/vboxuser/projects/sdl2_demo/sprites/easy.png");
        SDL_Texture* buttonTexture2 = IMG_LoadTexture(window.getRenderer(), "/home/vboxuser/projects/sdl2_demo/sprites/normal.png");
        SDL_Texture* buttonTexture3 = IMG_LoadTexture(window.getRenderer(), "/home/vboxuser/projects/sdl2_demo/sprites/hard.png");


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
#endif