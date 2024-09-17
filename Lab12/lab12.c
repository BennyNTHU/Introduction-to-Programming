/* EE2310 Lab12. GCD and LCM
   106061218, Cheng-En, Lee.
   Date:2017/12/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct factor {
	int prime;
	int power;
	struct factor *next;
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


int main(int argc, char *argv[])
{
	FACTOR *A;
	FACTOR *B;
    FACTOR *sGCD;
	FACTOR *sLCM;

 /* Allocate memories for each structure. */
  	A = (struct factor *)malloc(sizeof(struct factor));
  	B = (struct factor *)malloc(sizeof(struct factor));
  	sGCD = (struct factor *)malloc(sizeof(struct factor));
  	sLCM = (struct factor *)malloc(sizeof(struct factor));
 
 /* Factorize two comment line arguments and calculate GCD and LCM. */
  	A = factorize(atoi(argv[1]));
  	B = factorize(atoi(argv[2]));
  	sGCD = GCD(A,B);
  	sLCM = LCM(A,B);
 
 /* Print the factorized number, GCD and LCM. */
  	printf("A = ");		write(A);
  	printf("B = ");		write(B);
  	printf("GCD = ");	write(sGCD);
  	printf("LCM = ");	write(sLCM);

	return 0;
}


FACTOR *factorize(int N)
{
	int makeprime = 0;	// To make the sequence of primes.
	int i = 0;
 	int pwr = 0;
  	struct factor *new_node;
  	struct factor *first;

 /* To test whether prime factors include 2 and 3. */
  	first = NULL;
  	if (N%2 == 0)
	{
	 /* Make an new node and assign the value.*/
    	new_node = (struct factor *)malloc(sizeof(struct factor));
		new_node->prime = 2;
     
	 /* The loop test the power of the factor by dividing successively */
		for (i = 0; N%2 == 0; N = N/2, i++);
  		new_node->power = i;

	 /* Let "first" points to "new node." */
	  	new_node->next = first;
    	first = new_node;
	}
  
  
 /* Anologous with the codes above. */
  	if (N%3 == 0)
	{
    	new_node = (struct factor *)malloc(sizeof(struct factor));
		new_node->prime = 3;
		for (i = 0; N%3 == 0; N = N/3, i++);
    	new_node->power = i;
	  	new_node->next = first;
    	first = new_node;
	}
  
 /* To make sequence of primes. */
	for (makeprime = 5; N != 1; makeprime+=2)
		for (i = 2; (makeprime%i!=0)&&(i*i<=makeprime); i++)
			if ( (i+1)*(i+1)>makeprime )	// Get a prime.
				if (N % makeprime == 0)		// Is it a factor?
				{	
				 /* Anologous with the case of 2 and 3. */
					new_node = (struct factor *)malloc(sizeof(struct factor));
		      		new_node->prime = makeprime; 
          			for (pwr = 0; N%makeprime == 0; N = N/makeprime, pwr++);
		      		new_node->power = pwr;
	        		new_node->next = first;
          			first = new_node;
   				}

	return first;
}


FACTOR *GCD(FACTOR *A, FACTOR *B)
{
  	struct factor *new_node;
  	struct factor *first;
  	struct factor *ptr1, *ptr2;

 /* ptr1 and ptr2 is assigned according to A and B's largest 
 	prime factor. ptr1 is the smaller one while ptr2 is the
	bigger one. */
  	if (A->prime <= B->prime)
  	{
    	ptr1 = A;
    	ptr2 = B;
  	}
  	else
  	{
    	ptr1 = B;
    	ptr2 = A;
 	}
  
  	first = NULL;  // Make new nodes.
  	while ((ptr1 != NULL)&&(ptr2 != NULL))
  	{
   	 /* Compare two largest primes. If one is too big, the 
      	pointer points to other one would go to the next 
      	node. It'll repeat until the two prime factors are same. */
    	if (ptr1->prime < ptr2->prime)
      		ptr2 = ptr2->next;
    	else if (ptr1->prime > ptr2->prime)
      		ptr1 = ptr1->next;
    	else if (ptr1->prime == ptr2->prime)
    	{  
       	 /* Assign the memory location and values. 
          	For GCD, The smaller power suits. */
    	
      		new_node = (struct factor *)malloc(sizeof(struct factor));
      		new_node->prime = ptr1->prime;
      		new_node->power = ptr1->power > ptr2->power ? 
                            ptr2->power : ptr1->power;
        
        /* Update the pointers. */     		
      		new_node->next = first;
      		first = new_node;
      		ptr1 = ptr1->next;
      		ptr2 = ptr2->next;
		}
	}

  	return first;
}


FACTOR *LCM(FACTOR *A, FACTOR *B)
{
	struct factor *ptr1, *ptr2;
	struct factor *new_node;
	struct factor *first;

	if (A->prime <= B->prime)
	{
		ptr1 = A;
		ptr2 = B;
	}
	else
	{
		ptr1 = B;
		ptr2 = A;
	}
	
	first = NULL;
  	while ((ptr1 != NULL)&&(ptr2 != NULL))
	{
		if (ptr1->prime == ptr2->prime)
		{	
			new_node = (struct factor *)malloc(sizeof(struct factor));
      		new_node->prime = ptr1->prime;
			new_node->power = ptr1->power > ptr2->power ?
							  ptr1->power : ptr2->power;

			new_node->next = first;
			first = new_node;
			ptr1 = ptr1->next;
		}
		else
		{

      		new_node = (struct factor *)malloc(sizeof(struct factor));
      		new_node->prime = ptr1->prime > ptr2->prime ?
							  ptr1->prime : ptr2->prime;
      		new_node->power = ptr1->prime > ptr2->prime ? 
                              ptr1->power : ptr2->power;
        
        /* Update the pointers. */     		
      		new_node->next = first;
      		first = new_node;
      		if (ptr1->prime > ptr2->prime)
				ptr1 = ptr1->next;
			else
				ptr2 = ptr2->next;
		}
	}
}


void write (FACTOR *A)
{
  	int product = 1;
  	int i = 0;
  	struct factor *ptr;	// A copy of A.
   
	for (ptr = A; ptr != NULL; ptr = ptr->next)
	{
	 /* Product the prime factors successively according to their power. */
    	for (i = 0; i < ptr->power; i++)
      		product = product * ptr->prime;
    
		printf("%d ^ %d ", ptr->prime, ptr->power);
    	if (ptr->next != NULL) // Don't print "*" at the end.
      		printf("* ");
	}
	
	if (product != 1)
		printf("= %d\n", product);
	else
		printf("1\n");
}


