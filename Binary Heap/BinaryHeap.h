#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>
#include <iostream>
#include <stdexcept>

#include<cstdlib>
#include <string>
#include <fstream>
#define to_string( x ) static_cast< std::ostringstream & >(( std::ostringstream() << std::dec << x ) ).str()
#include <sstream>

#define L(i) 2*i
#define R(i) 2*i+1

using namespace std;


template <typename Comparable>
class BinaryHeap
{
    public:
    explicit BinaryHeap( int capacity =0 ):currentSize(capacity){};

    explicit BinaryHeap( const vector<Comparable> & items );

    bool isEmpty( ) const;
    const Comparable & findMin( ) const;

    void insert( const Comparable & x );

    void deleteMin( );
    void deleteMin( Comparable & minItem );
    void makeEmpty( );


    void graficar(string name);
    private:
    void recorrer(ofstream&in);
    int currentSize;
    vector<Comparable> array;
    void buildHeap( );
    void percolateDown( int hole );
};

template <class Comparable>
BinaryHeap<Comparable>::BinaryHeap( const vector<Comparable> & items ): array( items.size( ) + 10 ), currentSize{ items.size( ) }
{
    for( int i = 0; i < items.size( ); ++i )
    array[ i + 1 ] = items[ i ];
    buildHeap( );
}
template <class Comparable>
void BinaryHeap<Comparable>::buildHeap( )
{
    for( int i = currentSize / 2; i > 0; --i )
    percolateDown( i );
}

template<class Comparable>
bool BinaryHeap<Comparable>::isEmpty() const{
    return currentSize==0;
}
template<class Comparable>
const Comparable & BinaryHeap<Comparable>::findMin() const {
    return array[1];

}


template <class Comparable>
void BinaryHeap<Comparable>::insert( const Comparable & x ){


    if(currentSize==0){
        array.resize(2);
        array[1]=x;
        currentSize++;
        return;
    }
    this->graficar("b");
    if( currentSize == array.size( ) - 1 )
        array.resize( array.size( ) * 2 );

    int hole = ++currentSize;
    Comparable copy = x;
    array[ 0 ] = std::move( copy );
    for( ; x < array[ hole / 2 ]; hole /= 2 )
        array[ hole ] = std::move( array[ hole / 2 ] );
    array[ hole ] = std::move( array[ 0 ] );
}

template <class Comparable>
void BinaryHeap<Comparable>::deleteMin( )
{
    if( this->isEmpty( ) ){
        //throw invalid_argument("Intenta eliminar en una lista vacia");
        cout<<"Intenta eliminar en una lista vacia"<<endl;
        return;
    }
    array[ 1 ] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
}
template <class Comparable>
void BinaryHeap<Comparable>::deleteMin( Comparable & minItem )
{
    if( this->isEmpty( ) ){
        //throw invalid_argument("Intenta eliminar en una lista vacia");
        cout<<"Intenta eliminar en una lista vacia"<<endl;
        return;
    }
    minItem = std::move( array[ 1 ] );
    array[ 1 ] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
}
template <class Comparable>
void BinaryHeap<Comparable>::percolateDown( int hole )
{
    int child;
    Comparable tmp = std::move( array[ hole ] );
    for( ; hole * 2 <= currentSize; hole = child )
    {
            child = hole * 2;
        if( child != currentSize && array[ child + 1 ] < array[ child ] )
            ++child;
        if( array[ child ] < tmp )
            array[ hole ] = std::move( array[ child ] );
        else
            break;
    }
    array[ hole ] = std::move( tmp );
}

template<class Comparable>
void BinaryHeap<Comparable>::graficar(string name){
    ofstream in("a.txt");
    in<<"digraph G{\n";
    recorrer(in);
    in<<"}";
    in.close();
    string out="dot -Tpng a.txt -o "+name+".png";
    char*a=&out[0];
    system(a);
    out="start "+name+".png";
    a=&out[0];
    system(a);

}

template<class Comparable>
void BinaryHeap<Comparable>::recorrer(ofstream&in){
    string a,b;
    a="a[shape =record label=\"";
    for(int i=1;i<currentSize;i++){
        a+=(to_string(array[i])+"|");
    }
    a+=(to_string(array[currentSize])+"\"]");
    in<<a;
    for(int i=1;i<=currentSize;i++){
        if(L(i)>currentSize)
            return;
        b=to_string(array[L(i)]);
        a=to_string(array[i]);
        in<<a+"->"+b+"\n";
        if(R(i)>currentSize)
            return;
        b=to_string(array[R(i)]);
        a=to_string(array[i]);
        in<<a+"->"+b+"\n";
    }

}

#endif // BINARYTREE_H
