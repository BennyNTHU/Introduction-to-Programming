/* EE231002 Lab12. GCD and LCM
   106061218, Cheng-En Lee
   Date: 2017/12/18
*/

#include <stdio.h>
#include <stdlib.h>

// Define Linked List Node Structure
typedef struct factor {
    int prime;           // Prime factor
    int power;           // Power of the prime factor
    struct factor *next; // Pointer to the next factor
} FACTOR;

/* Function prototypes:
   factorize: Dismantling the given number to find out the prime 
   			  factors and their powers which consist that in the
			  linked nodes.
   GCD: Find out the GCD of two numbers, whose return type is 
   		the factorized link list.
   LCM: Find out the LCM of two numbers and return its factorized
   		linked list.
   write: Show the formula of product of prime factors. 
*/
FACTOR *factorize(int N);
FACTOR *GCD(FACTOR *A, FACTOR *B);
FACTOR *LCM(FACTOR *A, FACTOR *B);
void write(FACTOR *A);
void insert_factor(FACTOR **head, int prime, int power);
void free_list(FACTOR *head);
FACTOR *merge_factors(FACTOR *A, FACTOR *B, int take_min);

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
	{
        printf("Usage: %s <num1> <num2>\n", argv[0]); // Print usage message if incorrect arguments
        return 1; // Exit with error code
    }
    
    int num1 = atoi(argv[1]);      // Convert first argument to integer
    int num2 = atoi(argv[2]);      // Convert second argument to integer
    
    FACTOR *A = factorize(num1);   // Factorize first number
    FACTOR *B = factorize(num2);   // Factorize second number
    FACTOR *sGCD = GCD(A, B);      // Compute GCD
    FACTOR *sLCM = LCM(A, B);      // Compute LCM
    
    printf("A = "); write(A);      // Print factorized first number
    printf("B = "); write(B);      // Print factorized second number
    printf("GCD = "); write(sGCD); // Print GCD
    printf("LCM = "); write(sLCM); // Print LCM
    
    // Free allocated memory
    free_list(A);
    free_list(B);
    free_list(sGCD);
    free_list(sLCM);
    
    return 0; // Exit successfully
}

// Factorize a number into prime factors
FACTOR *factorize(int N) 
{
    FACTOR *head = NULL; // Initialize head pointer to NULL
    int count;           // Variable to count power of each factor
    
    for (int i = 2; i * i <= N; i++) 
	{
        if (N % i == 0) 
		{
            count = 0;
            while (N % i == 0) 
			{
                N /= i;  // Reduce N by factor i
                count++; // Increment power count
            }
            insert_factor(&head, i, count); // Insert factor into linked list
        }
    }
    if (N > 1) 
		insert_factor(&head, N, 1); // If N is a prime number, insert it
    
    return head; // Return factorized list
}

// Compute the Greatest Common Divisor (GCD)
FACTOR *GCD(FACTOR *A, FACTOR *B) 
{
    return merge_factors(A, B, 1); // Merge factors taking minimum powers
}

// Compute the Least Common Multiple (LCM)
FACTOR *LCM(FACTOR *A, FACTOR *B) 
{
    return merge_factors(A, B, 0); // Merge factors taking maximum powers
}

// Insert a new factor node into the linked list
void insert_factor(FACTOR **head, int prime, int power) 
{
    FACTOR *new_node = (FACTOR *)malloc(sizeof(FACTOR)); // Allocate memory for new node
    new_node->prime = prime; // Assign prime factor
    new_node->power = power; // Assign power
    new_node->next = *head;  // Insert at the beginning of the list
    *head = new_node;        // Update head pointer
}

// Free the linked list
void free_list(FACTOR *head) 
{
    FACTOR *temp;
    while (head) 
	{
        temp = head;       // Store current node
        head = head->next; // Move to next node
        free(temp);        // Free current node
    }
}

// Merge two factor lists based on min (GCD) or max (LCM)
FACTOR *merge_factors(FACTOR *A, FACTOR *B, int take_min) 
{
    FACTOR *result = NULL, **last = &result; // Initialize result list
    while (A && B) {
        if (A->prime < B->prime) 
		{
            if (!take_min) insert_factor(&result, A->prime, A->power); // Insert if LCM
            A = A->next;
        } 
		else if (A->prime > B->prime) 
		{
            if (!take_min) insert_factor(&result, B->prime, B->power); // Insert if LCM
            B = B->next;
        } 
		else 
		{
            insert_factor(&result, A->prime, take_min ? 
			(A->power < B->power ? A->power : B->power) : (A->power > B->power ? A->power : B->power));
            A = A->next;
            B = B->next;
        }
    }
    while (A && !take_min) 
		insert_factor(&result, A->prime, A->power), A = A->next;
    while (B && !take_min) 
		insert_factor(&result, B->prime, B->power), B = B->next;
    return result; // Return merged list
}

// Print the factorized number
void write(FACTOR *A) 
{
    if (!A) // If the linked list is empty, print 1
	{
        printf("1 = 1\n");
        return;
    }
    
    int product = 1; // Initialize product value
    FACTOR *ptr = A;
    while (ptr) 
	{
        printf("%d^%d", ptr->prime, ptr->power); // Print factor
		
        for (int i = 0; i < ptr->power; i++) 
			product *= ptr->prime; // Compute product

        ptr = ptr->next; // Move to next factor

        if (ptr) 
			printf(" * "); // Print multiplication symbol if more factors exist
    }
    printf(" = %d\n", product); // Print final product value
}

