#ifndef _MATRIX_H

#define _MATRIX_H
/*
  Name        : matrix.h
  Copyright   : Hrushikesh Vasista
  Author      : Hrushikesh Vasista
  Date        : 08/01/12 17:30
  Description : The class "matrix" provides the matrix operations; viz
                    -Addition
                    -Subtraction
                    -Multiplication (matrices)
                    -Multiplication (scalar)
                    -Inverse
  				-Determinant
*/
#include <iostream>

class matrix
{
      private:
             
             int row;
             int column;            
             
             float *p_mat;          
             
             static bool flag;      
      
      public:
                          
             matrix();               
             
             matrix(int row, int column);
           
             matrix(const matrix &rhs);
     
             ~matrix();
      
             void order_ip(int row,int column); 
        
             void edit(float new_ele,int row,int column);
             
             void display(void);
             
             void mat_ele_ip(void);
             
             matrix operator+(const matrix &rhs);
             
             matrix operator-(const matrix &rhs);
             
             void operator=(const matrix &rhs);
             
             friend matrix operator*(float scalar, matrix &rhs);
             
             friend matrix operator*(matrix &rhs, float scalar);
             
             matrix operator*(const matrix &rhs);
             
             void transpose();
                          
             matrix inverse();  
             
             float determinant();  
   
};

//Initialisation of static variables
bool matrix::flag(false);


matrix::matrix()
{

                p_mat=new float;    
                
                if(p_mat!=NULL)
                {
                   *p_mat=0;              //the element initialised to 0
                   row=1; 
                   column=1;
                }
          
                else
                {
                    exit(0);
              
                }           
       
}
//End of matrix() 



matrix::matrix(int m, int n)
{
                   
              
              if((m>0)&&(n>0))
              {
              
                  row=m; 
                  column=n;                       //store the required order

                  p_mat=new float[row*column];   //Create space for mxn elements
          
                  if(p_mat!=NULL)                //If space available then...
                     for(int i=0;i<m*n;i++)
                        *(p_mat+i)=0;            //initialise all elements to 0
              
                  else                           //else display a message.
                  {
                     
                     exit(0);
              
                  }
              
              }
              
              else                 
              {
                   
                   p_mat=new float;
              
                   if(p_mat!=NULL)
                   {
                      
                      row=1;
                      column=1;
                      *p_mat=0;
                      
                   
                   }
              
                   else
                   {
                       
                       exit(0);
 
                   }

                   
              }
                                      
                   
}
//End of matrix(int m, int n)


matrix::matrix(const matrix &rhs)
{

          
          row=rhs.row;                                   //Copy the row
          column=rhs.column;                             //and column
          
          p_mat=new float[row*column];                   //Create space for a temporary matrix
          
          if(p_mat!=NULL)                                //If space available then...
             for(int i=0;i<row*column;i++)               //Copy the elements
                *(p_mat+i)=*(rhs.p_mat+i);      
                
          else                                          //else display a message
          {
              exit(0);
              
          }


}
//End of matrix(const matrix &rhs)


matrix::~matrix()
{

                 delete []p_mat;
                 
}
//End of ~matrix()


void matrix::order_ip(int m, int n)
{
                        
           
           if((m>0)&&(n>0))
           {
                
                delete []p_mat;  
                row=m;
                column=n;
                p_mat=new float[row*column];
           
                if(p_mat!=NULL)
                   for(int i=0;i<m*n;i++)
                      *(p_mat+i)=0;                            //initialise all elements to 0
                else
                {
                   exit(0);
                }
                
          
           }
           
           else if((m==0)&&(n==0)&&flag)
           {
               delete []p_mat;
               
               row=0;
               column=0;
               
               flag=false;

           }

}
//End of order_ip(int m, int n)


void matrix::edit(float new_ele,int m,int n)
{
     
           if((m<row)&&(n<column)&&(m>=0)&&(n>=0)) //check for bounds of the given location
           {
               *(p_mat+m*column+n)=new_ele;
               
           }
 
}
//End of edit(float new_ele,int m,int n)


void matrix::display(void)
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


void matrix::mat_ele_ip(void)
{
 
     if(p_mat!=NULL)
        for(int i=0;i<row*column;i++)
           std::cin>>*(p_mat+i);                             
                  
     else 
     {
         exit(0);

     }
  
}
//End of mat_ele_ip(void)
 

