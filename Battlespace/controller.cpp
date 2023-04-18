#include "/home/nacho/Proyecto-I-Battlespace/Battlespace/third-party/include/serial/serial.h"
#include "thread"
#include <iostream>


int main(){
printf("puerto2");
    serial::Serial my_serial("/dev/ttyUSB0",9600,serial::Timeout::simpleTimeout(3000));
    if(my_serial.isOpen()){
        std::cout<<"port opened succesfully"<<std::endl;
        printf("puerto abierto");
    }else{
        std::cout<<"port failed to open"<<std::endl;
        printf("fallo al abrir el puerto");
    }
    my_serial.flushOutput();
}