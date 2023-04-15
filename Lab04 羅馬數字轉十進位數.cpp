/* EE2310 Lab04. Deciphering Roman Numerals
   106061218, Cheng En Lee
   Date: 2017/10/16
   In C, not C++. 
*/

# include <stdio.h>

int main ()
{
	char cRoman = ' ';					// Each Roman number letter input.
	int nbuffer = 0, npivot;		// nbuffer is the letter before npivot.
	int nSum = 0; 					// Decimal numbers output.

	printf ( "Input a Roman Numeral: " );
	while ( cRoman != '\n' )		// Stop keying in if it's linefeed.
	{	
		scanf ( "%c" ,&cRoman );	// Input a Roman Number letter.
		switch ( cRoman )			// Value of each letter.
		{
			case 'I' : npivot = 1;		break;
			case 'V' : npivot = 5;		break;
			case 'X' : npivot = 10;		break;
			case 'L' : npivot = 50;		break;
			case 'C' : npivot = 100;	break;
			case 'D' : npivot = 500;	break;
			case 'M' : npivot = 1000;	break;
			case '\n': npivot = 0;		
		}

  		if ( npivot > nbuffer )					
	 // Then nbuffer should substracted from both Sum and npivot 
	 // and then additive to the sum.  
	  		nSum = nSum - 2*nbuffer + npivot;	
  		else									
	 // Then additive the sum from left to right.
      		nSum += npivot;
			
    	nbuffer = npivot;			
   	 // Passing the value of the current letter from right to left.
	} 
	printf( "The value is: %d\n" , nSum );
	return 0;
}

