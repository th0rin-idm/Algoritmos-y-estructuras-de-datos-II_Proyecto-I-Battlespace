#ifndef spawner_hpp
#define spawner_hpp

#include <vector>
//#include </home/vboxuser/Downloads/Battlespace/mobs/alien.hpp>
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/alien.hpp>

void alienGenerator(int num,int frec, std::vector<Alien>& alienus){
    if(SDL_GetTicks() - frec >= num*15){
            frec = SDL_GetTicks();
            for(auto& alien : alienus){
                alien.move();
            }
    }
}
#endif