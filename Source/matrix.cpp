#include "matrix.h"

matrix::matrix()
{
    //Set p_mat to null
  p_mat=NULL;

  //Order = 0x0
  row=0;
  column=0;
}
//End of matrix()



matrix::matrix(int m, int n)
{
    //If valid order...
  if((m>0)&&(n>0))
  {
    //store the required order
    row=m;
    column=n;

        //Create space for mxn elements
    try
    {
      p_mat=new float[row*column];
    }
    catch(std::bad_alloc &ba)
    {
      std::cout<<"\nAllocation error...";
      exit(1);
    }

        //initialise all elements to 0
    for(int i=0;i<m*n;i++)
      *(p_mat+i)=0;

  }

  else
  {
    //Set p_mat to null
    p_mat=NULL;

    //Order = 0x0
    row=0;
    column=0;
  }
}
//End of matrix(int m, int n)


matrix::matrix(const matrix &rhs)
{
  //If valid matrix...
  if(rhs.row>0 && rhs.column>0)
  {
    //store the required order
    row=rhs.row;
    column=rhs.column;

    //Create space for the matrix
    try
    {
      p_mat=new float[row*column];
    }
    catch(std::bad_alloc &ba)
    {
      std::cout<<"\nAllocation error...";
      exit(1);
    }

    //Copy the elements
    for(int i=0;i<row*column;i++)
      *(p_mat+i)=*(rhs.p_mat+i);

  }

  else
  {
    //Set p_mat to null
    p_mat=NULL;

    //Order = 0x0
    row=0;
    column=0;

  }
}
//End of matrix(const matrix &rhs)


matrix::~matrix()
{
    //free the memory
  delete []p_mat;

}
//End of ~matrix()


void matrix::order_ip(int m, int n)
{
  //If valid order...
  if((m>0)&&(n>0))
  {
    //Clear previous order
    delete []p_mat;

    //Store new order
    row=m;
    column=n;

    try
    {
      p_mat=new float[row*column];
    }
    catch(std::bad_alloc &ba)
    {
      std::cout<<"\nAllocation error...";
      exit(1);
    }

    //initialise all elements to 0
    for(int i=0;i<m*n;i++)
      *(p_mat+i)=0;

  }
  else
  {
    //Reset previous attributes...
    //Free previous memory
    delete []p_mat;

    //Set p_mat to null
    p_mat=NULL;

    //Order = 0x0
    row=0;
    column=0;
  }
}
//End of order_ip(int m, int n)


void matrix::edit(float new_ele,int m,int n)
{
    //check for bounds of the given location
  if((m<row)&&(n<column)&&(m>=0)&&(n>=0))
   *(p_mat+m*column+n)=new_ele;

}
//End of edit(float new_ele,int m,int n)


void matrix::display(void) const
{
  int i,j;

  std::cout<<"\n";

  for(i=0;i<row;i++)
  {
    for(j=0;j<column;j++)
      std::cout<<*(p_mat+i*column+j)<<"\t";

    std::cout<<"\n";
  }

}
//End of display(void)


void matrix::mat_ele_ip_user(void)
{
  if(p_mat!=NULL)
  {
    for(int i=0;i<row*column;i++)
      std::cin>>*(p_mat+i);
  }
}
//End of mat_ele_ip_user(void)


matrix matrix::operator+(const matrix &rhs)const
{
  //temporary matrix having order same as the caller matrix
  matrix ans(row,column);

  //Addition to be done only if order of both matrices are same
  if((rhs.row==row)&&(rhs.column==column)&&(ans.p_mat!=NULL))
  {
    for(int i=0;i<(row*column);i++)
      *(ans.p_mat+i)=*(rhs.p_mat+i)+*(p_mat+i);

    return(ans);

  }
  else
  {
      //returning a matrix of 0x0 helps LHS to take clue to remain unchanged
    ans.order_ip(0,0);

    return ans;
  }

}
//End of operator+(const matrix &rhs)



