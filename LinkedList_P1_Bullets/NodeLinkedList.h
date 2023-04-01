// Function prototypes
#ifndef NODELINKEDLIST.h
#define NODELINKEDLIST.h
typedef struct node{
    int data;
    node* next;
}node;

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

#endif //NodeLinkedList.h