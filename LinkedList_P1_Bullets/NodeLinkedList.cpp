#include <iostream>
//#include "NodeLinkedList.h"
//#include "Bullets.cpp"
using std::cin;
using std::cout;


// Structure of the node of a singly linked list
typedef struct node{
    int data;
    node* next;
}node;


// Function prototypes
node *Create(int value); //Necesario usar este primero para crear la cabeza/inicio de la lista(si se utiliza esta bala se acaba el juego)
node *InsertAtBeg(node *head, int value);//Para insertar en la primera posicion(cabeza/inicio de la lista)
node *InsertAtPos(node *head, int value, int position);//Para insetar en x posicion
node *InsertAtEnd(node *head, int value);//Para insertar de ultimo en la lista
node *DeleteAtBeg(node *head);// Para eliminar el inicio(cabeza/inicio de la lista) el segundo en la lista pasaria a ser la cabeza/primero de la lista
node *DeleteAtPos(node *head, int position);// Para eliminar el nodo de x posicion
node *DeleteAtEnd(node *head); //Para eliminar el ultimo nodo de la lista
node *Concatenate(node *head1, node *head2);// no se va a usar probablemente
int Search(node *head, int element);// para buscar un nodo con cierto elemento
void Traverse(node *head); //para printear la lista
int Searchbullet(node *head, int element);// Para el buscar el dato int de la lista en x posicion

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
node *RecoveryBullets(int e,node* RecoveryList,int d){
    if(RecoveryList==nullptr){
        RecoveryList= InsertAtBeg(RecoveryList,e/d);
        printf("Se entro al if, se recupero la bala y fue \n guardada como la primera de las balas recuperdas \n");
        return RecoveryList;
    }else{
        RecoveryList=InsertAtEnd(RecoveryList,e/d);
        printf("Se recupero la bala y fue agregada a \n la ultima posicion de la lista de balas recuperadas \n");
    }
}
void addBullets(node*  BulletList,int e){
    BulletList=InsertAtEnd(BulletList,e);

}

int main()
{
    node *head1 = new node;
    // Creating a head node of value 81
    head1 = Create(81);
    // Inserting a node of value 2 at the end
    head1 = InsertAtEnd(head1, 2); 
    // Inserting a node of value 53 at the beginning
    head1 = InsertAtBeg(head1, 53);
    // Inserting a node of value 44 at the 2nd position
    head1 = InsertAtPos(head1, 44, 2);
    // Printing the first linked list
    cout<<"FIRST: ";
    Traverse(head1);

    cout<<"\n";

    node *head2 = new node;
    // Creating a head node of value 91
    head2 = Create(91);
    // Inserting a node of value 23 at the end
    head2 = InsertAtEnd(head2, 23);
    // Inserting a node of value -4 at the end
    head2 = InsertAtEnd(head2, -4);
    // Printing the second linked list
    cout << "SECOND: ";
    Traverse(head2);

    cout<<"\n";

    // Concatenating first and second linked list
    head1 = Concatenate(head1, head2);
    // Printing the concatenated linked list
    cout << "CONCATENATED: ";
    Traverse(head1);
    cout<<"\n";
    //Para llamar a la funcion bullets y crear la lista de balas(EL numero varia segun la dificultad)
    Bullets(30);
    // Para crear la Lista de RecoveryList, las balas recuperadas
    // Se necesita el nullprt para que la primer bala recuperada se guarde correctamente
    node *RecoveryList= nullptr;
    //La dificultad va a ser el numero por el cual se divida el damage inicial de la bala, esto para que la bala recuperada haga menor damage
    int d= 1;
    //Se necesita el = para que una vez que entre por primera vez se pueda guardar globalmente +la variable y no siga entrando a cambiar la primera posicion de balas recuperdas
    RecoveryList=RecoveryBullets(20,RecoveryList,d);
    //Despues que se entra por primera vez se puede usar de la siguente manera y no hay problemas
    RecoveryBullets(21,RecoveryList,d);
    RecoveryBullets(22,RecoveryList,d);
    RecoveryBullets(23,RecoveryList,d);
    Traverse(RecoveryList);
    Search(RecoveryList,0);
    Search(RecoveryList,2);
    int numero= Searchbullet(RecoveryList,3);

    cout<< "el da;o de la bala es: " << numero ;
    cout<<"\n";
    return 0;
}


