/* EE231002 Lab08. Blackjack
   106061218, Cheng En Lee
   Date: 2017/11/20
*/

/* The program assume that you have a large amount decks of pock cards
   and calculate the expected value and busted probability.
   Also, calculate the probability of getting 21 points */

#include <stdio.h>
#include <stdlib.h>
#define N 100000          // Number of experiment.
#define TRUE 1            // Get Ace.
#define FALSE 0           // Doesn't get Ace.

int cardpoint();  // Function to generate card points

int main(void) 
{

	int nplayer_point = 0;  // The current total points hold.
	int ninit_point = 0;    // The initial points.
	int nnew_card = 0;      // The getting a new card.
	int flag = FALSE;       // Get Ace or not.
	int i = 0;              // Index of loops
	int ntimes = 0;         // Counting the cumulated times of busted
							// or getting 21 points.
	float fexpected = 0;    // The expected value.
	float fprob = 0;        // Probability of busted or getting 21 points.

    printf("Points  E(hit)   %% Busted\n");

    // Part 1: Compute expected value and bust probability
    for (ninit_point = 2; ninit_point <= 20; ninit_point++) 
	{
        fexpected = 0;
        ntimes = 0;

        for (i = 0; i < N; i++) 
		{
            nplayer_point = ninit_point;
            nnew_card = cardpoint();
            nplayer_point += nnew_card;

            if (nplayer_point > 21) ntimes++;
            fexpected += nplayer_point;
        }

        fexpected /= N;  			 // Compute expected value
        fprob = 100.0 * ntimes / N;  // Compute bust probability
        printf("%3d  %7.2f  %8.4g%%\n", ninit_point, fexpected, fprob);
    }

    // Part 2: Compute probability of getting exactly 21 points
    ntimes = 0;

    for (i = 0; i < N; i++) 
	{
        nplayer_point = 0;
        int has_ace = 0;

        while (nplayer_point < 21) 
		{
            nnew_card = cardpoint();
            if (nnew_card == 11) has_ace = 1;
            nplayer_point += nnew_card;

            if (nplayer_point > 21 && has_ace) 
			{
                nplayer_point -= 10;  // Convert Ace from 11 to 1
                has_ace = 0;
            }
        }

        if (nplayer_point == 21) ntimes++;
    }

    fprob = 100.0 * ntimes / N;
    printf("\nProbability of getting 21 points is %.4g%%\n", fprob);

    return 0;
}

// Function to generate card points
int cardpoint() 
{
    int card = rand() % 13 + 1;
    if (card == 1) return 11;
    if (card >= 11) return 10;
    return card;
}
