#ifndef _MATRIX_H
#define _MATRIX_H

/*****************************************************************************
 * Filename        	 : matrix.h
 * Author      		 : Hrushikesh Vasista
 * Date        		 : 02/04/2014
 * Version     		 : 3.2
 *****************************************************************************/

class matrix {
private:

	/**
	 * Order of the matrix
	 */
	int row;
	int column;

	/**
	 * matrix elements
	 */
	float* p_mat;

	void resetOrder();

	void makeMatrix() throw(int);

	bool isOrderMatches(int rhsRow, int rhsColumn) const;

	bool isOrderValid(int rhsRow, int rhsColumn) const;

	void initializeElements();

	void initializeElements(const matrix& rhs);


public:

	const static int ALLOCATION_FAILURE = 0;

	const static int OPERATION_FAILURE = 1;

	const static int NOT_SQUARE_MATRIX = 2;

	const static int NO_INVERSE_EXISTS = 3;

	const static int DETERMINANT_ZERO = 4;

	const static int INVALID_ORDER = 5;


	matrix();

	matrix(int row, int column) throw(int);

	matrix(const matrix &rhs) throw(int);

	matrix(int m, int n, const float *ele_list);

	~matrix();

	int getRow();

	int getColumn();

	void order_ip(int row,int column) throw(int);

	void edit(float new_ele,int row,int column);

	//void display(void) const;

	//void mat_ele_ip_user(float);

	matrix operator+(const matrix &rhs)const throw(int);

	matrix operator-(const matrix &rhs)const;

	void operator=(const matrix &rhs) throw(int);

	friend matrix operator*(float scalar, const matrix &rhs) throw(int);

	matrix operator*(float scalar)const throw(int);

	matrix operator*(const matrix &rhs)const;

	void transpose(void) throw(int);

	matrix inverse(void)const throw(int);

	float determinant(void)const throw(int);

	matrix covariance(void)const throw(int);

	matrix append_h(const matrix &mat_right)const throw(int);

	matrix append_v(const matrix &mat_down)const throw(int);

	void operator+=(const matrix &rhs) throw(int);

	void operator-=(const matrix &rhs) throw(int);

	void operator*=(const matrix &rhs);

	void operator*=(const float n);

	bool operator==(const matrix &rhs)const;

	float get_element(int rhs_row, int rhs_column)const throw(int);

	void mat_ele_ip_list(const float *ele_list);



};

#endif
