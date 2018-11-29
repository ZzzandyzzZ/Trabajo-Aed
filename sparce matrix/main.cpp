#include <cstdio>
#include "SparceMatrix.h"

using namespace std;
int main()
{
    vector<vector<int> > m(4);
    for(int i=0;i<4;i++)
        m[i].resize(4);
    m[0][3]=3;
    m[1][1]=4;
    m[0][1]=6;
    m[2][2]=7;
    m[3][0]=9;
    SparceMatrix<int> A(m);
    SparceMatrix<int> B;
    B.insert(0,3,30);
    B.insert(2,3,20);
    B.insert(1,2,10);
    cout<<"Matriz A"<<endl;A.mostrar_l();
    cout<<"Matriz B"<<endl;B.mostrar_l();
    SparceMatrix<int> C=A+B;
    cout<<"Matriz C"<<endl;C.mostrar_l();
    SparceMatrix<int> D=A-B;
    cout<<"Matriz D"<<endl;D.mostrar_l();
    A.insert(0,2,5);
    A.insert(0,3,10);

    A.insert(5,3,10);
    A.insert(4,0,13);
    A.mostrar_l();
    A.borrar(0,3);
    A.borrar(7);
    A.mostrar_l();
    A.find(7);
    A.find(6);

    return 0;
}