matrix matrix::operator+(const matrix &rhs)
{
       matrix ans(row,column);                      //temporary matrix having order same as the caller matrix
       
       if((rhs.row==row)&&(rhs.column==column))     //Addition to be done only if order of both matrices are same
          {
                              
               if((ans.p_mat!=NULL))
               {
                   for(int i=0;i<(row*column);i++)                        
                      *(ans.p_mat+i)=*(rhs.p_mat+i)+*(p_mat+i);
               
                   return(ans);
                   
               }
               
               else
               {
                  exit(0);
               }
          
          }                
          
          else 
          {               
               flag=true;
               ans.order_ip(0,0);     //returning a matrix of 0x0 helps LHS to take clue to remain unchanged
               
               return ans; 
          
          }
          

}
//End of operator+(const matrix &rhs)



matrix matrix::operator-(const matrix &rhs)
{
      
      matrix ans(row,column);                      //temporary matrix having order same as the caller matrix
      
      if((rhs.row==row)&&(rhs.column==column))     //Subtraction to be done only if order of both matrices are same
      {
         
         if(ans.p_mat!=NULL)
         {
            for(int i=0;i<(row*column);i++)                        
               *(ans.p_mat+i)=*(p_mat+i)-*(rhs.p_mat+i);
         
            return(ans);
         
         }
         
         else
         {
             exit(0);   
             
         }
         
         
      }
                      
      else 
      {
           
           flag=true;
           ans.order_ip(0,0);
           
           return ans; 
      
      }
 
       
}
//End of operator-(const matrix &rhs)



void matrix::operator=(const matrix &rhs)
{
     
                    
     if(!((this==&rhs)||((rhs.row==0)&&(rhs.column==0))))         //to handle the case where A=A ie same mtrices
     {
         //IMPORTANT First check if its a indicator of 0x0 matrix and only then proceed to assign the RHS to LHS
       
              
        if(!((rhs.row==row)&&(rhs.column==column)))
             order_ip(rhs.row,rhs.column);                 
              
        if(p_mat!=NULL)
           for(int i=0;i<(row*column);i++)      
              *(p_mat+i)=*(rhs.p_mat+i);
          
        else
        {   
            exit(0);
        
        }
              
     }
     
     else
     {
         //Do nothing.
         
     }
          

}
//End of operator=(const matrix &rhs)
 

matrix operator*(float scalar, matrix &rhs)
{
        
        matrix temp(rhs.row, rhs.column);
        
        if(temp.p_mat!=NULL)
        {
            for(int i=0;i<rhs.row*rhs.column;i++)
                *(temp.p_mat+i)=(*(rhs.p_mat+i))*scalar;
        }
        else
        {
            exit(0);
        }
 
        
        return(temp);
        
        
}
//End of operator*(float scalar, matrix &rhs)


matrix operator*(matrix &rhs, float scalar)
{
        matrix temp(rhs.row, rhs.column);
        
        if(temp.p_mat!=NULL)
        {                 
            for(int i=0;i<rhs.row*rhs.column;i++)
                *(temp.p_mat+i)=(*(rhs.p_mat+i))*scalar;
        }
        else
        {
            exit(0);
        }
        

        
        return(temp);
                
}
//End of operator*(matrix &rhs, float scalar)


matrix matrix::operator*(const matrix &rhs)
{
       
       matrix temp(row, rhs.column);
       
       if(column==rhs.row)            //Multiplication to be done only of the order criteria is met
       {
            float res=0;
            int i,j,k;
            
            if(temp.p_mat!=NULL)
            {
               
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
                
             }//End of (temp.p_mat!=NULL)
            
            else
            {
                exit(0);
            }
                        
       }                                                    
                                                               
       else                                                                                              
       {
            
            flag=true;
            temp.order_ip(0,0);
           
            return temp; 
       
       }

}
//End of operator*(const matrix &rhs)
 

