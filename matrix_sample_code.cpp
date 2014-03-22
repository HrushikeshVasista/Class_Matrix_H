/*
  Name			: matrix_sample_code.cpp
  Copyright		: Hrushikesh Vasista   
  Author		: Hrushikesh Vasista
  Date			: 12/11/2013 22:22
  Version		: 3.0	
  Description	: Sample code to illustrate the use of "matrix" class.(using matrix.h v3.0)
*/


#include <iostream>
#include <conio.h>
#include "matrix.h"

using namespace std;


int main()
{
     float C_elements[] = {2,-1,0,6,-9,1,8,4,0};
     float A_elements[] = {1,1,1,1,5,6,0,10,1};
     float Sample_data[] = {5,-4,3,10,65,-89,29,34,-19,13,18,-2,0,34,22};
     //Creating a matrix
     matrix A;
     matrix B(2,3);
     const matrix C(3,3,C_elements);
     matrix D(3,2);
     matrix Inv;
     
     
     //Ordering a matrix
     A.order_ip(3,3);
     
     //Editing an element in matrix
     A.edit(-10,1,2);
     
     //Filling elements of a matrix    
     cout<<"\nEnter 6 elements for [B]:";
     B.mat_ele_ip_user();    
     
     //Displaying a matrix
     cout<<"\n[A]=\n";     
     A.display();
     
     //get an element
     float element=A.get_element(1,2);
     cout<<"\n\nA(1,2) = "<<element<<"\n";

     cout<<"\n\n[B]=\n";     
     B.display();
     
     cout<<"\n\n[C]=\n";     
     C.display();
     
     //C.mat_ele_ip_list(C_elements);
     D.mat_ele_ip_list(C_elements);
     
     cout<<"\n\n[D]=\n";     
     D.display();  

     

     
     //Matrix addition
     matrix Ans = C + A;
     cout<<"\n\nMatrix addition\n-----------------------------";
     cout<<"\n[A]+[C] = \n" ;
     Ans.display();
     
     //matrix subtraction
     Ans = C - A;
     cout<<"\n\nMatrix subtraction\n-----------------------------";
     cout<<"\n[C]-[A] = \n" ;
     Ans.display();
     
     //matrix multiplication
     Ans = D * B;
     cout<<"\n\nMatrix multiplication\n-----------------------------";
     cout<<"\n[D]*[B] =\n" ;
     Ans.display();
     
     Ans = (D * B)*0.5;
     cout<<"\n\nMatrix multiplication(scalar)\n-----------------------------";
     cout<<"\n([D]*[B])*0.5 = \n" ;
     Ans.display();
     
     Ans = 2*(D * B)*0.5;
     cout<<"\n\n2*([D]*[B])*0.5 = [Ans]\n-----------------------------" ;
     Ans.display();
     
     //Matrix transpose
     Ans.transpose();
     cout<<"\n\nMatrix transpose\n-----------------------------";
     cout<<"\n[Ans]' = \n" ;
     Ans.display();
     
     //matrix determinant
     float det = C.determinant();
     cout<<"\n\nMatrix determinant\n-----------------------------";
     cout<<"\ndet([C])= "<<det<<"\n";
     
     //Matrix inverse
     Inv = C.inverse();
     cout<<"\n\nMatrix inverse\n-----------------------------";
     cout<<"\n[C]^-1 = \n" ;
     Inv.display();
     
     //matrix covariance
     matrix X(5,3);
     X.mat_ele_ip_list(Sample_data);
     Ans = X.covariance();
     cout<<"\n\nCovariance matrix\n-----------------------------";
     cout<<"\n[X] = \n";
     X.display();
     cout<<"\nCov([X]) = \n" ;
     Ans.display();
     
     //matrix appending
     Ans = A.append_h(C);
     cout<<"\n\nAppending matrices (horizontal)\n-----------------------------";
     cout<<"\n[A C] = \n" ;
     Ans.display();
     
     Ans = C.append_v(A);
     cout<<"\n\nAppending matrices (vertical)\n-----------------------------";
     cout<<"\n[C]\n[A] = \n" ;
     Ans.display();

     //Shorthand operators
     A += C;
     cout<<"\n\nMatrix addition (using shorthand operator +=)\n-----------------------------";
     cout<<"\n[A]+=[B] = \n" ;
     A.display();
     
     A -= C;
     cout<<"\n\nMatrix subtraction (using shorthand operator -=)\n-----------------------------";
     cout<<"\n[A]-=[B] = \n" ;
     A.display();
     
     B *= D;
     cout<<"\n\nMatrix multiplication (using shorthand operator *=)\n-----------------------------";
     cout<<"\n[B]*=[D] = \n" ;
     B.display();
     
     B *= 2;
     cout<<"\n\n[B]*=2 = \n" ;
     B.display();
     
     //matrix equality
     cout<<"\n\nMatrix equality\n-----------------------------";
     if(A==C)     
         cout<<"\n[A] equals [C]";
     else
         cout<<"\n[A] does not equal [C]\n";
     
     cout<<"\nNow setting B=D\n";
     B=D;
     
     if(B==D)
         cout<<"\n[B] equals [D]";
     else
         cout<<"\n[B] does not equal [D]";


     getch();
     
     return 0;
 }
 
