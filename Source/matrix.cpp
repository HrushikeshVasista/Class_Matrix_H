#include "matrix.hpp"
#include <new>
#include <cstddef>

/**
 * Default constructor, creates a matrix of order 0x0
 */
matrix::matrix(){

	resetOrder();
}


/**
 * Creates matrix of order m x n. If invalid order is passed creates a 0x0 matrix
 * throws: ALLOCATION_FAILURE
 */
matrix::matrix(int rhsRow, int rhsColumn) throw(int){

	//If valid order...
	if(isOrderValid(rhsRow, rhsColumn)){

		row = rhsRow;
		column = rhsColumn;

		makeMatrix();

		initializeElements();

	}

	else
		resetOrder();
}


/**
 * Creates a copy of given matrix if its order is valid, else creates a 0x0 matrix
 * throws: ALLOCATION_FAILURE
 */
matrix::matrix(const matrix& rhs) throw(int){


	//If valid matrix...
	if(isOrderValid(rhs.row, rhs.column)){

		//store the required order
		row = rhs.row;
		column = rhs.column;

		//Create space for the matrix
		makeMatrix();

		//Copy the elements
		initializeElements(rhs);

	}

	else
		resetOrder();

}



/**
 * Creates a matrix and initializes the elements as per the given order
 * throws: ALLOCATION_FAILURE
 */
matrix::matrix(int m, int n, const float *ele_list)
{

	if(isOrderValid(m, n)){

		//store the required order
		row = m;
		column = n;

		//Create space for mxn elements
		makeMatrix();



		for(int i=0;i<m*n;i++)
			p_mat[i] = ele_list[i];

		//initialise the elements as in the list
		for(int i=0;i<m*n;i++)
			p_mat[i] = ele_list[i];

	}
	else{

		resetOrder();
	}
}



matrix::~matrix(){

	//free the memory
	delete []p_mat;

}


/**
 * Returns the row of the matrix
 */
int matrix::getRow(){
	return row;
}


/**
 * Returns the column of the matrix
 */
int matrix::getColumn(){
	return column;
}


/**
 * Changes the order of the matrix. If order is invalid throws INVALID_ORDER exception
 * throws: ALLOCATION_FAILURE, INVALID_ORDER
 */
void matrix::order_ip(int rhsRow, int rhsColumn) throw(int){

	if(!isOrderValid(rhsRow, rhsColumn))
		throw INVALID_ORDER;

	//Clear previous order
	delete []p_mat;

	//Store new order
	row = rhsRow;
	column = rhsColumn;

	makeMatrix();

	//initialise all elements to 0
	initializeElements();

}


/**
 * Replaces the element at m,n with new_ele. If the m,n is invalid no change is made
 */
void matrix::edit(float new_ele, int m, int n){

	//check for bounds of the given location
	if((m < row) &&
			(n < column) &&
			(m >= 0) &&
			(n >= 0))

		p_mat[m*column + n] = new_ele;

}



/**
 * Returns the addition of 2 matrices. If the orders are incompatible throws OPERATION_FAILURE
 * throws: ALLOCATION_FAILURE, OPERATION_FAILURE
 */
matrix matrix::operator+(const matrix &rhs)const throw(int){

	//temporary matrix having order same as the caller matrix
	matrix ans(row, column);

	//Addition to be done only if order of both matrices are same
	if(!(isOrderValid(rhs.row, rhs.column) && isOrderMatches(rhs.row, rhs.column)))
		throw OPERATION_FAILURE;

	for(int i = 0; i < row*column; i++)
		ans.p_mat[i]= rhs.p_mat[i] + p_mat[i];

	return ans;

}



/**
 * Returns the difference of 2 matrices. If the orders are incompatible throws OPERATION_FAILURE
 * throws: ALLOCATION_FAILURE, OPERATION_FAILURE
 */
matrix matrix::operator-(const matrix &rhs)const{

	//temporary matrix having order same as the caller matrix
	matrix ans(row, column);

	//Subtraction to be done only if order of both matrices are same
	if(!(isOrderValid(rhs.row, rhs.column) && isOrderMatches(rhs.row, rhs.column)))
		throw OPERATION_FAILURE;

	for(int i=0;i<(row*column);i++)
		ans.p_mat[i] = p_mat[i] - rhs.p_mat[i];

	return ans;

}



