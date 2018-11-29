
#include "HashTable.h"

using namespace std;



int main(){
	HashTable<int> a;


	a.insert(90);
	a.insert(80);
	a.insert(97);
	a.insert(200);
	a.insert(303);

	a.insert(406);
	a.insert(509);
	//a.insert(103);
/*
	for(int i=1;i<105;i++)
        a.insert(i);
    */
	a.mostrar();
}
