/* EE2310 Lab13. String Encoding
   106061218, Cheng-En, Lee
   2017/12/25
*/

/*
	Dear professor:
  	I've fixed all bugs, though it's a little bit late.
  	BTW, An interesting anecdote is that I found the original
  	text on the Internet by decoding the first line of the
  	etext.cd bare hands. XD
*/

#include <stdio.h>
#include <string.h>

int main(void)
{
/* 	line[150]: A single line. Its legnth is determined by the line length char.
	ptr: a pointer points to the line.
   	length: The line length char.
   	buf[4]: A group of encoded letters.
   	i: Used in the decoding loop.
   	stop: To stop a loop.
*/
	char line[150] = {'\0'}; 
  	char *ptr;
	char length = 0;
	char buf[4] = {'\0'};
  	int i = 0;
  	int stop = 0;
  
	while(getchar() != '\n');  // Skip The first line.
  
  	while (stop == 0)
  	{
  	 /* Read in the line length char but skip the line-changing 
	 	char and decode by inversing the rule of bit-5 check.
     	(Here's why last edition was wrong: I misunderstood
     	the rule to decode line length char and didn't skip
     	the line-changing char.) */
		length = getchar();   
    	if (length == '\n')  
      		length = getchar();
    	if (length > 64)     // Decode the line length char
		  	length -= 64;    
  
 	 /* The program decodes a single line and print each time. */
		for (ptr = &line[0]; ptr <= &line[length-1]; )
	  	{
   		 /* Reads in a group of decoded letters which has 4 
      		alphabet; Decode by inversing the rule of bit-5 check. */
  			for (i = 0; i < 4; i++)
		  	{
				buf[i] = getchar();
        		if (buf[i] >= 64)
         	 		buf[i] -= 64;
		  	}  
    
   		 /* Check if it reads "end". Because the ASCII code numbers 
      		of each letter, proper adjustments would be done. */
      		if ((length == 'e'-64)&&(buf[0] == 'n'-64)&&(buf[1] == 'd'-64))
        		stop = 1;
      
   		 /* Decoding Part: Treat the ASCII codes as binary 
      		numbers, A group of letters would convert into 3 
      		letters. each char should shift different digits 
      		left or right and would be combined with its neighbor. */ 
			*ptr++ = (buf[0]<<2) + (buf[1]>>4);  
		  	*ptr++ = (buf[1]<<4) + (buf[2]>>2);   
      		*ptr++ = (buf[2]<<6) + buf[3];
	  	}
    	*ptr++ = '\0';  // Set the end of each line to print.
    
    	if (stop == 0)  // Don't print the last line "end".
      		printf("%s",line); 
  }

	return 0;
}