// Function to create the head node (first node) of a singly linked list
node *Create(int value)
{
    node *ptr = new node;
    ptr->data = value;
    ptr->next = NULL;
    return ptr;
}

// Function to insert a new node at the beginning of a singly linked list
node *InsertAtBeg(node *head, int value)
{
    node *ptr = new node;
    ptr->data = value;
    ptr->next = head;
    head = ptr;
    return head;
}

// Function to insert a new node at the specified position of a singly linked list
node *InsertAtPos(node *head, int value, int position)
{
    if(position < 1)
    {
        cout<<"Invalid Position";
        return head;
    }
    
    if(position == 1)
        return InsertAtBeg(head, value);

    node *ptr1 = new node;
    ptr1 = head;

    node *ptr2 = new node;
    ptr2->data = value;
    ptr2->next = NULL;

    while(--position > 1)
        ptr1 = ptr1->next;

    ptr2->next = ptr1->next;
    ptr1->next = ptr2;

    return head;
}

// Function to insert a new node at the end of a singly linked list
node *InsertAtEnd(node *head, int value)
{
    node *ptr1 = new node;
    ptr1 = head;

    while(ptr1->next != NULL)
    {
        ptr1 = ptr1->next;
    }
    node *ptr2 = new node;
    ptr2->data = value;
    ptr2->next = NULL;

    ptr1->next = ptr2;

    return head;
}

// Function to delete a node from the beginning of a singly linked list
node *DeleteAtBeg(node *head)
{
    if(head == NULL)
    {
        cout<<"Underflow! Can't delete from empty list";
        return head;
    }
    node* ptr = new node;
    ptr = head;
    head = head->next;
    delete ptr;
    return head;
}

// Function to delete a node from the specified position of a singly linked list
node *DeleteAtPos(node *head, int position)
{
    if(head == NULL)
    {
        cout << "Underflow! Can't delete from empty list";
        return head;
    }

    if(position < 1)
    {
        cout << "Invalid Position";
        return head;
    }

    if(position == 1)
        return DeleteAtBeg(head); 

    node *ptr1 = new node;
    ptr1 = head;

    position--;
    while(position > 1)
    {
        ptr1 = ptr1->next;
        position--;
    }

    node *ptr2 = new node;
    ptr2 = ptr1->next;
    ptr1->next = ptr2->next;
    delete ptr2;
    return head;
}

// Function to delete a node from the end of a singly linked list
node *DeleteAtEnd(node *head)
{
    if(head == NULL)
    {
        cout << "Underflow! Can't delete from empty list";
        return head;
    }
    if(head->next == NULL)
    {
        delete head;
        return NULL;
    }

    node *ptr1 = new node;
    ptr1 = head;

    while(ptr1->next->next != NULL)
        ptr1 = ptr1->next;

    node *ptr2 = new node;
    ptr2 = ptr1->next;
    delete ptr2;
    ptr1->next = NULL;
    return head;
}

// Function to concatenate two singly linked lists
node *Concatenate(node *head1, node *head2)
{
    node *ptr = new node;
    ptr = head1;

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = head2;
    return head1;
}

// Function to search for an element in a singly linked list
int Search(node *head, int element)
{
    node *ptr = new node;
    ptr = head;
    int position = 0;
    while (ptr != NULL)
    {
        position++;
        if (ptr->data == element)
            return position;
        ptr = ptr->next;
    }
    return 0;
}

int Searchbullet(node *head, int element)
{
    node *ptr = new node;
    ptr = head;
    int position = 0;
    while (ptr != NULL)
    {
        
        if (position == element)
            return ptr->data;
        ptr = ptr->next;
        position++;
    }
    return 0;
}

// Function to print a singly linked list from head node to tail node
void Traverse(node *head)
{
    node *ptr = head;
    cout << "The linked list: ";
    while (ptr != NULL)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
}