matrix matrix::operator-(const matrix &rhs)const
{
  //temporary matrix having order same as the caller matrix
  matrix ans(row,column);

  //Subtraction to be done only if order of both matrices are same
  if((rhs.row==row)&&(rhs.column==column)&&(ans.p_mat!=NULL))
  {

    for(int i=0;i<(row*column);i++)
      *(ans.p_mat+i)=*(p_mat+i)-*(rhs.p_mat+i);

    return(ans);

  }
  else
  {
    //returning a matrix of 0x0 helps LHS to take clue to remain unchanged
    ans.order_ip(0,0);

    return ans;
  }
}
//End of operator-(const matrix &rhs)



void matrix::operator=(const matrix &rhs)
{
    //to handle the case where A=A ie same mtrices and is not an indicator matrix.
  if(!((this==&rhs)||((rhs.row==0)&&(rhs.column==0))))
  {
    //Make LHS matrix order same as RHS matrix
    if(!((rhs.row==row)&&(rhs.column==column)))
      order_ip(rhs.row,rhs.column);

    //Assign RHS elements to LHS
    if(p_mat!=NULL)
    {
      for(int i=0;i<(row*column);i++)
        *(p_mat+i)=*(rhs.p_mat+i);
    }
  }
  //else do nothing
}
//End of operator=(const matrix &rhs)


matrix operator*(float scalar, const matrix &rhs)
{
  //temporary matrix having order same as the multiplicand matrix
  matrix temp(rhs.row, rhs.column);

  //Multiply each element by the scalar
  if(temp.p_mat!=NULL)
  {
    for(int i=0;i<rhs.row*rhs.column;i++)
      *(temp.p_mat+i)=(*(rhs.p_mat+i))*scalar;
  }

  return(temp);
}
//End of operator*(float scalar, matrix &rhs)


matrix matrix::operator*(float scalar)const
{
  //temporary matrix having order same as the multiplicand matrix
  matrix temp(row, column);

  // temp = scalar * rhs;
  if(temp.p_mat!=NULL)
  {
    for(int i=0;i<row*column;i++)
      *(temp.p_mat+i)=(*(p_mat+i))*scalar;
  }

  return(temp);

}
//End of operator*(matrix &rhs, float scalar)


matrix matrix::operator*(const matrix &rhs)const
{
    //temporary matrix having order = row of left multiplicand matrix and column of right multiplicand matrix
  matrix temp(row, rhs.column);

  //Multiplication to be done only of the order criteria is met
  if((column==rhs.row)&&(temp.p_mat!=NULL))
  {
    float res=0;
    int i,j,k;

    for(i=0;i<row;i++)
    {
      for(j=0;j<rhs.column;j++)
      {
        for(k=0;k<rhs.row;k++)
          res=res+((*(p_mat+i*column+k))*(*(rhs.p_mat+k*rhs.column+j)));

        *(temp.p_mat+i*rhs.column+j)=res;

        res=0;
      }//j loop ends

    }//i loop ends

    return(temp);

  }
  else
  {
    //returning a matrix of 0x0 helps LHS to take clue to remain unchanged
    temp.order_ip(0,0);

    return temp;

  }
}
//End of operator*(const matrix &rhs)


void matrix::transpose(void)
{
  int counter=0,i,j;
  float temp_var=0;
  float *temp_mat;
  try
  {
    temp_mat=new float[row*column];
  }
  catch(std::bad_alloc &ba)
  {
    std::cout<<"\nAllocation error...";
    exit(1);
  }

  for(i=0;i<column;i++)
    for(j=0;j<row;j++)
    {
      *(temp_mat+counter)=*(p_mat+j*column+i);
      counter++;
    }

    for(i=0;i<row*column;i++)
      *(p_mat+i)=*(temp_mat+i);

    counter=column;

    column=row;

    row=counter;

  }
