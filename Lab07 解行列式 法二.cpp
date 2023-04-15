/* EE231002 Lab07. Matrix Determinant
   106061127,¼B®aºû 
   Date:2017/11/15
*/

#include<stdio.h>
//#if !define(N)
#define N 6 
//#endif

void changemat(int ,double A[][N],double change[][N],int);   
double det(double A[][N],int); //these three functions are used 
int sign(int);           //to calculate the determinant
int main(void)
{
	double A[N][N];//store the given matrix
	int n=N; //record the matrix's dimension
	int i=0,j=0;
	double answer=0; //the determinant of the matrix
	
	for (i=0;i<N;i++) {			//read the given matrix 
		for (j=0;j<N;j++) {
			scanf("%lf",&A[i][j]);	
		}
	}
	
	printf("Matrix A is\n  ");	//print out the title
	for (i=0;i<N;i++) {			//and the given matrix
		for (j=0;j<N;j++) {
			printf("%g ",A[i][j]);	
			if (j==N-1)
				printf("\n  ");
		}
	}

	answer=det(A,n);//use det function to calculate the determinant
	printf("\b\b");
	printf("det(A) = %g",answer);//print out the answer
	
	return 0;
}

double det(double a[][N],int dim)
{ 
	double change[N][N];//store the product of the function ''changemat''
	double ans=0; //answer
	int i=0;
	int dim2; //the new dimention after the function recurse
	
	dim2=dim-1; //the dimension minus 1 whenever the function recurse
	
	if (dim==1)
		ans=a[0][0]; //the determinant of a 1*1 matrix 
					 //is equal to the element in it
	else if (dim>=1) {
		for (i=0;i<dim;i++) { //do this thing from row 1 (i=0) 
			changemat(i,a,change,dim);
			ans=ans+sign(i)*a[i][0]*det(change,dim2);//recursive function
		}      //the given formula,and we call sign function to decide 
	}		   //whether the number is + or -
			   //use recursive call,for example,if we want to calculate
			   //a 3*3 matrix,we call function to calculate 2*2 and call
		//again to calculate 1*1,and the final element is coincidently
		//the 1*1 matrix's determinant so the answer is found.
	return ans;   //if it is done,return the answer
}

void changemat(int i,double a[][N],double change[][N],int n)
{
	int col,row;	//col,row are variables to record the matrix[][]
	int changerow=0;//is the varible to record the row of the change[][]
					//we don't need to declare a new variable because
					//we can use the origin col minus to represent
	for (row=0; row<n; row++,changerow++) {
		if (row==i)   //skip the row if it is the same
			row++;
		for (col=1;col<n;col++)//start from second column because we want to
			change[changerow][col-1]=a[row][col];//get the elements from 
	}										//different rows and columns								
}
int sign(int n)			//the function to determine  
{						//the sign of the element
	if (n%2==0)			//n is which row the element is in
		return 1;
	return -1;			
}
