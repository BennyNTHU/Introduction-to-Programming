/* EE2310 Lab08. Blackjack
   106061218, Cheng En, Lee
   2017/11/20
*/

/* The program assume that you have a large amount decks of pock cards
   and calculate the expected value and busted probability.
   Also, calculate the probability of getting 21 points */

#include <stdio.h>
#include <stdlib.h>
#define N 100000          // Number of experiment.
#define TRUE 1            // Get Ace.
#define FALSE 0           // Doesn't get Ace.

int cardpoint(int nplayer_point);  // Hits.

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
  
/***Part 1: findind expected value and busted probability
    "fprob" means the probability of busted. ***/
  
	printf("Points  E(hit)  % Busted\n");
  
	for (ninit_point = 2; ninit_point <= 20; ninit_point++)
	{
    	for (i = 0; i < N; i++)        // Do the experiment N times.
    	{
      		nplayer_point = ninit_point; // Assign the initial points at hand.
      		nnew_card = cardpoint(nplayer_point);  // The player hits.
      		nplayer_point += nnew_card;            // Add the points.
      		if (nplayer_point > 21)                // Busted?
          		ntimes++;                          // Count the busted time.
           
      		fexpected += nplayer_point;  
		 // Sum up all the points of each experiment.
      		nplayer_point = 0;           
		 // Reset the points at hand.
    	}
    
    	fexpected = fexpected / N;     // E = The sum divides 100000.
    	fprob = 100 * ((float) ntimes) / N;       // Calculate the probability.
    	printf("  %2d\t %5.2f\t  %5.4g\n",ninit_point, fexpected, fprob); 
	 // Outputs. Accuracy of each float is 0.01 and follow the given format.
    	fprob = 0;  // Reset.
    	ntimes = 0; // Reset.
  	}

 /* Reset some variables */
	nplayer_point = 0;
	ntimes = 0;
	fprob = 0;
  
/***Part 2: The probability if getting 21 points.
    "fprob" means the probability of getting 21 points,
    "ntimes" is used as the counter.***/

 /* Do N the experiment N times. */
	for (i = 0; i < N; i++)
  	{
    	for (nplayer_point = 0; nplayer_point < 21; nplayer_point += nnew_card)
    	{

		 /* Get a new card. It may be A.
			If it's an Ace which would not result in busted,
			that is, take the Ace as 11 points,
			then record it. */
			nnew_card = cardpoint(nplayer_point);  
      		if (nnew_card == 11) 
        		flag = TRUE;  
     
   		 /* If busted but you've get an Ace and its initial points is 11 */
      		if ( (nplayer_point + nnew_card > 21) && (flag == TRUE) )
      		{  
          		nplayer_point -= 10;  // Treat the Ace as 1 point.
          		flag = FALSE;         // The Ace is "used".
      		}          
    	}
    
    	flag = FALSE;               // Reset the flag.
    	if (nplayer_point == 21)    // If getting 21 points.
      		ntimes++;               // Count the times of getting 21 points.
  	}
  
 /* Calculate the probability of getting 21 points and output. */
	fprob = 100 * ((float) ntimes) / N;  
	printf("\nProbability of getting 21 points is %.4g%\n",fprob);
	
	system("PAUSE");
  	return 0;
}


/* The "hits" fuction: return the points of the crad get. */
int cardpoint(int nplayer_point)
{
	int card = 0;
  
	card = rand() % 13 + 1;  // Hit.
	switch(card)
  	{
  	 /* If Ace would result in busted, then return 1 point */
    	case  1: return nplayer_point+11 > 21 ? 1 : 11; 
    	case 11: 
    	case 12: 
    	case 13: return 10;    // 11~13has 10 points.
    	default: return card;  // Oterwise, the cards has face points.
  	}
}



