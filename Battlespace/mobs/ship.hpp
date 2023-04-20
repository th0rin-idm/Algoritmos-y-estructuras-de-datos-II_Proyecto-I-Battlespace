#ifndef ship_hpp
#define ship_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ship {
public:
    Ship(SDL_Renderer* renderer, const char* path, int x, int y) {
        surface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        rect = {x, y, 64, 64};
    }
    int health=100;
    
    void moveUp() {
        if(rect.y>0){rect.y -= 10;}
    }
    
    void moveDown() {
        if(rect.y<380){rect.y += 10;}
    }
    
    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
    
    SDL_Rect getRect() const {
        return rect;
    }
    
    SDL_Texture* getTexture() const {
        return texture;
    }


private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
};

#endif