#ifndef _MATRIX_H
#define _MATRIX_H

/*****************************************************************************
 * Filename        : matrix.h
 * Author      		 : Hrushikesh Vasista
 * Date        		 : 02/04/2014
 * Version     		 : 3.1
*****************************************************************************/
#include <iostream>
#include <new>
#include <stdlib.h>

class matrix {
	int row;
	int column;

	float *p_mat;

	public:

		matrix();

		matrix(int row, int column);

		matrix(const matrix &rhs);

		~matrix();

		void order_ip(int row,int column);

		void edit(float new_ele,int row,int column);

		void display(void) const;

		void mat_ele_ip_user(void);

		matrix operator+(const matrix &rhs)const;

		matrix operator-(const matrix &rhs)const;

		void operator=(const matrix &rhs);

		friend matrix operator*(float scalar, const matrix &rhs);

		matrix operator*(float scalar)const;

		matrix operator*(const matrix &rhs)const;

		void transpose(void);

		matrix inverse(void)const;

		float determinant(void)const throw(int);

		matrix covariance(void)const;

		matrix append_h(const matrix &mat_right)const;

		matrix append_v(const matrix &mat_down)const;

		void operator+=(const matrix &rhs);

		void operator-=(const matrix &rhs);

		void operator*=(const matrix &rhs);

		void operator*=(const float n);

		bool operator==(const matrix &rhs)const;

		float get_element(int rhs_row, int rhs_column)const throw(int);

		void mat_ele_ip_list(const float *ele_list);

		matrix(int m, int n, const float *ele_list);

};

#endif
