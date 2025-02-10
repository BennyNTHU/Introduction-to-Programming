/* EE231002 Lab05. Permutations
   106061218, Cheng En Lee
   Date: 2017/10/24
*/

#include <stdio.h>
#define N 4  // Define the number of elements

int main(void) 
{
    long factorial_N = 1; // Stores N!
    int j_index, k_index, i, temp; // Indices for swapping and temporary variable
    int seq[N];  // The sequence to be permuted
    
    // Compute N! (factorial)
    for (i = 1; i <= N; i++)
        factorial_N *= i;
    
    // Initialize the sequence in descending order
    for (i = 0; i < N; i++)
        seq[i] = N - i;
    
    printf("permutation #1:");
    for (i = 0; i < N; i++)
        printf(" %d", seq[i]);

    printf("\n");
    
    // Generate permutations using Narayan Pandia's algorithm
    for (int perm_count = 2; perm_count <= factorial_N; perm_count++) 
    {
        printf("permutation #%d:", perm_count);
        
        // Step 1: Find the largest j such that seq[j] > seq[j+1]
        j_index = N - 2;
        while (j_index >= 0 && seq[j_index] < seq[j_index + 1])
            j_index--;
        
        // Step 2: Find the largest k such that seq[j] > seq[k]
        k_index = N - 1;
        while (seq[j_index] < seq[k_index])
            k_index--;
        
        // Step 3: Swap seq[j] with seq[k]
        temp = seq[j_index];
        seq[j_index] = seq[k_index];
        seq[k_index] = temp;
        
        // Step 4: Reverse the sequence from seq[j+1] to seq[N-1]
        for (i = j_index + 1; i < (j_index + 1 + N) / 2; i++) 
        {
            temp = seq[N - 1 - (i - (j_index + 1))];
            seq[N - 1 - (i - (j_index + 1))] = seq[i];
            seq[i] = temp;
        }
        
        for (i = 0; i < N; i++)
            printf(" %d", seq[i]);
            
        printf("\n");
    }
    
    printf("Total number of permutations is %ld\n", factorial_N);
    return 0;
}
