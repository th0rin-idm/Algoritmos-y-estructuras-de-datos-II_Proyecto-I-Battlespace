#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    bool program_is_running = true;
    
    while (program_is_running) {

        std::cout << "Program is running..." << std::endl;
        // Lógica del programa aquí
    

        // Create a window
        SDL_Window* window = SDL_CreateWindow(
            "osea si2",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640,
            480,
            SDL_WINDOW_SHOWN
        );

        if (window == nullptr)
        {
            std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
            return 1;
        }

        // Wait for user to close window
        SDL_Event event;
        while (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                program_is_running= false;
                break;
            }
        }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    }
}