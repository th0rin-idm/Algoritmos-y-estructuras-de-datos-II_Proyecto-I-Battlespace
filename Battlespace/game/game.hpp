#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
#include <ctime>

using std::cin;
using std::cout;

/*
#include </home/vboxuser/Downloads/Battlespace/mobs/alien.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/bullet.hpp>
#include </home/vboxuser/Downloads/Battlespace/mobs/ship.hpp>
#include </home/vboxuser/Downloads/Battlespace/LinkedList_P1_Bullets/Bullets.cpp>
#include </home/vboxuser/Downloads/Battlespace/estrategias/lector.cpp>
*/

#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

#include "/home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/LinkedList_P1_Bullets/Bullets.cpp"
#include "/home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/ship.hpp"
#include "/home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/bullet.hpp"
#include "/home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/mobs/alien.hpp"
#include </home/nacho/Proyecto1/Proyecto-I-Battlespace/Battlespace/estrategias/lector.cpp>

int strike = 0;

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
                strike++;
                return true;
                }
                return true;
            }
        }
        }
    return false;
}


void game(int n){
    std::clock_t start = std::clock(); // Se guarda el tiempo inicial
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Battlespace", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    bool quit,replay = false;
    Uint32 lastAlienTime= SDL_GetTicks();
    
    Ship ship(renderer, "sprites/ship.png", 50, SCREEN_HEIGHT / 2 - 32);
    std::vector<Bullet> bullets;
    std::vector<Alien> aliens;
    
    int refract=1; 
    int bullets_count = 0;
    int d;

    int array[3];
    array[0] = n;
    array[1] = bullets_count;
    array[2]=d;
    int lista[array[0]];


    if(array[0]==50){array[2]=1;}else if(array[0]==60){array[2]=2;}else if(array[0]==70){array[2]=3;}
    //Para llamar a la funcion bullets y crear la lista de balas(EL numero varia segun la dificultad)
    node *BulletsList= nullptr;
    BulletsList=createBullets(array[0],BulletsList,d);
    // Para crear la Lista de RecoveryList, las balas recuperadas
    // Se necesita el nullprt para que la primer bala recuperada se guarde correctamente
    node *RecoveryList= nullptr;
    //Se necesita el = para que una vez que entre por primera vez se pueda guardar globalmente +la variable y no siga entrando a cambiar la primera posicion de balas recuperdas
    RecoveryList=RecoveryBullets(0,RecoveryList,d);

   for (int i = 0; i < array[0]; i++) {
        int randomy = rand() % 427 + 2; // Genera un número aleatorio entre 1 y 100
        lista[i] = randomy;
        aliens.emplace_back(renderer, SCREEN_WIDTH+(i*15), lista[i]);
    }


    const int MIN_HORDE_INTERVAL = 3000; // Tiempo mínimo entre hordas (en milisegundos)
    const int MAX_HORDE_INTERVAL = 4000; // Tiempo máximo entre hordas (en milisegundos)

    int lastHordeTime = 0; // Tiempo en que se generó la última horda

    using namespace LibSerial ;
    // Instantiate a Serial Port and a Serial Stream object.
    SerialStream serial_stream;

    try
    {
        // Abrir el puerto para el Serial_Stream donde esta conectado el arduino
        serial_stream.Open("/dev/ttyUSB0") ;
    }
    catch (const OpenFailed&)
    {
        std::cerr << "The serial port did not open correctly." << std::endl ;
    }
    serial_stream.SetBaudRate(LibSerial::BaudRate::BAUD_9600);
    serial_stream.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
    serial_stream.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);

    // Variables para almacenar los datos recibidos
    int lecturaX, lecturaY, bt, lecturaPot;


    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            ship.moveUp();
                            if(array[1] < array[0]*2 && bullets.size()<refract){
                                array[1]++;
                                //int dmgb=shotBullet(BulletsList);
                                int dmgb=array[2];
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32,dmgb);
                            }
                            break;
                       case SDLK_DOWN:
                            ship.moveDown();
                            if(array[1] < array[0]*2 && bullets.size()<refract){
                                array[1]++;
                                //int dmgb=shotBullet(BulletsList);
                                int dmgb=array[2];
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32,dmgb);
                            }
                            break;
                         case SDLK_LEFT:
                            if(refract>=2){
                                refract-=1;
                                }
                            break;
                        case SDLK_RIGHT:
                            refract+=1;
                            break;
                        break;
                    }
            }
        }

        // Leer los datos desde Arduino
        std::string data;
        std::getline(serial_stream, data);

        // Analizar los datos recibidos
        sscanf(data.c_str(), "%d,%d,%d,%d", &lecturaX, &lecturaY, &bt, &lecturaPot);

        // Imprimir los datos recibidos
        /*
        std::cout << "LecturaX: " << lecturaX << std::endl;
        std::cout << "LecturaY: " << lecturaY << std::endl;
        std::cout << "BT: " << bt << std::endl;
        std::cout << "LecturaPot: " << lecturaPot << std::endl;
        */
        // Enviar datos a Arduino para encender el siete segmentos, buzzer y led
        int sieteSegmentos = 0;
        int buzzer = 0;
        int led = 0;
        /*
        serial_stream << sieteSegmentos << "," << buzzer << "," << led << std::endl;
        // Esperar un tiempo antes de leer los datos de nuevo
        SDL_Delay(50);
        */
        //Movimiento de la nave con el arduino
        if(lecturaY>600){ship.moveUp();}else if(lecturaY<400){ship.moveDown();}else{}
        //Disparo con el arduino
        if(bt==0){if(array[1] < array[0]*2 && bullets.size()<refract){
                                array[1]++;
                                //int dmgb=shotBullet(BulletsList);
                                int dmgb=array[2];
                                bullets.emplace_back(renderer, 
                                    ship.getRect().x + 64, 
                                    ship.getRect().y + 32,dmgb);
                            }else{led=1;serial_stream << sieteSegmentos << "," << buzzer << "," << led << std::endl;}
        }
        //Velocidad de disparo con el arduino
        if(lecturaPot>0 && lecturaPot<400){refract=2;}else if(lecturaPot>400 && lecturaPot<600){refract=4;}else if(lecturaPot>600 && lecturaPot<800){refract=6;}else if(lecturaPot>800 && lecturaPot<100){refract=8;}

        if(array[0]==50 && SDL_GetTicks() - lastAlienTime >= array[0]*25){
            
            int currentTime = SDL_GetTicks();
            int elapsedTime = currentTime - lastHordeTime;
                
            // Verificar si es momento de generar una nueva horda
            if (elapsedTime >= MIN_HORDE_INTERVAL) {
                int randomInterval = MAX_HORDE_INTERVAL - MIN_HORDE_INTERVAL;
                int hordeInterval = rand() % randomInterval + MIN_HORDE_INTERVAL;
                    
                if (currentTime - lastHordeTime >= hordeInterval) {
                        // Generar nueva horda
                        sieteSegmentos=1;
                        serial_stream << sieteSegmentos << "," << buzzer << "," << led << std::endl;
                        int aliensPerHorde = 5 + (array[0] - 1) * 5; // Número de aliens por horda
                        for (int i = 0; i < aliensPerHorde && i < aliens.size(); i++) {
                            aliens[i].move();
                            if(i % 2 == 0){
                                aliens[i].Reverse_moveUp();
                            }else{
                                aliens[i].Reverse_moveDown();
                            }
                        }
                        // Actualizar tiempo de la última horda
                        lastHordeTime = currentTime;
                    }
            }
        }else if(array[0]==60 && SDL_GetTicks() - lastAlienTime >= array[0]*15){
            int currentTime = SDL_GetTicks();
            int elapsedTime = currentTime - lastHordeTime;
                
            // Verificar si es momento de generar una nueva horda
            if (elapsedTime >= MIN_HORDE_INTERVAL) {
                int randomInterval = MAX_HORDE_INTERVAL - MIN_HORDE_INTERVAL;
                int hordeInterval = rand() % randomInterval + MIN_HORDE_INTERVAL;
                    
                if (currentTime - lastHordeTime >= hordeInterval) {
                        // Generar nueva horda
                        int aliensPerHorde = 5 + (array[0] - 1) * 5; // Número de aliens por horda
                        for (int i = 0; i < aliensPerHorde && i < aliens.size(); i++) {
                            aliens[i].move();
                        }
                        
                        // Actualizar tiempo de la última horda
                        lastHordeTime = currentTime;
                    }
            }

        }else if(array[0]==70 && SDL_GetTicks() - lastAlienTime >= array[0]*5){
            int currentTime = SDL_GetTicks();
            int elapsedTime = currentTime - lastHordeTime;
                
            // Verificar si es momento de generar una nueva horda
            if (elapsedTime >= MIN_HORDE_INTERVAL) {
                int randomInterval = MAX_HORDE_INTERVAL - MIN_HORDE_INTERVAL;
                int hordeInterval = rand() % randomInterval + MIN_HORDE_INTERVAL;
                    
                if (currentTime - lastHordeTime >= hordeInterval) {
                        // Generar nueva horda
                        int aliensPerHorde = 5 + (array[0] - 1) * 5; // Número de aliens por horda
                        for (int i = 0; i < aliensPerHorde && i < aliens.size(); i++) {
                            aliens[i].move();
                        }
                        
                        // Actualizar tiempo de la última horda
                        lastHordeTime = currentTime;
                    }
            }
        }

        SDL_RenderClear(renderer);
        ship.draw(renderer);

        for(auto& alien : aliens){
            int enemy=0;
            if(enemy ==0){
            alien.draw(renderer);
            enemy++;
            }
        }


        //creacion de balas,movimiento,colision con alines y eliminacion de bala o recuperacion
        for (auto& bullet : bullets) {
            bullet.move();
            bullet.draw(renderer);
            //verifica si una bala colisiono con un alien
                for (auto& alien : aliens) {
                    if (collision(bullets, aliens)) {
                        int buzzer=1;
                        serial_stream << sieteSegmentos << "," << buzzer << "," << led << std::endl;
                    }
                    }
                    if(bullet.isOffScreen()){
                    RecoveryBullets(bullet.dmg,RecoveryList,array[0]);
                    //bullets.erase(bullets.begin());
                    addBullets(BulletsList,RecoveryList);
                    array[1]-=1;

        }
        }
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
            return bullet.getRecty()<0;
        }), bullets.end());



        SDL_RenderPresent(renderer);
        //SDL_Delay(60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
}

#endif
