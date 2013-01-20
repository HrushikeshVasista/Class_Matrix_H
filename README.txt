  Author      : Hrushikesh Vasista
  e-mail    : hmvasista@gmail.com
  16th Jan, 2013
  
  User guide for "matrix.h"
  ===========================
  
  CONTENTS
  ===========================
  I.    INTRODUCTION
  II.   FEATURES
  III.  HARDWARE / SOFTWARE REQUREMENTS
  IV.   KNOWN ISSUES

I. INTRODUCTION
=============================
The 'matrix' class (henceforth referred to as 'matrix') aims at providing the basic operations involving matrices, 
which can be used in C++ programs. It makes the programmer easy to realize the mathematical operations as normally done 
when solving by hand. With 'matrix' its now less tiring to perform calculations on large matrices.

II. FEATURES
============================
All the features of 'matrix' are provided in the form of 'matrix.h'. So just include 'matrix.h' in your code to
access these features:

a. Dimensioning a matrix (by specifying rows and columns at declaration)
b. Dimensioning a matrix, with elements initialised (by providing the base matrix at declaration)
c. Dimensioning of a matrix (by changing the order of the existing matrix)
d. Editing an element in the matrix
e. Printing the matrix
f. Assigning the elements to a matrix
g. Addition of matrices
h. Subtraction of matrices
i. Assigning one matrix to another
j. Scalar multiplication
k. Multplication of matrices
l. Transpose of a matrix
m. Inverse of a matrix
n. Determinant of a matrix


a. Dimensioning a matrix (by specifying rows and columns at declaration)
==========================================================================

Syntax - matrix <matrix_identifier>(<rows>,<columns>);

<matrix_identifier>	: Valid C-identifier
<rows>,<columns>	: integers	

This makes <matrix_identifier> a matrix of <rows> x <columns>. All elements are initialised to 0

Eg: matrix A(3,2); //[A] = 3x2


b. Dimensioning a matrix, with elements initialised (by providing the base matrix at declaration)
===================================================================================================

Syntax - matrix <matrix_identifier>(<init_matrix>);

<matrix_identifier>	: Valid C-identifier
<init_matrix>		: another matrix of the the type 'matrix'	

This makes <matrix_identifier> a matrix same as <init_matrix> ie same order and elements.

Eg: If [B] is a 1x4 matrix as [1 2 3 4] then,

matrix B(A); //makes [B] a 1x4 matrix, initialised with elements = [1 2 3 4]


c. Dimensioning of a matrix (by changing the order of the existing matrix)
=============================================================================

Syntax - <matrix_identifier>.order_ip(<rows>,<columns>);

<matrix_identifier>	: existing matrix
<rows>,<columns>	: integers, required dimension	

This makes <matrix_identifier> a matrix of order <rows> x <columns> and all its elements initialised to 0.

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
     A.order_ip(1,4);   //Makes [A] of order 1x4

	 
d. Editing an element in the matrix
=============================================================================

Syntax - <matrix_identifier>.edit(<new_value>,<row>,<column>);

<matrix_identifier>	: existing matrix
<new_value>			: float, the new value
<rows>,<columns>	: integers, location where to edit. This is 0 indexed.

If the location value is invalid / out of bounds, then no changes would be made in the matrix.

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	
	[A]	 = 	|0      0|
			|0      0|
			|0      0|
			
	A.edit(1.23,2,1);	//Makes the element at 3rd row, 2nd column as 1.23
	 
	[A]  = 	|0      0|
			|0      0|
			|0   1.23|
			
    A.edit(98.3,3,2);	//No change, since location is out of bound
	A.edit(98.3,-1,2);	//No change, since invalid location
	

e. Printing the matrix
=============================================================================

Syntax - <matrix_identifier>.display();

<matrix_identifier>	: existing matrix

This prints all the elements of the given matrix of as per order ie <rows> x <columns>.

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
     A.display();   	//Displays [A]
	 
	0      0
	0      0
	0      0
	

f. Assigning the elements to a matrix
=============================================================================

Syntax - <matrix_identifier>.mat_ele_ip();

<matrix_identifier>	: existing matrix

This accepts all the elements of the given matrix of as per order ie <rows> x <columns>.

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
     A.mat_ele_ip();   	//Accepts the 6 elements of [A]
	 

	

g. Addition of matrices
=============================================================================

Syntax - <matrix_ans> = <matrix_1> + <matrix_2> ;

<matrix_ans>, <matrix_1>, <matrix_2>: existing matrices

The '+' operation performs the addition of the 2 matrices and returns the resultant matrix,
which is assigned to the matrix at LHS. The <matrix_ans> is re-ordered to accommodate the RHS 
and hence all previous data is lost and filled with the new ones.

Note: If there is a mismatch in the order between <matrix_1> and <matrix_2>, no addition is performed
and hence <matrix_ans> remains as before. 

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 matrix B(3,2);  	//Makes [B] of order 3x2
	 matrix C;  	    //Makes [C] of order 1x1
	 matrix D(1,4);  	//Makes [D] of order 1x4
	 
	 C= A+B;			// [C] is now 3x2 and contains A+B.
	 C= A+D;			// [C] remains unchanged, due to mismatch between [A] and [D].
	 
	 	

h. Subtraction of matrices
=============================================================================

Syntax - <matrix_ans> = <matrix_1> - <matrix_2> ;

<matrix_ans>, <matrix_1>, <matrix_2>: existing matrices

The '-' operation performs the subtraction of the 2 matrices and returns the resultant matrix,
which is assigned to the matrix at LHS. The <matrix_ans> is re-ordered to accommodate the RHS 
and hence all previous data is lost and filled with the new ones.

