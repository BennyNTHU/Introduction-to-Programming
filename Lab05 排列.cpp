/* Find every permutations of an sequence
   Using Narayan Pandia algorithm
   Developer: Benny Lee
   2017/10/24
   Develop with C
*/

# include <stdio.h>
# define N 4

int main(void)
{
  long lfactor = 1;          	 // N!
  long ltimes = 1;          	 // List N! permutations.
  int m = 0, p = 0, i = 0;   	 // Index of loops.
  int nseq[N] = {0};         	 // Sequence which would be permuted.
  int nbuffer = 0;           	 // Varible to switch two values.
	
	for( m = N ; m > 0 ; m-- )	 // Calculate N!.
		lfactor = lfactor * m;
 
	printf( "permutation #1:" );
	for ( m = 0 ; m < N ; m++ )	 // Assign the sequence.
	{
		nseq[m] = (N-m);         // nseq[m] = {1, 2, 3, ...}
		printf(" %d", nseq[m]);	 // List the first permutation.
	}

	for ( ltimes = 2 ; ltimes <= lfactor ; ltimes ++ ) 	// Start permutation.
	{
    	printf( "\npermutation #%d:" ,ltimes );
		for ( m = (N-1) ; nseq[m] > nseq[m-1] ; m-- );	 // Find largest m such that a[m-1] > a[m].
		for ( p = (N-1) ; nseq[p] >= nseq[m-1] ; p-- );  // Find largest p such that a[m-1] > a[p].
		
 		/* Swap a[m-1] with a[p]. */
		nbuffer = nseq[m-1];
		nseq[m-1] = nseq[p];
		nseq[p] = nbuffer;
   
    	for ( i = 0 ; i < N ; i++ )
		{
			if ( ( i>=m ) && ( i<=(m+N-1)/2 ) ) 		// Reverse nseq from a[m] to a[N-1]. 
			{
				nbuffer = nseq[m+N-1-i];				// For each a[x] should be swaped, we have i + x = m + (N-1). 
				nseq[m+N-1-i] = nseq[i];
				nseq[i] = nbuffer;
			}
			printf( " %d" ,nseq[i] );           // List the permutations.
		}
	}
	printf( "\n  Total number of permutations is %d\n" ,lfactor );
	return 0;
}

