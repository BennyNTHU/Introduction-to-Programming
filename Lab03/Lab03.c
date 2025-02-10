/* EE231002 Lab03. Balanced Prime Numbers
   106061218, Cheng En Lee
   Date: 2017/10/11
*/

#include <stdio.h>

int main() 
{
    int count = 0; // Count of balanced prime numbers found
    int prev_prime = 3, curr_prime = 5, next_prime = 7; // Three consecutive primes
    int num = 0, is_prime = 0, sqrt_root = 0, i = 0;    // Used for finding prime numbers
	int found_prime = 0; // Flag to indicate when a prime is found
    
    while (count < 1000) 
	{
        // Check if the current prime is a balanced prime
        if (2 * curr_prime == prev_prime + next_prime) 
		{
            count++;
            // Print only the first 10 and last 10 balanced prime numbers
            if (count <= 10 || count >= 991)
                printf("Balanced Prime Number #%d: %d\n", count, curr_prime);
        }
        
        // Move to the next set of three prime numbers
        prev_prime = curr_prime;
        curr_prime = next_prime;
        
        // Find the next prime number
        num = next_prime + 2;
		found_prime = 0; // Flag to indicate when a prime is found
        
        while (!found_prime) 
		{
            is_prime = 1; // Assume the number is prime
            
            // Compute square root
            for (sqrt_root = 1; sqrt_root * sqrt_root <= num; sqrt_root++);
            sqrt_root--;
            
            // Check divisibility from 2 up to the sqrt_root
			for (i=2; (i<=sqrt_root) && is_prime; i++)
				if (num % i == 0) 
					is_prime = 0; // Not a prime number
            
            if (is_prime) 
			{
                next_prime = num;
                found_prime = 1; // Prime found, exit loop conditionally
            } 
			else
                num += 2; // Only check odd numbers to improve efficiency
        }
    }
    
    return 0;
}
