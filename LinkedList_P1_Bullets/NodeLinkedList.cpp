#include <iostream>
using std::cin;
using std::cout;


// Structure of the node of a singly linked list
typedef struct node{
    int data;
    node* next;
}node;

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

// Funcion para buscar el dato en cierta posicion de la lista
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