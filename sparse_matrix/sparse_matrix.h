#ifndef sparse_matrix_h_
#define sparse_matrix_h_

#include <iostream>
#include <vector>

#define c_ cout<<"A"<<endl;
using namespace std;
template<class T>
class sparse_matrix;
template <class T>
class Nodo{
private:
    T valor;
    int vfil;
    int vcol;
    Nodo<T> * pfil;
    Nodo<T> * pcol;
public:
    Nodo(int fil=0,int col=0,T valor=0):vfil(fil),vcol(col),valor(valor),pfil(nullptr),pcol(nullptr){};
    friend class sparse_matrix<T>;
};
template <class T>
class sparse_matrix {
public:

    //CONSTRUCTOR DESTRUCTOR
    sparse_matrix();
    sparse_matrix( int nrows, int ncols);
    sparse_matrix( const sparse_matrix<T>& old );
    ~sparse_matrix();

    //SOBRECARGA OPERADORES
    const sparse_matrix<T>& operator=( const sparse_matrix& old );
    sparse_matrix<T> operator+( const sparse_matrix& rhs ) const;
    sparse_matrix<T> operator*( const sparse_matrix& rhs ) const;
    bool operator==( const sparse_matrix& rhs ) const;

    //MODIFICAR MATRIZ
    void put( int r, int c, const T& value );
    void make_zero( int r, int c );
    void resize( int nrows, int ncols );


    //OBTENER DATOS DE MATRIZ
    bool is_zero( int r, int c) const;
    T get( int r, int c ) const;
    int num_rows() const;
    int num_cols() const;
    void print_row( int r ) const;
    void print_col( int c ) const;
    void mostrar()const;
private:
    void clear();
    vector<Nodo<T>*> filas;
    vector<Nodo<T>*> columnas;
    int nfilas;
    int ncolumnas;

};

template<class T>
sparse_matrix<T>::sparse_matrix():nfilas(0),ncolumnas(0){};
template<class T>
sparse_matrix<T>::sparse_matrix( int nrows, int ncols):nfilas(nrows),ncolumnas(ncols){
    filas.assign(nrows,nullptr);
    columnas.assign(ncols,nullptr);
}
template<class T>
sparse_matrix<T>::sparse_matrix( const sparse_matrix<T>& old ){
    *this=old;
}
template<class T>
sparse_matrix<T>::~sparse_matrix(){
    this->clear();
}



template<class T>
const sparse_matrix<T>&sparse_matrix<T>::operator=( const sparse_matrix& old ){
    this->clear();
    this->resize(old.nfilas,old.ncolumnas);
    Nodo<T>*aux;
    for(int i=0;i<old.nfilas;i++){
        aux=old.filas[i];
        while(aux!=nullptr){
            this->put(aux->vfil,aux->vcol,aux->valor);
            aux=aux->pfil;
        }
    }
}
template<class T>
sparse_matrix<T> sparse_matrix<T>::operator+( const sparse_matrix& rhs ) const{
    Nodo<T>*aux,*aux2;

    if(rhs.nfilas==nfilas&&rhs.ncolumnas==ncolumnas){
        sparse_matrix<T> temp(*this);
        for(int i=0;i<nfilas;i++){
            aux=temp.filas[i];
            aux2=rhs.filas[i];
            while(aux2!=nullptr){
                //cout<<"i"<<i<<endl;
                if(aux==nullptr||aux->vcol>aux2->vcol){
                    //cout<<"caso 1"<<endl;
                    temp.put(aux2->vfil,aux2->vcol,aux2->valor);
                    aux2=aux2->pfil;
                }
                else if(aux->vcol==aux2->vcol){
                    //cout<<"caso 2"<<endl;
                    aux->valor+=aux2->valor;
                    aux2=aux2->pfil;
                    aux=aux->pfil;

                }
                else if(aux->vcol<aux2->vcol){
                   //cout<<"caso 3"<<endl;
                    aux=aux->pfil;
                }
            }
        }
        return temp;
    }
    else
        cout<<"no se pueden sumar las matrices "<<endl;
}
template<class T>
sparse_matrix<T> sparse_matrix<T>::operator*( const sparse_matrix& rhs ) const{
    if(rhs.nfilas==ncolumnas){
        sparse_matrix<T> temp(nfilas,rhs.ncolumnas);
        Nodo<T>*aux,*aux2;
        int con;
        for(int i=0;i<nfilas;i++){
            for(int j=0;j<rhs.ncolumnas;j++){
                aux2=rhs.columnas[j];
                aux=filas[i];
                con=0;
                while(aux2!=nullptr&&aux!=nullptr){
                  //  cout<<"i "<<i<<"j "<<j<<aux->valor<<" "<<aux2->valor<<endl;
                    if(aux->vcol>aux2->vfil){
                        //cout<<"caso 1"<<endl;
                        aux2=aux2->pcol;
                    }
                    else if(aux->vcol==aux2->vfil){
                        //cout<<"caso 2"<<endl;
                        con+=(aux->valor*aux2->valor);
                        aux2=aux2->pcol;
                        aux=aux->pfil;

                    }
                    else if(aux->vcol<aux2->vfil){
                        //cout<<"caso 3"<<endl;
                        aux=aux->pfil;
                    }
                   // cout<<"con"<<con<<endl;
                }
                if(con!=0)temp.put(i,j,con);
            }
        }
        return temp;
    }
    else
        cout<<"No se puede multiplicar"<<endl;
}
template<class T>
bool sparse_matrix<T>:: operator==( const sparse_matrix& rhs ) const{
    Nodo<T> *aux,*aux2;
    if(nfilas!=rhs.nfilas||ncolumnas!=rhs.ncolumnas)return false;
    for(int i=0;i<nfilas;i++){
        aux=filas[i];
        aux2=rhs.filas[i];
        while(aux!=nullptr&&aux2!=nullptr){
            if(aux->vcol!=aux2->vcol||aux->valor!=aux2->valor)
                return false;
            aux=aux->pfil;
            aux2=aux2->pfil;
        }
    }
    return true;
}


