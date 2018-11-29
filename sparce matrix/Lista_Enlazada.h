#include <iostream>
#include <list> //Line 2
#include <iterator> //Line 3
#include <algorithm>
#include <assert.h>
using namespace std;

template <class T>
class nodeType
{
    public:
    T info;
    int fila;
    int columna;
    nodeType<T> *next;
    nodeType<T> *back;
};


template <class Type>
class doublyLinkedList
{
public:
    const doublyLinkedList<Type>& operator=(const doublyLinkedList<Type> &);
    void copyList(const doublyLinkedList<Type>& otherList);
    void initializeList();
    bool isEmptyList() const;
    void destroy();
    void print() const;
    void reversePrint() const;
    int length() const;
    Type front() const;
    Type back() const;
    bool search(const Type& searchItem) const;
    void insert(const Type& insertItem,int fil,int col);
    void deleteNode(const Type& deleteItem);
    doublyLinkedList();
    ~doublyLinkedList();

    int count;
    nodeType<Type> *first;
    nodeType<Type> *last;

};
template <class Type>
doublyLinkedList<Type>::doublyLinkedList()
{
    first= NULL;
    last = NULL;
    count = 0;
}
template <class Type>
doublyLinkedList<Type>::~doublyLinkedList()
{
    destroy();
}
template <class Type>
bool doublyLinkedList<Type>::isEmptyList() const
{
    return (first == NULL);
}
template <class Type>
void doublyLinkedList<Type>::destroy()
{
    nodeType<Type> *temp;
    while (first != NULL)
    {
        temp = first;
        first = first->next;
        delete temp;
    }
    last = NULL;
    count = 0;
}
template <class Type>
void doublyLinkedList<Type>::initializeList()
{
    destroy();
}
template <class Type>
int doublyLinkedList<Type>::length() const
{
    return count;
}
template <class Type>
void doublyLinkedList<Type>::print() const
{
    nodeType<Type> *current;
    current = first;
    while (current != NULL)
        {
            cout<<current->fila<<" "<<current->columna<<": "<< current->info << " "<<endl;;
            current = current->next;
        }
    cout<<endl;cout<<endl;
}
template <class Type>
void doublyLinkedList<Type>::reversePrint() const
{
    nodeType<Type> *current;
    current = last;
    while (current != NULL)
    {
        cout << current->info << " ";
        current = current->back;
    }
    cout<<endl;
}
template <class Type>
bool doublyLinkedList<Type>::search(const Type& searchItem) const
{
    bool found = false;
    nodeType<Type> *current; //pointer to traverse the list
    current = first;
    while (current != NULL && !found)
        if (current->info >= searchItem)
            found = true;
        else
            current = current->next;
    if (found)
        found = (current->info == searchItem); //test for equality
    return found;
}//end search
template <class Type>
Type doublyLinkedList<Type>::front() const
{
    assert(first != NULL);
    return first->info;
}
template <class Type>
Type doublyLinkedList<Type>::back() const
{
    assert(last != NULL);
    return last->info;
}

template <class Type>
void doublyLinkedList<Type>::insert(const Type& insertItem,int fil,int col)
{
    //cout<<"insertando "<<insertItem<<endl;
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    nodeType<Type> *newNode; //pointer to create a node
    newNode = new nodeType<Type>; //create the node
    newNode->info = insertItem; //store the new item in the node
    newNode->fila=fil;
    newNode->columna=col;
    newNode->next = NULL;
    newNode->back = NULL;
    bool o;
    if (first == NULL) //if list is empty, newNode is the only node
    {
        first = newNode;
        last = newNode;
        count++;
    }
    else
  {
      o=false;
      current = first;
        while(current!=NULL){
           // cout<<"1 "<<current->info<<endl;
            if(current->fila==fil){o=true;break;}
            else if(current->fila>fil)break;
            trailCurrent = current;
            current=current->next;
        }
        while(current!=NULL&&o&&current->fila==fil){
           // cout<<"2 "<<current->info<<endl;
            if(current->columna==col){
                cout<<"Casilla ocupada"<<fil<<" "<<col<<endl;
                return;
            }
            if(current->columna>col)break;
            trailCurrent = current;

            current=current->next;

        }


     if (current == first) //insert newNode before first
     {
        first->back = newNode;
        newNode->next = first;
        first = newNode;
        count++;
     }
    else
    {
//insert newNode between trailCurrent and current
   // cout<<"A";
   // cout<<current<<endl;
        if (current != NULL)
        {

            trailCurrent->next = newNode;
            newNode->back = trailCurrent;
            newNode->next = current;
            current->back = newNode;
        }
        else
        {

            trailCurrent->next = newNode;

            newNode->back = trailCurrent;

            last = newNode;

        }
        count++;
        }//end else
    }//end else
}//end insert