/**
 * Assigns RHS to LHS. If the RHS is invalid matrix, then OPERATION_FAILURE is thrown
 * If the RHS and LHS are the same, then no assignment is made
 * throws: ALLOCATION_FAILURE, OPERATION_FAILURE
 */
void matrix::operator=(const matrix &rhs) throw(int){

	//to handle the case where A=A ie same matrices and is not an indicator matrix.
	if(!(this == &rhs) && isOrderValid(rhs.row, rhs.column))
	{
		//Make LHS matrix order same as RHS matrix, if not same
		if(!isOrderMatches(rhs.row, rhs.column))
			order_ip(rhs.row,rhs.column);

		//Assign RHS elements to LHS
		if(isOrderValid(row, column)){

			for(int i = 0; i < row*column; i++)
				p_mat[i] = rhs.p_mat[i];
		}
	}
	//else do nothing
}


/**
 * Performs the scalar multiplication result i.e n*[A]
 * throws: ALLOCATION_FAILURE
 */
matrix operator*(float scalar, const matrix &rhs) throw(int){

	//temporary matrix having order same as the multiplicand matrix
	matrix temp(rhs.row, rhs.column);

	//Multiply each element by the scalar
	for(int i=0;i<rhs.row*rhs.column;i++)
		temp.p_mat[i] = scalar * rhs.p_mat[i];

	return(temp);
}


/**
 * Returns the scalar multiplication result i.e [A]*n
 * throws: ALLOCATION_FAILURE
 */
matrix matrix::operator*(float scalar)const throw(int){

	//temporary matrix having order same as the multiplicand matrix
	matrix temp(row, column);

	for(int i=0;i<row*column;i++)
		temp.p_mat[i] = scalar*p_mat[i];

	return(temp);

}



matrix matrix::operator*(const matrix &rhs)const
{
	//temporary matrix having order = row of left multiplicand matrix and column of right multiplicand matrix
	matrix temp(row, rhs.column);

	//Multiplication to be done only of the order criteria is met
	if(!((column == rhs.row) && temp.isOrderValid(temp.row, temp.column)))
		throw OPERATION_FAILURE;

	float res = 0;
	int i,j,k;

	for(i = 0; i < row; i++){

		for(j = 0; j < rhs.column; j++){

			for(k = 0; k < rhs.row; k++){
				res += (p_mat[i*column + k] * rhs.p_mat[k*rhs.column + j]);
			}

			temp.p_mat[i*rhs.column+j] = res;

			res = 0;


		}//j loop ends

	}//i loop ends

	return(temp);

}


/**
 * Transposes the matrix
 * throws: ALLOCATION_FAILURE
 */
void matrix::transpose(void) throw(int){

	matrix temp(row, column);

	//transpose
	for(int i=0;i<column;i++){
		for(int j=0;j<row;j++){
			temp.edit(p_mat[j*column+i], i, j);
		}
	}

	//make the copy
	for(int i = 0; i < row*column; i++){
		p_mat[i] = temp.p_mat[i];
	}

	//swap order
	int tempColumn = column;
	column = row;
	row = tempColumn;

}



/**
 * Returns the inverse of the matrix. If no inverse exists NO_INVERSE_EXISTS exception is thrown
 * throws: NO_INVERSE_EXISTS, ALLOCATION_FAILURE
 */
