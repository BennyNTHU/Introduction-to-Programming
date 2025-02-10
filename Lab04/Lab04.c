/* EE231002 Lab04. Deciphering Roman Numerals
   106061218, Cheng En Lee
   Date: 2017/10/16
*/

#include <stdio.h>

int main() 
{
    char cRoman; // Each Roman numeral character input
    int prev_value = 0, curr_value = 0; // Previous and current numeral values
    int nSum = 0; // Decimal output

    printf("Input a Roman Numeral: ");
    
    while (1) 
	{ 
        scanf("%c", &cRoman);	// Read characters until newline
        
        // Assign value to the current Roman numeral
        switch (cRoman) 
		{
            case 'I': curr_value = 1; break;
            case 'V': curr_value = 5; break;
            case 'X': curr_value = 10; break;
            case 'L': curr_value = 50; break;
            case 'C': curr_value = 100; break;
            case 'D': curr_value = 500; break;
            case 'M': curr_value = 1000; break;
            case '\n': curr_value = 0; break; // Stop processing on newline
            default: continue; 				  // Ignore invalid characters
        }

        if (curr_value == 0) break; 		  // Stop if newline is encountered

        // If previous value is smaller, subtract it from the total
        if (prev_value < curr_value)
            nSum += curr_value - 2 * prev_value;
        else
            nSum += curr_value;
        
        prev_value = curr_value; // Update previous value for next iteration
    }
    
    printf("The value is: %d\n", nSum);
    return 0;
}