void matrix::transpose()
{
        
        int counter=0,i,j;
        float temp_var=0;
        float *temp_mat=new float[row*column];
        
        if(temp_mat!=NULL) 
        {     
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
        
        else
        {
            
            exit(0);
        }
                   
                  
 
}
//End of transpose(matrix &rhs)


matrix matrix::inverse()
{
       
       
       matrix temp_mat(row,row);       //temporary matrix = input matrix
       matrix inv(row,column);         //[I] matrix to calculate the inverse

             
       if(row==column)
       {
                   
               
               if((temp_mat.p_mat!=NULL)&&(inv.p_mat!=NULL))
               {
                     int i,j,k,m,n,flagger=0;
                     float ratio=0,temp=0,count=0;
               
                     for(i=0;i<row;i++)           //start by considering answer as [I] matrix.
                         *(inv.p_mat+i*row+i)=1;  //[I] matrix
                      
                      for(i=0;i<row*row;i++)
                          *(temp_mat.p_mat+i)=*(p_mat+i);   //the input matrix is used to perform required operations
               
               
                   			                    
                      for(i=0;i<row;i++)
	                  {
                       
                           flagger=i;
		                   while(*(temp_mat.p_mat+i*row+i)==0)      // for gauss elimnation consider only de PD elemts
		                   {
                                 if(flagger==(row-1))               //flagger indicates the Max No. of failed attempts
			                     {                                  //of exchanging the diff columns.
                                 
				                 
                                       flag=true;
                                       temp_mat.order_ip(0,0);
                                 
                                       return temp_mat;             //This is for matrix of 1x1
                                 
			                 
			                      }
			                 
                                  else
			                      {
				             
                                       flagger++;
				                 
                                       for(k=0;k<row;k++)              //swapping columns n again checking
				                       {
                    
                                            temp=*(temp_mat.p_mat+k*row+i);
					                        *(temp_mat.p_mat+k*row+i)=*(temp_mat.p_mat+k*row+flagger);
					                        *(temp_mat.p_mat+k*row+flagger)=temp;

					                        temp=*(inv.p_mat+k*row+i);                                //whatever exchanges done to base matrix
					                        *(inv.p_mat+k*row+i)=*(inv.p_mat+k*row+flagger);          //do similar changes to answer matrix 
					                        *(inv.p_mat+k*row+flagger)=temp;
					                  
                                        }
	                            
	                            
                                    }//else ends
                             

		                     } // while ends...repeat till (n-1) columns have been swapped ie max limit



                             for(j=0;j<row;j++)
		                     {
			               
                                  if(j!=i)
				                      ratio=(*(temp_mat.p_mat+j*row+i))/(*(temp_mat.p_mat+i*row+i));       //find the ratio. Again Take care to consider only the PD elemnts ie j=i.
			              
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
						        
                                             if(*(temp_mat.p_mat+m*row+n)==0)        //check after every manipulation whether all elements
						                          count++;                           //of input matrix are 0.
						        
                                        }

					                    if(count==row)
					                    {
						       
						                      flag=true;
                                              temp_mat.order_ip(0,0);
                               
                                              return temp_mat;
                                                
					                     }
					         
                                   
                                   }//m loop ends
			           
		               }//j ends
               
	           } //i ends
             
	         
              for(i=0;i<row;i++)
	          {   
                 
                  for(j=0;j<row;j++)
                  {
                      
                      (*(inv.p_mat+i*row+j))/=(*(temp_mat.p_mat+i*row+i));
                       
                  }
                 
              }
               
              return (inv);
                
             }
             
             else
             {
                 exit(0);
                 
             }
              
             
          }       
           
          else
          {
                   
                   flag=true;
                   temp_mat.order_ip(0,0);
                   
                   return temp_mat;
                   
          }
			  
           
	          
   
}
//End of inverse()



float matrix::determinant()
{
       
       
       matrix temp_mat(row,row);       //temporary matrix = input matrix
       
       float determinant_value = 1;
             
       if(row==column)
       {
                   
               
               if((temp_mat.p_mat!=NULL))
               {
                     int i,j,k,m,n,flagger=0;
                     float ratio=0,temp=0,count=0;
               
                     for(i=0;i<row*row;i++)
                          *(temp_mat.p_mat+i)=*(p_mat+i);   //the input matrix is used to perform required operations
               
               
                   			                    
                      for(i=0;i<row;i++)
	                  {
                       
                           flagger=i;
		                   while(*(temp_mat.p_mat+i*row+i)==0)      // for gauss elimnation consider only de PD elemts
		                   {
                                 if(flagger==(row-1))               //flagger indicates the Max No. of failed attempts
			                     {                                  //of exchanging the diff columns.
                                 
                                       flag=true;
                                                                        
                                       return 0;             //This is for matrix of 1x1
                                 
			                 
			                      }
			                 
                                  else
			                      {
				             
                                       flagger++;
				                 
                                       for(k=0;k<row;k++)              //swapping columns n again checking
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
				                      ratio=(*(temp_mat.p_mat+j*row+i))/(*(temp_mat.p_mat+i*row+i));       //find the ratio. Again Take care to consider only the PD elemnts ie j=i.
			              
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
						        
                                             if(*(temp_mat.p_mat+m*row+n)==0)        //check after every manipulation whether all elements
						                          count++;                           //of input matrix are 0.
						        
                                        }

					                    if(count==row)
					                    {
						       
                                              flag=true;
                                                                             
                                              return 0;
                                                
					                     }
					         
                                   
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
             {
                 exit(0);
                 
             }
              
             
          }       
           
          else
          {
                   
                   flag=true;
                                     
                   return 0;
                   
          }      
       
}

#endif
