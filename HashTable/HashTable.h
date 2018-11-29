
#ifndef HASHTABLE
#define HASHTABLE

#include <bits/stdc++.h>

using namespace std;
int nextPrime(int a){
    int i, j, count, num;
    for (i = a + 1; 1; i++){
        for (j = 2, count = 0; j <= i; j++){
            if (i%j == 0){
                count++;
            }
        }
        if (count == 1){
            return i;
            break;
        }
    }
}

int doublehash(int a,int tam){
        return tam-(a%tam);
}


template <typename Key>
class hashi
{
    public:
    size_t operator() ( const Key & k ) const;
};

template <>
class hashi<string>
{
public:
    size_t operator()( const string & key )
    {
        size_t hashVal = 0;
        for( char ch : key )
        hashVal = 37 * hashVal + ch;
        return hashVal;
    }
};
template <>
class hashi<int>
{
public:
    size_t operator()( const int & key ){
        return key;
    }
};

template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable( int size = 101 ): array(nextPrime(size))
	{ makeEmpty( ); }
	bool contains( const HashedObj & x ) const;
	void makeEmpty( );
	bool insert( const HashedObj & x );
	//bool insert( HashedObj && x );
	bool remove( const HashedObj & x );
	enum EntryType { ACTIVE, EMPTY, DELETED };
	void mostrar(){
        for(int i=0;i<array.size();i++){
            cout<<array[i].element<<" ";
        }
        cout<<endl;

	}

private:
struct HashEntry
	{
        HashedObj element;
        EntryType info;
        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY ): element{ e }, info{ i } { }
        HashEntry( HashedObj && e, EntryType i = EMPTY ): element{ std::move( e ) }, info{ i } { }
	};
	vector<HashEntry> array;
	int currentSize;
	bool isActive( int currentPos ) const;
	int findPos_L( const HashedObj & x ) const;
	int findPos_C( const HashedObj & x ) const;
	int findPos_D( const HashedObj & x ) const;
	void rehash(){
        vector<HashEntry> oldArray = array;
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }
	size_t myhash( const HashedObj & x ) const{
        static hashi<HashedObj> hf;
        return hf(x) % array.size( );
    }



};

template<typename HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
	currentSize = 0;
	for( auto & entry : array )
		entry.info = EMPTY;
}
template<typename HashedObj>
bool HashTable<HashedObj>::contains( const HashedObj & x ) const{
	return isActive( findPos( x ) );

}
//DOBLE REHASH
template<typename HashedObj>
int HashTable<HashedObj>::findPos_D( const HashedObj & x ) const{
	int currentPos = myhash( x );
	int offset = doublehash(currentPos,array.size());
	if(array[currentPos].element==x)return -1;
	while(array[currentPos].info!=EMPTY&&array[currentPos].element!=x){
            currentPos+=offset;
            cout<<"valor: "<<x<<"  hash: "<<currentPos<<endl;
		if( currentPos >= array.size( ) )
			currentPos -= array.size( );
	}
	return currentPos;
}


//LINEAR

template<typename HashedObj>
int HashTable<HashedObj>::findPos_L( const HashedObj & x ) const{
	int currentPos = myhash( x );
	if(array[currentPos].element==x)return -1;
	while(array[currentPos].info!=EMPTY&&array[currentPos].element!=x){
        currentPos++;
		if( currentPos >= array.size( ) )
			currentPos -= array.size( );
	}
	return currentPos;
}


//CUADRATICA

template<typename HashedObj>
int HashTable<HashedObj>::findPos_C( const HashedObj & x ) const{
    int offset =1;
	int currentPos = myhash( x );
	if(array[currentPos].element==x)return -1;
	while(array[currentPos].info!=EMPTY&&array[currentPos].element!=x){
        currentPos += offset;
		offset += 2;
		if( currentPos >= array.size( ) )
			currentPos -= array.size( );
	}
	return currentPos;
}



template<typename HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const{
	return array[ currentPos ].info == ACTIVE;
}
template<typename HashedObj>
bool HashTable<HashedObj>::insert( const HashedObj & x )
{
// Insert x as active
    int currentPos = findPos_L( x );
    //int currentPos = findPos_C( x );
    //int currentPos = findPos_D( x );
    if(currentPos<0)return false;
    if( isActive( currentPos ) )
        return false;

    array[ currentPos ].element = x;
    array[ currentPos ].info = ACTIVE;
    // Rehash; see Section 5.5
    if( ++currentSize > array.size( ) / 2 )
        rehash( );
    return true;
}

template<typename HashedObj>
bool HashTable<HashedObj>::remove( const HashedObj & x )
{
int currentPos = findPos( x );
if( !isActive( currentPos ) )
return false;
array[ currentPos ].info = DELETED;
return true;
}

#endif
