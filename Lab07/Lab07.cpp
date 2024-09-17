/* EE2310 lab07 Matrix determinants.
   106061218 Cheng-En Lee.
   2017/11/13
*/

#include <stdio.h>
#if !defined(N)
#define N 3
#endif



/*The fuction to solve determinants recursively*/
double det(double A[N][N], int dim);
  
int main(void)
{  
	double A[N][N];    // The initial determinants.
	int dim = N;       // The size of determinants.
	int i = 0, j = 0;
	double ans = 0;    // value of determinant
 
 /* Initialize the array */   
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			A[i][j] = 0.0;
      
 /* Read in the determinants */	
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			scanf("%lf ", &A[i][j]);	
      
 /* Show the determinants */	
	printf("Matrix A is\n");
	for (i = 0; i < N; i++) 
    {	
		printf("  ");
			for (j = 0; j < N; j++)
				printf("%lg ", A[i][j]);		
	  	printf("\n");
  	}

 /* Calculate the answer and print */  
	ans = det(A, dim);
	printf("det(A) = %lg\n", ans);
	
	return 0;
}

double det(double A[N][N], int dim)
{
	int i = 0, j = 0;   // Rows and columns of the determinants
	int sgn = 1;        // The sign of the minor. 
	double value = 0;   // The value of minors.
  
 /* get the elements of minor if the size of minors become 2. */  
	int p[2] = {0,0}, s = 0, k = 0;
  
 /* To record the removed row and to get minors */  
	static int used[N] = {0};

	if (dim == 2)
  	{
 	 /* If dim = 2, that means only two rows are not removed.
        and the column is definitely N-1 and N-2 */
		for (k = 0; k < N; k++)
			if (used[k] != 1) 
        		p[s++] = k;
 
 	/* Return Value */
		return A[p[0]][N-2]*A[p[1]][N-1] - A[p[0]][N-1]*A[p[1]][N-2];   
	}
	else if (dim > 2)
  	{
    	j = N - dim;	// Set the column.
		dim--;
	/*  Start the algorithm from A[0][0] */
    	for (i = 0; i < N; i++)
    	{
     	 /* find the first row that wasn't removed in previous recursion. */
        	if (used[i] != 1)  
        	{
          		used[i] = 1;  // Removed the row
            
       		 /* Get the value of the related elements of A
			 	and update the sign of minor.*/
          		value += sgn * A[i][j] * det(A, dim); 
              	sgn = -sgn;   
        	
       		 /* When coming back to current recursion,
          	    reset dim and used[i] and move to the next row. */ 
          		used[i]=0; 
       
        	}	                      
    	}       
    	return value; 
  	}
}

/* 
  Dear professor:
	I've found bugs (thanks to my roomate). It's related to line 75 and 87.
	My last edition doesn't has variable "j" and thus cause error.
	However, in line 87 if I change the index A[i][j] to A[i][N-dim+1],
	things go wrong too. 
	We still don't know why though we've discussed.
	Thank you for your time letting me know what's the reason.

  Sincere,
  Benny Lee
*/