//End of transpose(matrix &rhs)


  matrix matrix::inverse(void)const
  {
    //temporary matrix = input matrix
    matrix temp_mat(row,row);

  //[I] matrix to calculate the inverse
    matrix inv(row,column);

  //If square matrix...
    if((row != 0 && column != 0 && row==column)&&(temp_mat.p_mat!=NULL)&&(inv.p_mat!=NULL))
    {
      int i,j,k,m,n,flagger=0;
      float ratio=0,temp=0,count=0;

    //start by considering answer as [I] matrix.
      for(i=0;i<row;i++)
        *(inv.p_mat+i*row+i)=1;

    //the input matrix is used to perform required operations
      for(i=0;i<row*row;i++)
        *(temp_mat.p_mat+i)=*(p_mat+i);


      for(i=0;i<row;i++)
      {

        flagger=i;

      //find inverse by Gauss Elimination method.
      //Consider only the PD elements
        while(*(temp_mat.p_mat+i*row+i)==0)
        {
        //flagger indicates the Max No. of failed attempts of exchanging the diff columns.
          if(flagger==(row-1))
          {
          //returning a matrix of 0x0 helps LHS to take clue to remain unchanged
            temp_mat.order_ip(0,0);

            return temp_mat;
          }

          else
          {
            flagger++;

          //swap the columns and check again
            for(k=0;k<row;k++)
            {
              temp=*(temp_mat.p_mat+k*row+i);
              *(temp_mat.p_mat+k*row+i)=*(temp_mat.p_mat+k*row+flagger);
              *(temp_mat.p_mat+k*row+flagger)=temp;

            //whatever exchanges done to base matrix do similar changes to answer matrix
              temp=*(inv.p_mat+k*row+i);
              *(inv.p_mat+k*row+i)=*(inv.p_mat+k*row+flagger);
              *(inv.p_mat+k*row+flagger)=temp;
            }

        }//else ends

      } // while ends...repeat till (n-1) columns have been swapped ie max limit


      for(j=0;j<row;j++)
      {
        if(j!=i)
          //find the ratio by considering only the PD elements
          ratio=(*(temp_mat.p_mat+j*row+i))/(*(temp_mat.p_mat+i*row+i));

        else
          continue;

        for(k=0;k<row;k++)
        {
         *(temp_mat.p_mat+j*row+k)=*(temp_mat.p_mat+j*row+k)-(ratio*(*(temp_mat.p_mat+i*row+k)));
         *(inv.p_mat+j*row+k)=*(inv.p_mat+j*row+k)-(ratio*(*(inv.p_mat+i*row+k)));

        }// k ends

        for(m=0;m<row;m++)
        {
          count=0;

          for(n=0;n<row;n++)
          {
            //check after every manipulation whether all elements of a row of input matrix are 0.
            if(*(temp_mat.p_mat+m*row+n)==0)
              count++;

          }

          //If all elements of a row are 0...
          if(count==row)
          {
            //returning a matrix of 0x0 helps LHS to take clue to remain unchanged
            temp_mat.order_ip(0,0);

            return temp_mat;
          }

        }//m loop ends

      }//j ends

    } //i ends

    //Divide each element of a row with corresponding PD element
    for(i=0;i<row;i++)
    {
      for(j=0;j<row;j++)
      {
        (*(inv.p_mat+i*row+j))/=(*(temp_mat.p_mat+i*row+i));
      }
    }

    return (inv);


  }
  //Return Indicator matrix if not a square matrix
  else
  {
    temp_mat.order_ip(0,0);

    return temp_mat;
  }

}
//End of inverse()



