/* EE2310 Lab09. Word Processing
   106061218, Cheng-En Lee
   Date:2017/11/27
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LSTR 5000

int N = 0;  // Numbers of literals of a single line.

int readline(char para[LSTR]);
void leftAlign(char *para); 
void center(char *para);
void bothAlign(char *para);
void bprint(char *para);

int main(int argc, char *argv[])
{
	char para[LSTR] = {'\0'};  	 // The paragragh.
	char mode = '0';  		  	 // argv[2].

	N = atoi(argv[1]);  	  	 // Set when execute ./a.out.
	mode = argv[2][0];     		 // Set when execute ./a.out.
	
	while (readline(para) != 1)  // Not EOF
	{	
		switch(mode)
		{
			case 'l': leftAlign(para); break;
			case 'c': center(para);    break;
			case 'b': bothAlign(para); break;
      		default : printf("illegal argument\n"); 
                	  exit(1);
		}
	}

 	printf("\n");
	return 0;
}


int readline(char para[LSTR])
{
	char ch = '0';
  	int i = 0;			 // Index of para.

	while (ch != '\n')	 // Paragraghs end when changing line.
	{
		ch = getchar();  // Read the paragragh character by character.
		if (i < LSTR)
			para[i++] = ch;
	}
 	para[i] = '\0';  	 // Set the end of a paragragh.

	if ((para[0] == 'E') && (para[1] == 'O') && (para[2] == 'F'))
		return 1;  		 // End of file.
	else
		return 0;		 // End of a paragragh.
}


void leftAlign(char *para)
{
	int i = 0;

 /* If the length of the paragragh is less than N,
 	than print it right away. */
	if (strlen(para) <= N)	
		printf("%s\n",para);

 /* Normal Cases: Longer than N.*/
	else
	{	
	 /* Find the last space of a single line. */
		for (i = N; para[i] != ' '; i--);
	 
	 /* If the paragragh has successive blanks,
	 	find the first of them. */
		while (para[i-1] == ' ')
			i--;

		para[i] = '\0';				// Tag the end of the line.
		printf("%s\n",para);		// Print.
		while (para[i+1] == ' ')	// Find the first char of the next line.
			i++;
		leftAlign(para+i+1);		// Process the next line.
	}
}

/*******center函數有問題,是錯的********/ 
void center(char *para)
{
	int i = 0;
	int k = 0;	// total blanks need in a single line.
	int j = 0;  // index.

 /* If the length of the paragragh is less than N,
 	than print it right away. */
	if (strlen(para) <= N)	
	{	
 		k = N - strlen(para);	// Total blanks needed.
		
     /* Print the blanks in the front and end of a line,
	 	and also the text. */
		for (j = 1; j <= k/2; j++)
			printf(" ");	
		printf("%s",para);		
		for (j = (k/2)+1; j <= k; j++)
			printf(" ");
		printf("\n");
	}

 /* The other cases: Longer than N.*/
	else
	{	

		for (i = N; para[i] != ' ';i--);
	 
	 /* If the paragragh has successive blanks,
	 	find the first of them. */
		while (para[i-1] == ' ')
			i--;

		para[i] = '\0';	// Tag the end of the line.
		
		k = N - i;		// Total spaces need in a single line.

	 /* Print the blanks in the front and end of a line */
		for (j = 1; j <= k/2; j++)
			printf(" ");	
		printf("%s",para);		
		for (j = (k/2)+1; j <= k; j++)
			printf(" ");
		printf("\n");

		while (para[i+1] == ' ')	// Find the first char of the next line.
			i++;
		leftAlign(para+i+1);		// Process the next line.
	}

}


void bothAlign(char *para)
{
 /* This function works similar to "leftAkign".
 	but replace "printf" with "bprint". */

	int i = 0;

	if (strlen(para) <= N)
		bprint(para);
	else
	{
		for (i = N; para[i] != ' '; i--);
		while (para[i-1] == ' ')
			i--;
		para[i] = '\0';
		bprint(para);
		while (para[i+1] == ' ')
			i++;
		bothAlign(para+i+1);
	}

}


void bprint(char *line)
{
	int i = 0;				// The index of a line.
	double k = 0;			// amount of blanks (but not successive).
	double x = 0, y = 0;	

 /* x and y are used for determine whether to put an extra space.
 	x will be assigned as the space needed in the end of a single
	line first. */
	x = N-strlen(line);
	
 /* Counting the amount of not blanks between words. */	
	for (i = 0; i < strlen(line); i++)
		if ((line[i] == ' ') && (line[i+1] != ' '))
			k++;

 /* y is the ratio of x and k (amounts of blanks). 
 	and assign x as 0.5 for resonable frequency 
	that extra blanks appear. In other word, the
	two varibles brings the blanks at the end of 
	each line to a reasonable place in the line. */	
	y = x/k;
	x = 0.5;

 /* Each line will be printed character by character.
 	and decides whether to put extra space between words. */
	for (i = 0; line[i] != '\0'; i++)
	{
	 /* Encounter a blank and the next character is not another blank. */
		if ((line[i] == ' ') && (line[i+1] != ' '))
		{
			
		 /* Each times encounter a blank, x would plus y
		 	until x > 1. That means it's the timing that
			an extra spaces should appear. */
			x+=y;
			
			if (x >= 1)			// Need extra space.
			{
				printf(" ");

			 /* Reset x for next timing an extra space should appear. */
				x -= 1;			
			}
			printf(" ");		// The initial space exist in the line.
		}

	 /* Encounter an character which isn't a space. */
		else
			printf ("%c",line[i]);
	}

 /* Change lines. The next line would be processed identically. */
	printf("\n");	
}





