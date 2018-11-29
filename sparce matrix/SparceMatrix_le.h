

#ifndef SPARCEMATRIX
#define SPARCEMATRIX
#include <vector>
#include "Lista_Enlazada.h"

#include<iostream>
using namespace std;
#include<stdio.h>
#include<stdlib.h>


template <class T>
class Node
{
    T valor;
    int fila;
    int columna;
    Node *next;
public:
    Node(T val):valor(val=0),fila(-1),columna(-1),next(nullptr){};
};


template <class T>
class SparceMatrix{
public:
    SparceMatrix(){
        size=0;
    }
    SparceMatrix(vector<vector<T> > matriz);
    void insert(int fila,int columna,T elemento);
    void borrar(T elemento);
    void mostrar_l();
    void mostrar_m();
    bool find(T elemento);
    SparceMatrix operator +(const SparceMatrix &p1);
    SparceMatrix operator -(const SparceMatrix &p1);
    SparceMatrix operator =(const SparceMatrix &p1);
private:
    doublyLinkedList<T> lista;
    int size;

};
template <class T>
SparceMatrix<T>::SparceMatrix(vector<vector<T> >  matriz ){
    size=0;
    int f=matriz.size();
    int c=matriz[0].size();
    for(int i=0;i<f;i++)
        for(int j=0;j<c;j++){
            if(matriz[i][j]!=0){
                lista.insert(matriz[i][j],i,j);
                size++;
            }
        }
}

template <class T>
void SparceMatrix<T>::insert(int fil,int col,T elemento ){

    lista.insert(elemento,fil,col);
    size++;
}
template <class T>
void SparceMatrix<T>::mostrar_l(){
    lista.print();
}

template <class T>
void SparceMatrix<T>::borrar(T elemento){
    lista.deleteNode(elemento);
    size--;
}

template <class T>
bool SparceMatrix<T>::find(T elemento){
    return lista.search(elemento);
}
template <class T>
SparceMatrix<T> SparceMatrix<T>::operator =(const SparceMatrix &p1){
    if(this!=&p1){
        this->lista=p1.lista;
    }

    return *this;
}

template <class T>
SparceMatrix<T> SparceMatrix<T>::operator +(const SparceMatrix &p1){
    SparceMatrix<T> aux=*this;
    nodeType<T>*temp=p1.lista.first;

    while(temp!=NULL){
        bool found=false;
        nodeType<T> *current; //pointer to traverse the list
        current = lista.first;
        //cout<<"T"<<temp->info<<endl;
        while (current->next!= NULL && !found){
            //cout<<"C"<<current->info<<endl;
            if (current->fila==temp->fila&&current->columna==temp->columna){
                found = true;
                current->info+=temp->info;
                break;
                }
            else{
                current = current->next;
            }
        }
        if (found==false)
            aux.insert(temp->fila,temp->columna,temp->info);
        temp=temp->next;

    }
    return aux;
}

template <class T>
SparceMatrix<T> SparceMatrix<T>::operator -(const SparceMatrix &p1){
    SparceMatrix<T> aux=*this;
    nodeType<T>*temp=p1.lista.first;
    while(temp!=NULL){
        bool found=false;
        nodeType<T> *current; //pointer to traverse the list
        current = aux.lista.first;
        //cout<<"T"<<temp->info<<endl;
        while (current->next!= NULL && !found){
            //cout<<"C"<<current->info<<endl;
            if (current->fila==temp->fila&&current->columna==temp->columna){
                found = true;
                current->info-=(temp->info);

                break;
                }
            else{
                current = current->next;
            }
        }
        if (found==false)
            aux.insert(temp->fila,temp->columna,-(temp->info));
        temp=temp->next;

    }
    return aux;
}



#endif