float matrix::determinant(void)const throw(int)
{
  //Exception flag; 0= Invalid matrix, 1= not a square matrix
  int excep_flag=0;

  //If a valid matrix proceed, else throw exception
  if(row!=0 && column!=0)
  {
    excep_flag = 1;

    //temporary matrix = input matrix
    matrix temp_mat(row,row);

    float determinant_value = 1;

    //Calculate determinant only if square matrix else throw an exception
    if(row==column)
    {
      int i,j,k,m,n,flagger=0;
      float ratio=0,temp=0,count=0;

      for(i=0;i<row*row;i++)
        //the input matrix is used to perform required operations
        *(temp_mat.p_mat+i)=*(p_mat+i);


      for(i=0;i<row;i++)
      {
        flagger=i;

        //Consider only the PD elements
        while(*(temp_mat.p_mat+i*row+i)==0)
        {
          if(flagger==(row-1))
            return 0;

          else
          {
            flagger++;

            for(k=0;k<row;k++)
            {
              temp=*(temp_mat.p_mat+k*row+i);
              *(temp_mat.p_mat+k*row+i)=*(temp_mat.p_mat+k*row+flagger);
              *(temp_mat.p_mat+k*row+flagger)=temp;

            }

          }//else ends

        } // while ends...repeat till (n-1) columns have been swapped ie max limit


        for(j=0;j<row;j++)
        {
          if(j!=i)
            //find the ratio by considering only the PD elements.
            ratio=(*(temp_mat.p_mat+j*row+i))/(*(temp_mat.p_mat+i*row+i));

          else
            continue;

          for(k=0;k<row;k++)
          {
            *(temp_mat.p_mat+j*row+k)=*(temp_mat.p_mat+j*row+k)-(ratio*(*(temp_mat.p_mat+i*row+k)));

          }// k ends

          for(m=0;m<row;m++)
          {
            count=0;
            for(n=0;n<row;n++)
            {
              if(*(temp_mat.p_mat+m*row+n)==0)
                count++;
            }

            if(count==row)
              return 0;

          }//m loop ends

        }//j ends

      } //i ends

      for(i=0;i<row;i++)
      {
        determinant_value *= ((*(temp_mat.p_mat+i*row+i)));
      }

      return (determinant_value);

    }

    else
      throw excep_flag;
  }
  else
    throw excep_flag;


}//determinant() ends



matrix matrix::covariance(void)const
{
  //covariance matrix is a square matrix
  matrix temp_mat(column,column);
  float *mean_ptr;
  if((row!=0 && column!=0) && (temp_mat.p_mat != NULL))
  {
    try
    {
      mean_ptr = new float[column];
    }
    catch(std::bad_alloc &ba)
    {
      std::cout<<"\nAllocation error...";
      exit(1);
    }

    int i,j,k;

    //proceed further only if enough memory is available
    for(i=0; i<column; i++)
    {
      *(mean_ptr+i)=0;

      for(j=0; j<row; j++)
      {
        *(mean_ptr+i) += *(p_mat+j*column+i);
      }

      //Store mean for each column
      *(mean_ptr+i) /= row;
    }

    //Find covariance for ith and jth columns
    for(i=0; i<column; i++)
    {
      for(j=0; j<column; j++)
      {
        *(temp_mat.p_mat+i*column+j)=0;

        for(k=0; k<row; k++)
        {
          *(temp_mat.p_mat+i*column+j) +=  (*(p_mat+k*column+i) - *(mean_ptr+i))*(*(p_mat+k*column+j) - *(mean_ptr+j));

        }

        *(temp_mat.p_mat+i*column+j) /= row;
      }
    }

    return (temp_mat);

  }
  else
  {
    //returning a matrix of 0x0 helps LHS to take clue to remain unchanged
    temp_mat.order_ip(0,0);

    return temp_mat;
  }



}//covariance() ends



matrix matrix::append_h(const matrix &mat_right)const
{
  //temporary martix
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
  if(row!=0 && column!=0 && row == mat_right.row)
  {
    //reorder temp matrix
    temp.order_ip((mat_right.row),(column +mat_right.column));

    //no. of elements in appended matrix
    iter = (mat_right.row)*(column +mat_right.column);

    while((i+j)<iter)
    {
      if(temp_col_left < column)
      {
        //copy the left matrix's elements
        *(temp.p_mat +i+j)= *(p_mat +i);
        i++;
        temp_col_left++;
        //temp.p_mat++;
      }
      else if(temp_col_right < mat_right.column)
      {
        //copy right elements
        *(temp.p_mat +i+j)= *(mat_right.p_mat +j);
        j++;
        temp_col_right++;
        //temp.p_mat++;

      }
      else
      {
        //reset the temp column counters
        temp_col_left =0;
        temp_col_right =0;

      }
    }

    return(temp);
  }

  //return an indicator matrix to signal no change on LHS matrix
  else
  {
    temp.order_ip(0,0);
    return(temp);
  }

}//append_h() ends



