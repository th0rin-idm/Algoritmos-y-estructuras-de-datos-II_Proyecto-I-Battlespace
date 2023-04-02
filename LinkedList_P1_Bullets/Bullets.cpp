#include <iostream>
//#include "NodeLinkedList.h"
#include "NodeLinkedList.cpp"
using std::cin;
using std::cout;

//Para crear la lista de las balas principales
node* Bullets(int c, node* BulletList){
    int BulletsSize=c;
    node *BulletsList= new node;
    BulletsList= Create(999);
    for(int i=0;i<=c;i++){
        BulletsList=InsertAtEnd(BulletsList, 23+i); 
    }
    Traverse(BulletsList);
    std::cout<<"La cantidad de balas es: " <<BulletsSize << std::endl;
    return BulletsList;
}

//Para crear la Lista de las balas recuperdas
node *RecoveryBullets(int e,node* RecoveryList,int d){
    if(RecoveryList==nullptr){
        RecoveryList= Create(999);
        RecoveryList=InsertAtEnd(RecoveryList,e/d);
        printf("Se entro al if, se recupero la bala y fue \n guardada como la primera de las balas recuperdas \n");
        return RecoveryList;
    }else{
        RecoveryList=InsertAtEnd(RecoveryList,e/d);
        printf("Se recupero la bala y fue agregada a \n la ultima posicion de la lista de balas recuperadas \n");
    }
}

//Para agregar la primer bala de las balas recuperdas como la ultima bala a la lista de balas principales
void addBullets(node*  BulletList,node* RecoveryList){
    cout<<"entro a addBullets \n";
    if(Searchbullet(RecoveryList,1) != NULL){
        cout<<"entro al if \n";
        BulletList=InsertAtEnd(BulletList,Searchbullet(RecoveryList,1));
        RecoveryList=DeleteAtPos(RecoveryList,2);

    }else{
        cout <<"No hay balas en RecoveryList";
    }

}
// Para conocer el dato/damage de la bala a disparar, si no quedaran retornaria 0 para acabar el juego
int shotBullet(node* BulletsList){
    if(Searchbullet(BulletsList,1)!= NULL){
        int bullet=BulletsList->next->data;
        cout<<"el damage de la bala es"<< bullet;
        BulletsList=DeleteAtPos(BulletsList,2);
        return bullet;
    }else{cout<<"No quedan balas";return 0;}
}

int main(){
    //La dificultad va a ser el numero por el cual se divida el damage inicial de la bala, esto para que la bala recuperada haga menor damage
    int d= 1;

    //Para llamar a la funcion bullets y crear la lista de balas(EL numero varia segun la dificultad)
    node *BulletsList= nullptr;
    BulletsList=Bullets(30,BulletsList);

    // Para crear la Lista de RecoveryList, las balas recuperadas
    // Se necesita el nullprt para que la primer bala recuperada se guarde correctamente
    node *RecoveryList= nullptr;
    //Se necesita el = para que una vez que entre por primera vez se pueda guardar globalmente +la variable y no siga entrando a cambiar la primera posicion de balas recuperdas
    RecoveryList=RecoveryBullets(20,RecoveryList,d);
    //Despues que se entra por primera vez se puede usar de la siguente manera y no hay problemas
    RecoveryBullets(21,RecoveryList,d);
    RecoveryBullets(22,RecoveryList,d);
    RecoveryBullets(23,RecoveryList,d);
    cout<<" \n Lista de balas y balas recuperadas \n";
    Traverse(BulletsList);
    Traverse(RecoveryList);
    cout<<" \n Lista de balas y balas recuperdas luego de a;adir algunas recuperadas a las balas principales \n";
    int numero= Searchbullet(RecoveryList,3);
    addBullets(BulletsList,RecoveryList);
    Traverse(BulletsList);
   Traverse(RecoveryList);
   shotBullet(BulletsList);
   cout<<" \n Bala disparada \n ";
   Traverse(BulletsList);
   Traverse(RecoveryList);

    cout<<"\n";
    return 0;
}