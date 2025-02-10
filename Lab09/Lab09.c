/* EE231002 Lab09. Word Processing
   106061218, Cheng-En Lee
   Date: 2017/11/27
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LSTR 5000  // Define the max paragraph length

int N = 0;  // Number of characters per line

// Function declarations
int readline(char para[LSTR]);
void leftAlign(char para[LSTR]);
void center(char para[LSTR]);
void bothAlign(char para[LSTR]);
void printJustified(char *line, int lineLength);

int main(int argc, char *argv[]) 
{
    char para[LSTR]; // Buffer to store paragraph input
    char mode; 		 // Variable to store alignment mode

    // Check for correct argument count
    if (argc != 3) 
    {
        printf("Usage: %s <line_length> <mode>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);  // Read max line width from argument
    mode = argv[2][0];   // Read alignment mode from argument

    // Read and process paragraphs until EOF is detected
    while (readline(para) != 1)
        switch(mode) 
		{
            case 'l': leftAlign(para); break; // Left alignment
            case 'c': center(para);    break; // Center alignment
            case 'b': bothAlign(para); break; // Both-edge alignment
            default: printf("Invalid argument\n"); exit(1); // Handle invalid mode
        }
    return 0;
}

// Function to read a paragraph from input
int readline(char para[LSTR]) 
{
    if (!fgets(para, LSTR, stdin)) return 1; 	// Read line, return 1 if failed
    if (strncmp(para, "EOF", 3) == 0) return 1; // Detect end of file
    para[strcspn(para, "\n")] = '\0';  			// Remove trailing newline character
    return 0;
}

// Function to left-align text
void leftAlign(char para[LSTR]) 
{
    int i = 0, start = 0, len = strlen(para); // Initialize variables
    while (start < len) 
	{
        int end = start + N; // Determine where to break line
        if (end >= len) 
		{ 
			// If remaining text fits in one line
            printf("%s\n", &para[start]);
            break;
        }
        while (end > start && para[end] != ' ') 
			end--;	// Find last space before N
        if (end == start) 
			end = start + N;	// No spaces found, force break
        para[end] = '\0';		// Terminate line
        printf("%s\n", &para[start]);
        start = end + 1;		// Move to the next part of the paragraph
    }
}

// Function to center-align text
void center(char para[LSTR]) 
{
    int i = 0, start = 0, len = strlen(para);
    while (start < len) 
	{
        int end = start + N;
        if (end >= len) 
		{
            int padding = (N - (len - start)) / 2; // Calculate padding for centering
            printf("%*s%s\n", padding, "", &para[start]); // Print centered text
            break;
        }
        while (end > start && para[end] != ' ') 
			end--;
        if (end == start) 
			end = start + N;
        para[end] = '\0';
        int padding = (N - (end - start)) / 2;
        printf("%*s%s\n", padding, "", &para[start]);
        start = end + 1;
    }
}

// Function to both-align text
void bothAlign(char para[LSTR]) 
{
    int i = 0, start = 0, len = strlen(para);
    while (start < len) 
	{
        int end = start + N;
        if (end >= len) 
		{
            printf("%s\n", &para[start]); // If last line, left-align it
            break;
        }
        while (end > start && para[end] != ' ') 
			end--;
        if (end == start) 
			end = start + N;
        para[end] = '\0';
        printJustified(&para[start], end - start); // Justify text
        start = end + 1;
    }
}

// Function to print a justified line
void printJustified(char *line, int lineLength) 
{
    int spaces = 0, extraSpaces=0, i=0, j=0;

    for (i = 0; i < lineLength; i++)
        if (line[i] == ' ') spaces++; // Count spaces in the line
    
    if (spaces == 0) // If no spaces, print line as is
	{ 
        printf("%s\n", line);
        return;
    }
    
    extraSpaces = (N - lineLength) / spaces; 		// Calculate extra spaces per word
    int extraRemainder = (N - lineLength) % spaces; // Calculate remaining spaces
    
    for (i = 0; i < lineLength; i++) 
	{
        putchar(line[i]); // Print each character
        if (line[i] == ' ') 
		{ 
			// If space is encountered
            for (j = 0; j < extraSpaces; j++) 
				putchar(' ');	// Insert extra spaces

            if (extraRemainder > 0) 
			{ 
				// Distribute remaining spaces evenly
                putchar(' ');
                extraRemainder--;
            }
        }
    }
    printf("\n"); // Print newline
}
