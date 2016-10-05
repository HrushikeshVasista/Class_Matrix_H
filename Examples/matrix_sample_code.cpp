/*Name			: matrix_sample_code.cpp  
  Author		: Hrushikesh Vasista  
  Version		: 3.2
  Description	: Sample code to illustrate the use of "matrix" class
*/


#include <iostream>
#include "matrix.hpp"

using namespace std;

void display(matrix a){

	int rows = a.getRow();
	int columns = a.getColumn();

	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			cout<<a.get_element(i, j);
			cout<<"\t";
		}
		cout<<"\n";
	}

	cout<<"\n";
}


int main()
{
     float C_elements[] = {2,-1,0,6,-9,1,8,4,0};
     float Sample_data[] = {5,-4,3,10,65,-89,29,34,-19,13,18,-2,0,34,22};
     float B_elements[] = {0,1,0,1,0,1};

     //Creating a matrix
     matrix A;
     matrix B(2,3);
     const matrix C(3,3, C_elements);
     matrix D(3,2);
     matrix Inv;
     matrix Ans;


     //Ordering a matrix

     A.order_ip(3,3);

     //Editing an element in matrix
     A.edit(-10,1,2);

     cout<<"Line: "<<__LINE__<<"\n";
	 B.mat_ele_ip_list(B_elements);
     //Displaying a matrix
     cout<<"\n[A]=\n";
     display(A);

     //get an element
     float element=A.get_element(1,2);
     cout<<"\n\nA(1,2) = "<<element<<"\n";

     cout<<"\n\n[B]=\n";
     display(B);


     cout<<"\n\n[C]=\n";
     display(C);

     D.mat_ele_ip_list(C_elements);

     cout<<"\n\n[D]=\n";
     display(D);






     //Matrix addition
     cout<<"Line: "<<__LINE__<<"\n";
     Ans = C + A;
     cout<<"\n\nMatrix addition\n-----------------------------";
     cout<<"\n[A]+[C] = \n" ;
     display(Ans);

     //matrix subtraction
     cout<<"Line: "<<__LINE__<<"\n";
     Ans = C - A;
     cout<<"\n\nMatrix subtraction\n-----------------------------";
     cout<<"\n[C]-[A] = \n" ;
     display(Ans);

     //matrix multiplication
     cout<<"Line: "<<__LINE__<<"\n";
     Ans = D * B;
     cout<<"\n\nMatrix multiplication\n-----------------------------";
     cout<<"\n[D]*[B] =\n" ;
     display(Ans);

     cout<<"Line: "<<__LINE__<<"\n";
     Ans = D * B*0.5;
     cout<<"\n\nMatrix multiplication(scalar)\n-----------------------------";
     cout<<"\n([D]*[B])*0.5 = \n" ;
     display(Ans);

     cout<<"Line: "<<__LINE__<<"\n";
     Ans = 2* D * B *0.5;
     cout<<"\n\n2*([D]*[B])*0.5 = [Ans]\n-----------------------------" ;
     display(Ans);

     //Matrix transpose
     cout<<"Line: "<<__LINE__<<"\n";
     A.transpose();
     cout<<"\n\nMatrix transpose\n-----------------------------";
     cout<<"\n[Ans]' = \n" ;
     display(Ans);

     //matrix determinant
     cout<<"Line: "<<__LINE__<<"\n";
     float det = C.determinant();
     cout<<"\n\nMatrix determinant\n-----------------------------";
     cout<<"\ndet([C])= "<<det<<"\n";

     //Matrix inverse
     cout<<"Line: "<<__LINE__<<"\n";
     Inv = C.inverse();
     cout<<"\n\nMatrix inverse\n-----------------------------";
     cout<<"\n[C]^-1 = \n" ;
     display(Inv);

     //matrix covariance
     cout<<"Line: "<<__LINE__<<"\n";
     matrix X(5,3);
     X.mat_ele_ip_list(Sample_data);
     Ans = X.covariance();
     cout<<"\n\nCovariance matrix\n-----------------------------";
     cout<<"\n[X] = \n";
     display(X);
     cout<<"\nCov([X]) = \n" ;
     display(Ans);

     //matrix appending
     cout<<"Line: "<<__LINE__<<"\n";
     Ans = A.append_h(C);
     cout<<"\n\nAppending matrices (horizontal)\n-----------------------------";
     cout<<"\n[A C] = \n" ;
     display(Ans);

     cout<<"Line: "<<__LINE__<<"\n";
     Ans = C.append_v(A);
     cout<<"\n\nAppending matrices (vertical)\n-----------------------------";
     cout<<"\n[C]\n[A] = \n" ;
     display(Ans);

     //Shorthand operators
     cout<<"Line: "<<__LINE__<<"\n";
     A += C;
     cout<<"\n\nMatrix addition (using shorthand operator +=)\n-----------------------------";
     cout<<"\n[A]+=[B] = \n" ;
     display(A);

     cout<<"Line: "<<__LINE__<<"\n";
     A -= C;
     cout<<"\n\nMatrix subtraction (using shorthand operator -=)\n-----------------------------";
     cout<<"\n[A]-=[B] = \n" ;
     display(A);

     cout<<"Line: "<<__LINE__<<"\n";
     B *= D;
     cout<<"\n\nMatrix multiplication (using shorthand operator *=)\n-----------------------------";
     cout<<"\n[B]*=[D] = \n" ;
     display(B);

     cout<<"Line: "<<__LINE__<<"\n";
     B *= 2;
     cout<<"\n\n[B]*=2 = \n" ;
     display(B);

     //matrix equality
     cout<<"Line: "<<__LINE__<<"\n";
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

     cout<<"\n\n"<<"Line: "<<__LINE__<<"\n";
     try
     {
    	 B.order_ip(-1, 3);
     }catch (int e) {
    	 cout<<"Error";

	}

     return 0;
}
