

#ifndef SPARCEMATRIX
#define SPARCEMATRIX
#include <vector>


#include<iostream>
using namespace std;
template <class T>
class SparceMatrix{4
public:
    SparceMatrix(){
        size=0;
    }
    SparceMatrix(vector<vector<T> > matriz);
    void insert(int fila,int columna,T elemento);
    void borrar(T elemento);
    void borrar(int fila,int columna);
    void mostrar_l();
    void mostrar_m();
    void find(T elemento);
    SparceMatrix operator +(const SparceMatrix &p1);
    SparceMatrix operator -(const SparceMatrix &p1);
    SparceMatrix operator =(const SparceMatrix &p1);
private:
    vector<T> fila;
    vector<T> columna;
    vector<T> valor;
    int size;
    //vector<vector<T> > lista;
};
template <class T>
SparceMatrix<T>::SparceMatrix(vector<vector<T> >  matriz ){
    size=0;
    int f=matriz.size();
    int c=matriz[0].size();
    for(int i=0;i<f;i++)
        for(int j=0;j<c;j++){
            if(matriz[i][j]!=0){
                fila.push_back(i);
                columna.push_back(j);
                valor.push_back(matriz[i][j]);
                size++;
            }
        }
}

template <class T>
void SparceMatrix<T>::insert(int fil,int col,T elemento){
    int i;
    for(i=0;i<size;i++){
        if(fila[i]==fil||fila[i]>fil)break;
    }
    for(;i<size;i++){
        if(columna[i]==col){
            cout<<"Casilla ocupada"<<endl;
            return;
        }
        if(columna[i]>col)break;
    }

    fila.insert(fila.begin()+i,fil);
    columna.insert(columna.begin()+i,col);
    valor.insert(valor.begin()+i,elemento);
    size++;
}
template <class T>
void SparceMatrix<T>::mostrar_l(){
    for(int i=0;i<size;i++){
        cout<<fila[i]<<" "<<columna[i]<<":"<<valor[i]<<endl;
    }
    cout<<endl;
}
template <class T>
void SparceMatrix<T>::borrar(int fil,int col){
    int i;
    for(i=0;i<size;i++){
        if(fila[i]==fil)break;
    }
    for(;i<size;i++){
        if(columna[i]==col)break;
    }
    fila.erase(fila.begin()+i);
    columna.erase(columna.begin()+i);
    valor.erase(valor.begin()+i);
    size--;
}
template <class T>
void SparceMatrix<T>::borrar(T elemento){
    int i;
    for(i=0;i<size;i++){
        if(valor[i]==elemento)break;
    }
    fila.erase(fila.begin()+i);
    columna.erase(columna.begin()+i);
    valor.erase(valor.begin()+i);
    size--;
}

template <class T>
void SparceMatrix<T>::find(T elemento){
    int i;
    for(i=0;i<size;i++){
        if(valor[i]==elemento)break;
    }
    if(i==size){
        cout<<"Elemento no encontrado"<<endl;
        return;
    }
    cout<<"fila: "<<fila[i]<<endl;
    cout<<"columna: "<<columna[i]<<endl;
}
template <class T>
SparceMatrix<T> SparceMatrix<T>::operator =(const SparceMatrix &p1){
    if(this!=&p1){
        this->filas=p1.filas;
        this->columnas=p1.columnas;
        this->valor=p1.valor;
    }
    return *this;
}

template <class T>
SparceMatrix<T> SparceMatrix<T>::operator +(const SparceMatrix &p1){
    SparceMatrix<T> aux=*this;
    bool con;
    for(int j=0;j<p1.size;j++){
        con=false;
        int i;
        for(i=0;i<aux.size;i++){
            if(p1.fila[j]==aux.fila[i])break;
        }
        for(;i<aux.size&&p1.fila[j]==aux.fila[i];i++){
            if(aux.columna[i]==p1.columna[j]){
                aux.valor[i]+=p1.valor[j];con=true;
                break;
            }
            if(aux.columna[i]>p1.columna[j]){
                break;
            }
        }
        if(!con){
        aux.fila.insert(aux.fila.begin()+i,p1.fila[j]);
        aux.columna.insert(aux.columna.begin()+i,p1.columna[j]);
        aux.valor.insert(aux.valor.begin()+i,p1.valor[j]);
        aux.size++;
        }
    }
    return aux;
}

template <class T>
SparceMatrix<T> SparceMatrix<T>::operator -(const SparceMatrix &p1){
    SparceMatrix<T> aux=*this;
    bool con;
    for(int j=0;j<p1.size;j++){
        con=false;
        int i;
        for(i=0;i<aux.size;i++){
            if(p1.fila[j]==aux.fila[i])break;
        }
        for(;i<aux.size&&p1.fila[j]==aux.fila[i];i++){
            if(aux.columna[i]==p1.columna[j]){
                aux.valor[i]-=p1.valor[j];con=true;
                break;
            }
            if(aux.columna[i]>p1.columna[j]){
                break;
            }
        }
        if(!con){
        aux.fila.insert(aux.fila.begin()+i,p1.fila[j]);
        aux.columna.insert(aux.columna.begin()+i,p1.columna[j]);
        aux.valor.insert(aux.valor.begin()+i,-p1.valor[j]);
        aux.size++;
        }
    }
    return aux;
}



#endif