/*
template <class Type>
void doublyLinkedList<Type>::insert(const Type& insertItem,int fil,int col)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    nodeType<Type> *newNode; //pointer to create a node
    bool found;
    newNode = new nodeType<Type>; //create the node
    newNode->info = insertItem; //store the new item in the node
    newNode->fila=fil;
    newNode->columna=col;
    newNode->next = NULL;
    newNode->back = NULL;
    if (first == NULL) //if list is empty, newNode is the only node
    {
        first = newNode;
        last = newNode;
        count++;
    }
    else
  {
        found = false;
        current = first;
        while (current != NULL && !found)
         if(current->fila==fil&&current->columna==col){
                cout<<"Casilla ocupada no se puede insertar: "<<insertItem<<"en "<<fil<<" "<<col<<endl;
                return;
         }
         else if (current->info > insertItem)
            found = true;
         else
         {
            trailCurrent = current;
            current = current->next;
         }
     if (current == first) //insert newNode before first
     {
        first->back = newNode;
        newNode->next = first;
        first = newNode;
        count++;
     }
    else
    {
//insert newNode between trailCurrent and current
        if (current != NULL)
        {
            trailCurrent->next = newNode;
            newNode->back = trailCurrent;
            newNode->next = current;
            current->back = newNode;
        }
        else
        {
            trailCurrent->next = newNode;
            newNode->back = trailCurrent;
            last = newNode;
        }
        count++;
        }//end else
    }//end else
}//end insert


*/
template <class Type>
void doublyLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    bool found;
    if (first == NULL)
        cout << "Cannot delete from an empty list." << endl;
    else if (first->info == deleteItem) //node to be deleted is
    //the first node
    {
        current = first;
        first = first->next;
        if (first != NULL)
            first->back = NULL;
        else
            last = NULL;
        count--;
        delete current;
    }
    else
    {
        found = false;
        current = first;
        while (current != NULL && !found) //search the list
            if (current->info >= deleteItem)
                found = true;
            else
                current = current->next;
        if (current == NULL)
            cout << "The item to be deleted is not in "<< "the list." << endl;
        else if (current->info == deleteItem) //check for equality
        {
            trailCurrent = current->back;
            trailCurrent->next = current->next;
            if (current->next != NULL)
                current->next->back = trailCurrent;
            if (current == last)
                last = trailCurrent;
            count--;
            delete current;
        }
        else
            cout << "The item to be deleted is not in list."<<endl;
    }//end else
}//end deleteNode

template <class C>
void doublyLinkedList<C>::copyList(const doublyLinkedList<C>& otherList)
{
    nodeType<C> *newNode; //pointer to create a node
    nodeType<C> *current; //pointer to traverse the list
    if (first != NULL) //if the list is nonempty, make it empty
    destroy();
    if (otherList.first == NULL) //otherList is empty
    {
        first = NULL;
        last = NULL;
        count = 0;
    }
    else
    {
    current = otherList.first; //current points to the
//list to be copied
    count = otherList.count;
//copy the first node
    first = new nodeType<C>; //create the node

    first->info = current->info; //store the new item in the node
    first->fila=current->fila;
    first->columna=current->columna;
    first->next = NULL;
    first->back = NULL;
    last = first; //make last point to the first node
    current = current->link; //make current point to the next
// node
//copy the remaining list
    while (current != NULL)
    {
        newNode = new nodeType<C>; //create a node
        newNode->info = current->info; //store the new item in the node
        newNode->fila=current->fila;
        newNode->columna=current->columna;
        newNode->next = NULL;
        newNode->back = NULL;

        last->link = newNode; //attach newNode after last
        last = newNode; //make last point to the actual last
//node
        current = current->link; //make current point to the
//next node
            }//end while
        }//end else
    }//end copyList
template <class I>
const doublyLinkedList<I>& doublyLinkedList<I>::operator=(const doublyLinkedList<I>& otherList)
{
    if (this != &otherList) //avoid self-copy
    {
        copyList(otherList);
    }//end else
    return *this;
}
