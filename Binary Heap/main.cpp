#include "BinaryHeap.h"
#include<iostream>
using namespace std;


int main(){
    vector<int> A;
    int con=0;
    for(int i=1;i<10;i++)A.push_back(i);
    BinaryHeap<int> a;
    BinaryHeap<int> b(A);
    cout<<a.isEmpty()<<endl;
    /*
    a.deleteMin();
    for(int i=10;i>0;i--)a.insert(i);
    a.graficar("b");
    */
    a.insert(4);
    a.insert(3);
    a.insert(7);
    a.insert(9);
    a.insert(6);
    a.insert(2);
    a.graficar("b");
    /*
    cout<<b.findMin()<<endl;
    b.graficar("a"+to_string(con++));
    b.deleteMin();
    b.graficar("a"+to_string(con++));
*/


}