Note: If there is a mismatch in the order between <matrix_1> and <matrix_2>, no subtraction is performed
and hence <matrix_ans> remains as before. 

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 matrix B(3,2);  	//Makes [B] of order 3x2
	 matrix C;  	    //Makes [C] of order 1x1
	 matrix D(1,4);  	//Makes [D] of order 1x4
	 
	 C= A-B;			// [C] is now 3x2 and contains A-B.
	 C= A-D;			// [C] remains unchanged, due to mismatch between [A] and [D].
	 	 


i. Assigning one matrix to another
=============================================================================

Syntax - <matrix_1> = <matrix_2> ;

<matrix_1>, <matrix_2>: existing matrices

The '=' operation assigns the matrix on RHS to the matrix on LHS. The <matrix_1> is re-ordered to accommodate the RHS 
and hence all previous data is lost and filled with the new ones.

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 matrix B;  	    //Makes [B] of order 1x1
	 
	 A=B;			    // [A] is now 1x1 and contains elements of [B].
	 


j. Scalar multiplication
=============================================================================

Syntax - <matrix_ans> = k*<matrix_1> ;
		 <matrix_ans> = <matrix_1>*k ;

<matrix_ans>, <matrix_1>: existing matrices
k						: float

The '*' operation returns the <matrix_1> with each element multiplied by k .
The <matrix_ans> is re-ordered to accommodate the RHS and hence all previous data is lost and filled with the new ones.

Note: <matrix_1> remains unchanged (both, its order and elements remain unchanged)

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 matrix B;  	    //Makes [B] of order 1x1
	 
	 B=1.2*A;		    // [B] is now 3x2 and contains elements of [B] multiplied with 1.2, [A] remains unchanged.	 


k. Multplication of matrices
=============================================================================

Syntax - <matrix_ans> = <matrix_1> * <matrix_2> ;
		 
<matrix_ans>, <matrix_1>, <matrix_2>: existing matrices

The '*' operation returns the multiplication of <matrix_1> with <matrix_2>.
The <matrix_ans> is re-ordered to accommodate the RHS and hence all previous data is lost and filled with the new ones.

Note: <matrix_1> and <matrix_2> remain unchanged (both, its order and elements remain unchanged).
      If there is an order mismatch, then multiplication is not performed and <matrix_ans> remains unchanged. 

Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 matrix B(2,3);	    //Makes [B] of order 2x3
	 matrix C;	        //Makes [C] of order 1x1
	 matrix D;          //Makes [D] of order 1x1
	 
	 C=A*B;		       // [C] is now 3x3 and contains elements of [A] multiplied with [B].		 
	 C=A*D;		       // [C] is still 3x3 and unchanged. multiplication not performed..
	 
	 
l. Transpose of a matrix
=============================================================================

Syntax - <matrix_1>.transpose();

<matrix_1>: existing matrices, of order say m x n

This transposes the <matrix_1>.
The <matrix_1> is thus re-ordered to n x m, containing the previous elements itself, but in transposed 
manner.


Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 A.transpose();	    // [A] now has an order of 2x3
	 

	 
m. Inverse of a matrix
=============================================================================

Syntax - <matrix_2> = <matrix_1>.inverse();

<matrix_2>, <matrix_1>: existing matrices

This returns the inverse of the <matrix_1> to <matrix_2>.
The <matrix_2> is thus re-ordered to accommodate the RHS and hence all previous data is lost and filled with the new ones.

Note: The above is true only if <matrix_1> is a square matrix, with its determinant not equal to 0.
Incase of <matrix_1> being a non-square matrix / determinant =0, then inverse doesn't exist and hence
<matrix_2> remains unchanged.


Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 matrix B(3,3);  	//Makes [B] of order 3x3
	 matrix C;  		//Makes [C] of order 1x1
	 
	 C= A.inverse();	// [C] remains unchanged
	 C= B.inverse();	// [C] is now 3x3 and contains [B]^-1
	 



	 
n. Determinant of a matrix
=============================================================================

Syntax - <Det> = <matrix_1>.inverse();

<matrix_1>	: existing matrix
<det>		: float, determinant of <matrix_1> 

This returns the determinant of the <matrix_1> to <matrix_2>.
The <det> is contains the determinant of <matrix_1>.

Note: The above is true only if <matrix_1> is a square matrix.
Incase of <matrix_1> being a non-square matrix, then 0 is returned and hence <det> = 0.


Eg:  matrix A(3,2);  	//Makes [A] of order 3x2
	 matrix B(3,3);  	//Makes [B] of order 3x3
	 float det;  		//Makes [C] of order 1x1
	 
	 det= A.determinant();	// det = 0.
	 det= B.determinant();	// det contains determinant of [B] 
	 
	 

III. HARDWARE / SOFTWARE REQUREMENTS
======================================

1. The 'matrix.h' file is can be used on the compilers supporting Standard C++. 

2. The file 'matrix.h' must be present in the project folder.



IV. KNOWN ISSUES
======================================

1. The matrix elements are of type 'float'. Hence the range depends on the
   type of machine on which the code is running.
   Eg: 16-bit,32-bit, 64-bit will have different range for a 'float'

2. Matrices of type 'char' are not supported, and also the elements cannot be a character.

3. The precision of the float number is compiler dependent.

4. The execution of the program would cease if there is not enough memory.

5. If invalid order for a matrix is entered (eg: 0, -ve values), then a matrix of order 1x1 would be created instead.
