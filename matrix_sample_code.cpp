/*
  Name:         matrix_sample_code.cpp
  Copyright:    Hrushikesh Vasista
  Author:       Hrushikesh Vasista
  Date: 19-01-13 18:45
  Description:   Sample code to illustrate the use of 'matrix' class
*/

#include <iostream>
#include <conio.h>
#include "matrix.h"

using namespace std;

int main()
{    
    matrix A(2,2),B(3,3),C(3,3);
    float det;
    
    A.order_ip(3,3);
    
    cout<<"\nEnter elements of [A]: ";
    A.mat_ele_ip();
    
    cout<<"\nEnter elements of [B]: ";
    B.mat_ele_ip();
    
    //Editing the first element of [A]
    A.edit(4,0,0);
    
    cout<<"\n\n[A] = \n"; 
    A.display();
    
    cout<<"\n\n[B] = \n"; 
    B.display();
    
    cout<<"\n\n[C] = \n"; 
    C.display();
    
    //Addition
    C= A+B;
    
    cout<<"\n\n[A]+[B] = \n"; 
    C.display();
    
    //Subtraction
    C= A-B;
    
    cout<<"\n\n[A]-[B] = \n"; 
    C.display();
    
    //Scalar multiplication
    C= 1.5*C;
    cout<<"\n\n1.5*[C] = \n"; 
    C.display();
    
    //Scalar multiplication
    C= C*2;
    
    cout<<"\n\n[C]*2 = \n"; 
    C.display();
    
    //matrix multiplication
    C= A*B;
    
    cout<<"\n\n[A]*[B] = \n"; 
    C.display();
    
    //Transpose
    B.transpose();
    
    cout<<"\n\n[B]' = \n"; 
    B.display();
    
    //Determinant
    det= A.determinant();
    
    cout<<"\n\ndet([A])= "<<det;
    
    //Inverse
    C= A.inverse();
    
    cout<<"\n\n[A]^-1= \n";
    C.display();

    getch();

    return 0;
}
