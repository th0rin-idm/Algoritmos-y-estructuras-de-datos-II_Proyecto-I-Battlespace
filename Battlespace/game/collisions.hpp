#ifndef collisions_hpp
#define collisions_hpp

#include <SDL2/SDL.h>
#include <vector>

#include </home/vboxuser/Downloads/Battlespace/mobs/alien.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/bullet.hpp>

/*#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/alien.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/bullet.hpp>*/

//Para comprobar que hay colision entre la bala y alien
bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

//para comprobar que alguna bala colisiono con alguna nave y
bool collision(std::vector<Bullet>& bullets, std::vector<Alien>& aliens) {
    for(int i=0;i < bullets.size();i++){
        for (int j = 0; j < aliens.size(); j++) {
            if (CheckCollision(bullets[i].getRect(),aliens[j].getRect())) { 
                int damage=bullets[i].dmg;
                bullets.erase(bullets.begin()+i);
                aliens[j].health -= damage;
                if(aliens[j].health <= 0){
                aliens.erase(aliens.begin()+j);
                return true;
                }
                return true;
            }
        }
        }
    return false;
}


#endif