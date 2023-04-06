#ifndef bullet_hpp
#define bullet_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Bullet {
public:
    Bullet(SDL_Renderer* renderer, int x, int y) {
        rect = {x, y, 16, 16};
        recty=y;
        surface = IMG_Load("sprites/bullet.png");
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    int dmg=80;
    
    void move() {
        rect.x += 15;
    }
    
    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
    
    bool isOffScreen() const {
        return rect.x > SCREEN_WIDTH;
    }
    
    SDL_Rect getRect() const {
        return rect;
    }
     int getRecty() const {
        return recty;
    }
    
    SDL_Texture* getTexture() const {
        return texture;
    }
    
private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
    int recty;
};


#endif