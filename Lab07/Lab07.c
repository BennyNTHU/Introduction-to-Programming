/* EE231002 Lab07. Matrix Determinants
   106061218 Cheng-En Lee
   Date: 2017/11/13
*/

#include <stdio.h>
#if !defined(N)
#define N 12
#endif

// Function declaration
double det(double A[N][N], int dim);

int main(void) 
{
    double A[N][N];  // The input matrix
    int i, j;
    double ans;

    // Read matrix input
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            scanf("%lf", &A[i][j]);

    // Print the matrix
    printf("Matrix A is:\n");
    for (i = 0; i < N; i++) 
	{
        printf("  ");
        for (j = 0; j < N; j++)
            printf("%lg ", A[i][j]);
        printf("\n");
    }

    // Compute determinant
    ans = det(A, N);
    printf("det(A) = %lg\n", ans);
    
    return 0;
}

// Function to compute determinant recursively
double det(double A[N][N], int dim) 
{
	double minor[N][N]; // Temporary minor matrix
    double value = 0;
    int i, j, k;

    if (dim == 1)	// Base case: 1x1 matrix
        return A[0][0]; 
    
    if (dim == 2)	// Base case: 2x2 determinant calculation
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];
    
    for (k = 0; k < dim; k++) 
	{
        // Construct the minor matrix by removing row 0 and column k
        for (i = 1; i < dim; i++) 
		{
            int colIndex = 0;
            for (j = 0; j < dim; j++) 
			{
                if (j != k) 
				{
                    minor[i-1][colIndex] = A[i][j];
                    colIndex++;
                }
            }
        }
        // Recursive determinant calculation
        value += ((k % 2 == 0 ? 1 : -1) * A[0][k] * det(minor, dim - 1));
    }
    return value;
}