matrix matrix::append_v(const matrix &mat_down)const
{
  //temporary martix
  matrix temp;

  //index for left matrix elements
  int i=0;

  //flag to keep track when each row of the matrix is iver
  int temp_col_top=0;

  //check for order compatibility before appending
  if(row!=0 && column!=0 && column == mat_down.column)
  {
    //reorder temp matrix
    temp.order_ip((row +mat_down.row),(mat_down.column));

    for(i=0;i<(row*column);i++)
    {
      *(temp.p_mat + i) = *(p_mat +i);
    }

    for(i=0;i<(mat_down.row *mat_down.column);i++)
    {
      *(temp.p_mat + (row*column)+i) = *(mat_down.p_mat +i);
    }

    return(temp);
  }

  //return an indicator matrix to signal no change on LHS matrix
  else
  {
    temp.order_ip(0,0);
    return(temp);
  }

}//append_v() ends



void matrix::operator+=(const matrix &rhs)
{
  if(p_mat != NULL && rhs.p_mat != NULL)
  {
    if(row==rhs.row && column == rhs.column)
    {
      *this= *this + rhs;
    }
  }

}//operator+=() ends



void matrix::operator-=(const matrix &rhs)
{
  if(p_mat != NULL && rhs.p_mat != NULL)
  {
    if(row==rhs.row && column == rhs.column)
    {
      *this= *this - rhs;
    }
  }

}//operator-=() ends



void matrix::operator*=(const matrix &rhs)
{
  if(p_mat != NULL && rhs.p_mat != NULL)
  {
    if(column==rhs.row)
    {
      *this = (*this) * rhs;
    }
  }

}//operator*=() ends



void matrix::operator*=(const float n)
{
  if(p_mat != NULL)
  {
    *this = (*this)*n;
  }

}//operator*=() ends



bool matrix::operator==(const matrix &rhs)const
{
  int i;

  bool flag = true;

  //Check for orders
  if(column == rhs.column && row == rhs.row)
  {
    //Check for elements
    for(i=0;i<(row*column);i++)
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


float matrix::get_element(int rhs_row, int rhs_column)const throw(int)
{
  int excep_flag =0;

  //Check for position validity and also marix's validity; else throw exception
  if(rhs_row >= 0 && rhs_row < row && rhs_column >= 0 && rhs_column < column && p_mat != NULL)
  {
    //return the required element
    return(*(p_mat + rhs_row*row + rhs_column));
  }
  else
    throw excep_flag;

}//get_element() ends


void matrix::mat_ele_ip_list(const float *ele_list)
{
  if(p_mat!=NULL)
  {
    for(int i=0;i<row*column;i++)
      *(p_mat+i) = *(ele_list+i);
  }

}//mat_ele_ip_list() ends


matrix::matrix(int m, int n, const float *ele_list)
{
  //If valid order...
  if((m>0)&&(n>0))
  {
    //store the required order
    row=m;
    column=n;

        //Create space for mxn elements
    try
    {
      p_mat=new float[row*column];
    }
    catch(std::bad_alloc &ba)
    {
      std::cout<<"\nAllocation error...";
      exit(1);
    }

    //initialise the elements as in the list
    for(int i=0;i<m*n;i++)
      *(p_mat+i) = *(ele_list + i);

  }
  else
  {
    //Set p_mat to null
    p_mat=NULL;

    //Order = 0x0
    row=0;
    column=0;
  }
}