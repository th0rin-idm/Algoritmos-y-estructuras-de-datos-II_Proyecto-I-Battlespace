#ifndef movement_hpp
#define movement_hpp

#include <SDL2/SDL.h>

int speed(int x2){
    Uint32 lastIncrementTime = SDL_GetTicks();
    // Obtener el tiempo actual en milisegundos.
    Uint32 currentTime = SDL_GetTicks();
    // Calcular la cantidad de tiempo transcurrido desde el último incremento.
    Uint32 elapsedTime = currentTime - lastIncrementTime;

    // Solo incrementar la variable si ha pasado al menos 100 milisegundos.
    if (elapsedTime >= 10) {
        x2 += 10;
        lastIncrementTime = currentTime;
    }

    // Esperar un poco para evitar sobrecargar la CPU.
    SDL_Delay(1);
    return x2;
    }
    
#endif