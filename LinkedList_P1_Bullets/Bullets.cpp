#include <iostream>
#include "NodeLinkedList.h"

int Bullets(int c){
    int BulletsSize=c;
    node *BulletsList= new node;
    BulletsList= Create(22);
    for(int i=0;i<=c;i++){
        BulletsList=InsertAtEnd(BulletsList, 23+i); 
    }
    Traverse(BulletsList);
    std::cout<<"La cantidad de balas es: " <<BulletsSize << std::endl;
    return 0;
}

int main(){
    Bullets(30);
    return 0;
}