matrix matrix::inverse(void)const throw(int){

	//temporary matrix = input matrix
	matrix temp_mat(row,row);

	//[I] matrix to calculate the inverse
	matrix inv(row,column);

	if(!(isOrderValid(row, column) && (row == column)))
		throw NO_INVERSE_EXISTS;


	int i, j, k, m, n, flagger = 0;
	float ratio = 0, temp = 0, count = 0;

	//start by considering answer as [I] matrix.
	for(i=0;i<row;i++)
		inv.p_mat[i*row+i] = 1;

	//Copy the input matrix is used to perform required operations
	for(i=0;i<row*row;i++)
		temp_mat.p_mat[i] = p_mat[i];


	for(i=0; i<row; i++){

		flagger = i;

		//find inverse by Gauss Elimination method.
		//Consider only the PD elements
		while(temp_mat.p_mat[i*row + i] == 0){

			//flagger indicates the Max No. of failed attempts of exchanging the diff columns.
			if(flagger == (row - 1)){

				throw NO_INVERSE_EXISTS;
			}

			else{

				flagger++;

				//swap the columns and check again
				for(k=0; k<row; k++){

					temp = temp_mat.p_mat[k*row+i];
					temp_mat.p_mat[k*row+i] = temp_mat.p_mat[k*row+flagger];
					temp_mat.p_mat[k*row+flagger] = temp;

					//whatever exchanges done to base matrix do similar changes to answer matrix
					temp = inv.p_mat[k*row+i];
					inv.p_mat[k*row+i] = inv.p_mat[k*row+flagger];
					inv.p_mat[k*row+flagger] = temp;
				}

			}//else ends

		} // while ends...repeat till (n-1) columns have been swapped ie max limit


		for(j=0;j<row;j++){

			if(j!=i){
				//find the ratio by considering only the PD elements
				ratio = temp_mat.p_mat[j*row+i] / temp_mat.p_mat[i*row+i];
			}
			else{
				continue;
			}

			for(k=0; k<row; k++){

				temp_mat.p_mat[j*row+k] = temp_mat.p_mat[j*row+k] - ratio * (temp_mat.p_mat[i*row+k]);
				inv.p_mat[j*row+k] = inv.p_mat[j*row+k] - ratio*(inv.p_mat[i*row+k]);

			}// k ends

			for(m=0; m<row; m++){

				count=0;

				for(n=0;n<row;n++){

					//check after every manipulation whether all elements of a row of input matrix are 0.
					if(temp_mat.p_mat[m*row+n] == 0)
						count++;

				}

				//If all elements of a row are 0...
				if(count == row){

					throw NO_INVERSE_EXISTS;
				}

			}//m loop ends

		}//j ends

	} //i ends

	//Divide each element of a row with corresponding PD element
	for(i=0;i<row;i++){

		for(j=0;j<row;j++){
			inv.p_mat[i*row+j] /= temp_mat.p_mat[i*row+i];
		}
	}

	return (inv);

}

/**
 * Returns the determinant of the matrix
 * throws: ALLOCATION_FAILURE, OPERATION_FAILURE, DETERMINANT_ZERO
 */
float matrix::determinant(void)const throw(int){

	//Calculate determinant only if square matrix else throw an exception
	if(!isOrderValid(row, column)){
		throw OPERATION_FAILURE;
	}


	//temporary matrix = input matrix
	matrix temp_mat(row,row);

	float determinant_value = 1;


	int i,j,k,m,n,flagger=0;
	float ratio=0,temp=0,count=0;

	for(i=0;i<row*row;i++)
		//the input matrix is used to perform required operations
		temp_mat.p_mat[i] = p_mat[i];


	for(i=0;i<row;i++)
	{
		flagger=i;

		//Consider only the PD elements
		while(temp_mat.p_mat[i*row+i] == 0)
		{
			if(flagger == (row-1))
				return 0;

			else
			{
				flagger++;

				for(k=0;k<row;k++)
				{
					temp = temp_mat.p_mat[k*row+i];
					temp_mat.p_mat[k*row+i] = temp_mat.p_mat[k*row+flagger];
					temp_mat.p_mat[k*row+flagger] = temp;
				}

			}//else ends

		} // while ends...repeat till (n-1) columns have been swapped ie max limit


		for(j=0;j<row;j++)
		{
			if(j!=i)
				//find the ratio by considering only the PD elements.
				ratio = temp_mat.p_mat[j*row+i] / temp_mat.p_mat[i*row+i];

			else
				continue;

			for(k=0;k<row;k++)
			{
				temp_mat.p_mat[j*row+k] -= ratio* temp_mat.p_mat[i*row+k];

			}// k ends

			for(m=0;m<row;m++)
			{
				count=0;
				for(n=0;n<row;n++)
				{
					if(temp_mat.p_mat[m*row+n]==0)
						count++;
				}

				if(count==row)
					return 0;

			}//m loop ends

		}//j ends

	} //i ends

	for(i=0;i<row;i++)
	{
		determinant_value *= temp_mat.p_mat[i*row+i];
	}

	return (determinant_value);

}



/**
 * Returns the convariance of a matrix
 * throws: ALLOCATION_FAILURE
 */

