#include "sparse_matrix.h"
#include <iostream>



int main(){
    sparse_matrix<int> A(4,4);
    A.put(0,1,4);
    A.put(0,0,5);
    A.put(0,3,6);
    A.put(0,2,7);
    A.print_row(0);
    A.print_col(2);
    A.mostrar();
    sparse_matrix<int>B(A);
    B.put(1,2,8);
    B.resize(4,5);
    B.put(1,4,9);
    B.put(2,3,1);
    B.put(2,3,5);
    B.put(0,1,9);
    B.mostrar();
    A.mostrar();
    cout<<"funcion GET"<<endl;
    cout<<B.get(1,3)<<endl;
    cout<<B.get(1,4)<<endl;
    cout<<"funcion isZERO"<<endl;
    cout<<B.is_zero(1,3)<<endl;
    cout<<B.is_zero(1,4)<<endl;
    cout<<"funcion MAKEZERO"<<endl;
    B.make_zero(1,3);
    B.make_zero(1,4);
    B.mostrar();
    cout<<"operador =="<<endl;
    sparse_matrix<int> C(B);
    bool a=C==B;
    cout<<a<<endl;
    a=A==B;
    cout<<a<<endl;
    cout<<"operador +"<<endl;
    sparse_matrix<int> D;
    C.put(2,2,5);
    C.put(3,0,8);
    C.mostrar();
    B.mostrar();
    D=C+B;
    D.mostrar();
    cout<<"operador *"<<endl;
    C.resize(4,4);
    C.mostrar();
    D.mostrar();
    (C*D).mostrar();
    cout<<"A";
}
