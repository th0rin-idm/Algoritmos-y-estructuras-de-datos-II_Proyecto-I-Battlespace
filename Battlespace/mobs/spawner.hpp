#ifndef spawner_hpp
#define spawner_hpp

#include <vector>
#include <iostream>
#include </home/vboxuser/Downloads/Battlespace/mobs/alien.hpp>

void aliencreator(std::vector<Alien>& aliens,int bullets_count, int n){
    Uint32 lastAlienTime= SDL_GetTicks();
    
    
        /*if(n==35 && SDL_GetTicks() - lastAlienTime >= n*35){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
            }
            
            

        }else if(n==45 && SDL_GetTicks() - lastAlienTime >= n*25){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
                
            }
            
        }else if(n==55 && SDL_GetTicks() - lastAlienTime >= n*15){
            lastAlienTime = SDL_GetTicks();
            for(auto& alien : aliens){
                alien.move();
                
            }
            
        }*/
    
    /*for(int i = (loop+1)*5; i < (loop+2)*5 && i < aliens.size(); i++){
        aliens[(i/5)-1].move();        
    }*/
}
#endif