template<class T>
void sparse_matrix<T>:: put( int f, int c, const T& value ){
    Nodo<T>*nuevo=new Nodo<T>(f,c,value);
    Nodo<T>*ac,*an;
    if(filas[f]==nullptr){
        filas[f]=nuevo;
    }
    else{
        ac=filas[f];
        an=ac;
        while(ac!=nullptr&&ac->vcol<c){
            an=ac;
            ac=ac->pfil;
        }
        if(ac!=nullptr&&ac->vcol==c){
            ac->valor=value;
        }
        else if(ac==filas[f]){
            nuevo->pfil=ac;
            filas[f]=nuevo;
        }
        else if(ac==nullptr){
            an->pfil=nuevo;
        }
        else{
            an->pfil=nuevo;
            nuevo->pfil=ac;
        }
    }
    if(columnas[c]==nullptr){
        columnas[c]=nuevo;
    }
    else{
        ac=columnas[c];
        an=ac;
        while(ac!=nullptr&&ac->vfil<f){
            an=ac;
            ac=ac->pcol;
        }
        if(ac!=nullptr&&ac->vfil==f){
            ac->valor=value;
        }
        else if(ac==columnas[c]){
            nuevo->pcol=ac;
            columnas[c]=nuevo;
        }
        else if(ac==nullptr){
            an->pcol=nuevo;
        }
        else{
            an->pcol=nuevo;
            nuevo->pcol=ac;
        }
    }


}
template<class T>
void sparse_matrix<T>:: make_zero( int f, int c ){
    Nodo<T>*ac,*an;
    ac=filas[f];
    an=ac;
    while(ac!=nullptr&&ac->vcol!=c){
        an=ac;
        ac=ac->pfil;
    }
    if(ac==nullptr){
        cout<<"Ya es cero"<<endl;
        return;
    }
    an->pfil=ac->pfil;
    if(filas[f]==ac)filas[f]=nullptr;
    delete ac;
}
template<class T>
void sparse_matrix<T>::resize( int nrows, int ncols ){
    if(ncols!=ncolumnas)columnas.resize(ncols);
    if(nrows!=nfilas)filas.resize(nrows);
    nfilas=nrows;
    ncolumnas=ncols;
}
template<class T>
void sparse_matrix<T>::clear(){
    Nodo<T>*ac,*an;
    if(filas.size()==0)return;
    for(int i=0;i<nfilas;i++){
        ac=filas[i];
        while(ac!=nullptr){
            Nodo<T>*an;
            an=ac;
            ac=ac->pfil;
            delete an;
        }
    }

}


template<class T>
bool sparse_matrix<T>:: is_zero( int f, int c) const{

    Nodo<T>*aux=filas[f];
    while(aux!=nullptr){
        if(aux->vcol==c)return false;
        aux=aux->pfil;
    }
    return true;
}
template<class T>
T sparse_matrix<T>::get( int f, int c ) const{
    Nodo<T>*aux=filas[f];
    while(aux->pfil!=nullptr&&aux->vcol!=c){
        aux=aux->pfil;
    }
    if(aux->vcol==c)return aux->valor;
    return 0;

}
template<class T>
int sparse_matrix<T>::num_rows() const{
    return nfilas;
}
template<class T>
int sparse_matrix<T>::num_cols() const{
    return ncolumnas;
}
template<class T>
void sparse_matrix<T>::print_row( int f ) const{
    Nodo<T>*aux=filas[f];
    for(int i=0;i<ncolumnas;i++){
        if(aux!=nullptr&&aux->vcol==i){
            cout<<aux->valor<<" ";
            aux=aux->pfil;
        }
        else
            cout<<"0 ";
    }
    cout<<endl;

}
template<class T>
void sparse_matrix<T>::print_col( int c ) const{
    Nodo<T>*aux=columnas[c];
    for(int i=0;i<nfilas;i++){
        if(aux!=nullptr&&aux->vfil==i){
            cout<<aux->valor<<" ";
            aux=aux->pcol;
        }
        else
            cout<<"0 ";
    }
    cout<<endl;

}
template<class T>
void sparse_matrix<T>::mostrar() const{
    cout<<endl;
    for(int i=0;i<nfilas;i++){
        print_row(i);
    }
}

#endif