matrix matrix::covariance(void)const throw(int)	{

	//covariance matrix is a square matrix
	matrix temp_mat(column,column);
	float *mean_ptr;

	if(!(isOrderValid(row, column) && temp_mat.isOrderValid(temp_mat.row, temp_mat.column)))
		throw INVALID_ORDER;

	try{
		mean_ptr = new float[column];
	}
	catch(std::bad_alloc &ba){
		throw ALLOCATION_FAILURE;
	}

	int i,j,k;

	//proceed further only if enough memory is available
	for(i=0; i<column; i++){

		mean_ptr[i]=0;

		for(j=0; j<row; j++){

			mean_ptr[i] += p_mat[j*column+i];
		}

		//Store mean for each column
		mean_ptr[i] /= row;
	}

	//Find covariance for ith and jth columns
	for(i=0; i<column; i++)	{

		for(j=0; j<column; j++)	{

			temp_mat.p_mat[i*column+j] = 0;

			for(k=0; k<row; k++){

				temp_mat.p_mat[i*column+j] +=  (p_mat[k*column+i] - mean_ptr[i]) * (p_mat[k*column+j] - mean_ptr[j]);
			}

			temp_mat.p_mat[i*column+j] /= row;
		}
	}

	return (temp_mat);




}//covariance() ends


/**
 * Returns the matrix appended  (horizontally, at the end) with the given matrix
 * throws: ALLOCATION_FAILURE, INVALID_ORDER
 */
matrix matrix::append_h(const matrix &mat_right)const throw(int){
	/*//temporary martix
	matrix temp;

	//index for left matrix elements
	int i=0;

	//index for right matrix elements
	int j=0;

	int iter=0;

	//flag to keep track when each row of the matrix is iver
	int temp_col_left=0;

	//flag to keep track when each row of the matrix is iver
	int temp_col_right=0;

	//check for order compatibility before appending
	if(!(isOrderValid(row, column) && row == mat_right.row))
		throw INVALID_ORDER;


	//reorder temp matrix
	temp.order_ip((mat_right.row),(column + mat_right.column));

	//no. of elements in appended matrix
	iter = (mat_right.row)*(column + mat_right.column);

	while((i+j) < iter){

		if(temp_col_left < column){

			//copy the left matrix's elements
			temp.p_mat[i+j] = p_mat[i];
			i++;
			temp_col_left++;
		}
		else if(temp_col_right < mat_right.column){

			//copy right elements
	 *(temp.p_mat +i+j)= *(mat_right.p_mat +j);
			j++;
			temp_col_right++;
		}
		else{

			//reset the temp column counters
			temp_col_left =0;
			temp_col_right =0;

		}
	}

	return(temp);
	 */

	//check for order compatibility before appending
	if(!(isOrderValid(row, column) && row == mat_right.row))
		throw INVALID_ORDER;

	matrix temp(row + mat_right.row, column + mat_right.column);


	for(int i=0; i < row; i++){

		for(int j=0; j<column; j++){

			temp.p_mat[i*mat_right.row + j] = p_mat[i*row + j];
		}
	}

	for(int i=0; i<mat_right.row; i++){

		for(int j=0; j<mat_right.column; j++){

			temp.p_mat[i*mat_right.row + column + j] = mat_right.p_mat[i*mat_right.row + j];
		}
	}

	return temp;
}//append_h() ends



/**
 * Returns the matrix appended  (vertically, at the bottom) with the given matrix
 * throws: ALLOCATION_FAILURE, INVALID_ORDER
 */
matrix matrix::append_v(const matrix &mat_down)const throw(int)	{

	//check for order compatibility before appending
	if(!(isOrderValid(row, column) && column == mat_down.column))
		throw INVALID_ORDER;


	//reorder temp matrix
	matrix temp((row +mat_down.row), (mat_down.column));

	for(int i=0;i<(row*column);i++)	{

		temp.p_mat[i] = p_mat[i];
	}

	for(int i=0; i<(mat_down.row *mat_down.column);i++)	{

		temp.p_mat[(row*column) + i] = mat_down.p_mat[i];
	}

	return(temp);

}//append_v() ends


