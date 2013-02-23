/*
  Name  		: matrix_sample_code.cpp
  Copyright		:    
  Author		: Hrushikesh Vasista
  Date			: 23-02-13 20:10
  Version		: 	
  Description	: Sample code to illustrate the use of "covariance()" function.(using matrix.h v2.0)
*/


#include <iostream>
#include <conio.h>
#include "matrix.h"

using namespace std;


int main()
{
     //Matrix containing the sample data
     matrix X(5,3);
     
     //Matrix to hold the covariances
     matrix Ans;
     
     cout<<"\nEnter the elements of X:";
     
     //Accepting the elements
     X.mat_ele_ip();
     
     //Displaying the matrix
     cout<<"\n[X] = \n";
     X.display();


     //Get the covariance values
     Ans = X.covariance();
    
     //Display the answer
     cout<<"\nCov([X]) = \n";
     Ans.display();
     
     getch();
     
     return 0;
 }
 
