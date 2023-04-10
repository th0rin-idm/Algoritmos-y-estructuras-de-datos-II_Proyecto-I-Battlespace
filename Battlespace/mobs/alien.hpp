#ifndef alien_hpp
#define alien_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include </home/nacho/Proyecto-I-Battlespace/sdl2_demo/mobs/alien.hpp>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Alien {
public:
    Alien(SDL_Renderer* renderer, int x, int y) {
        rect_alien = {x, y, 32, 32};
        skin_alien = IMG_Load("sprites/alien.png");
        texture_alien = SDL_CreateTextureFromSurface(renderer, skin_alien);
        SDL_FreeSurface(skin_alien);
    }
    int health=100;
    
    void move() {
        rect_alien.x -= 15;
    }
    
    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture_alien, nullptr, &rect_alien);
    }
    
    bool isOffScreen() const {
        return rect_alien.x > SCREEN_WIDTH;
    }
    
    SDL_Rect getRect() const {
        return rect_alien;
    }
    
    SDL_Texture* getTexture() const {
        return texture_alien;
    }
    
private:
    SDL_Surface* skin_alien;
    SDL_Texture* texture_alien;
    SDL_Rect rect_alien;
};


#endif