/**
 * Performs the shorthand addition operation i.e adds and assigns to the matrix
 * throws: INVALID_ORDER, OPERATION_FAILURE, ALLOCATION_FAILURE
 */
void matrix::operator+=(const matrix &rhs) throw(int){

	if(!(isOrderValid(row, column) && rhs.isOrderValid(rhs.row, rhs.column)))
		throw INVALID_ORDER;

	if(!(isOrderMatches(rhs.row, rhs.column)))
		throw OPERATION_FAILURE;

	*this = *this + rhs;

}//operator+=() ends



/**
 * Performs the shorthand subtraction operation i.e subtracts and assigns to the matrix
 * throws: INVALID_ORDER, OPERATION_FAILURE, ALLOCATION_FAILURE
 */
void matrix::operator-=(const matrix &rhs) throw(int){

	if(!(isOrderValid(row, column) && rhs.isOrderValid(rhs.row, rhs.column)))
		throw INVALID_ORDER;

	if(!(isOrderMatches(rhs.row, rhs.column)))
		throw OPERATION_FAILURE;

	*this= *this - rhs;

}//operator-=() ends



/**
 * Performs the shorthand multiplication operation i.e multiplies and assigns to the matrix
 * throws: INVALID_ORDER, OPERATION_FAILURE, ALLOCATION_FAILURE
 */
void matrix::operator*=(const matrix &rhs){

	if(!(isOrderValid(row, column) && rhs.isOrderValid(rhs.row, rhs.column)))
		throw INVALID_ORDER;

	if(!(column == rhs.row))
		throw OPERATION_FAILURE;

	*this = (*this) * rhs;

}//operator*=() ends


/**
 * Performs the shorthand multiplication operation i.e multiplies and assigns to the matrix
 * throws: INVALID_ORDER, OPERATION_FAILURE
 */
void matrix::operator*=(const float n){

	if(!isOrderValid(row, column))
		throw INVALID_ORDER;

	*this = (*this)*n;

}//operator*=() ends


/**
 * Returns true if order and elements match, else returns false
 */
bool matrix::operator==(const matrix &rhs)const{
	bool flag = true;

	//Check for orders
	if(column == rhs.column && row == rhs.row)
	{
		//Check for elements
		for(int i=0;i<(row*column);i++)
			if(*(p_mat + i) != *(rhs.p_mat + i))
			{
				flag = false;
				break;
			}

		return flag;
	}

	//return false if order mismatch
	else
		return false;

}//operator==() ends


/**
 * Returns the element of the matrix specified by row and column (0-based)
 * throws: INVALID_ORDER, OPERATION_FAILURE
 */
float matrix::get_element(int rhs_row, int rhs_column)const throw(int){

	if(!isOrderValid(row, column))
		throw INVALID_ORDER;

	//Check for position validity and also marix's validity; else throw exception
	if(rhs_row >= 0 && rhs_row < row && rhs_column >= 0 && rhs_column < column){

		//return the required element
		return p_mat[rhs_row*column + rhs_column];
	}
	else
		throw OPERATION_FAILURE;

}//get_element() ends


/**
 * Edits all the elements of the matrix
 * throws: INVALID_ORDER
 */
void matrix::mat_ele_ip_list(const float *ele_list){

	if(!isOrderValid(row, column))
		throw INVALID_ORDER;

	for(int i=0;i<row*column;i++){
		p_mat[i] = ele_list[i];
	}


}//mat_ele_ip_list() ends


bool matrix::isOrderMatches(int rhsRow, int rhsColumn)const{
	return((row == rhsRow) &&
			(column == rhsColumn));
}

bool matrix::isOrderValid(int rhsRow, int rhsColumn)const{
	return((rhsRow > 0) &&
			(rhsColumn > 0));
}

void matrix::makeMatrix() throw(int){
	try	{
		p_mat=new float[row*column];
	}
	catch(std::bad_alloc &ba){
		throw ALLOCATION_FAILURE;
	}

}

void matrix::initializeElements(){
	for(int i = 0; i < row*column; i++)
		p_mat[i]=0;
}

void matrix::initializeElements(const matrix& rhs){
	for(int i = 0; i < row*column; i++)
		p_mat[i]=rhs.p_mat[i];
}

void matrix::resetOrder(){
	p_mat=NULL;

	//Reset order
	row=0;
	column=0;
}
