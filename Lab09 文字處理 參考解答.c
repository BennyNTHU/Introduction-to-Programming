/* EE231002 Lab10. Word Processing
   
   Date:2016/12/05
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSTR 5000

int N;
int readLine(char para[LSTR]); 
void leftAlign(char *para);    
void center(char *para);       
void bothAlign(char *para);

int main(int argc,char *argv[])
{
	char para[LSTR];
	char mode;
	
	N = atoi(argv[1]);  
	mode = argv [2][0];
	        
	while (readLine(para) == 0) {
		switch (mode) {    
            case 'l':
                leftAlign(para); 
                break;
            case 'c':
                center(para); 
                break;
            case 'b':
                bothAlign(para); 
                break;
            default:        
                printf("Ilegal mode!");
        }	
	}
	printf("\n");		
	return 0;
}
int readLine(char para[LSTR])
{
	long int ncount=0;
    char c;
	//define ncount as the number of words
	//c as the words 

	c = getchar();
	while (c != '\n') {
		para[ncount] = c;
		ncount++;
		c = getchar();
	}
	para[ncount] = '\n';
	ncount++;
	para[ncount] = '\0';
	//to let it read paragraph by paragraph
	if (para[0] == 'E' && para[1] == 'O' && para[2] == 'F')
		return 1;
	else
		return 0;
	//when it reads till EOF, it will return 1
	//else it will return 0
}

void leftAlign(char *para)
{ 
	char line[N];
    char temp[100]; int tcount = 0;
	char c;
	int pcount = 0, i, lcount = 0;
	//define line as the line of the paragraph
	//temp as the words which will be divided by different lines
	//tcount as the number of terms of temp
	//c as the words
	//pcount as the number of terms of paragraph
	//lcount as the number of terms of line

	c = para[pcount++];
	while (c != '\0') {
		if (c == ' ') {
			temp[tcount] = '\0';
			if (tcount > N-lcount) {
				line[lcount - 1] = '\0';
				printf("%s\n", line);
				lcount = 0;
				for (i = 0; i < tcount; i++) {
					line[lcount++] = temp[i];
				}
				line[lcount++]=' ';
			}
			else {
				for (i = 0; i < tcount; i++) {
					line[lcount++] = temp[i];
				}
			    line[lcount++] = ' ';
			}
			tcount = 0;
		}
		else {
			temp[tcount++] = c;
		}
		c=para[pcount++];
	}
	//to check whether the words will be divided by different lines
	//if it does,temp will store the word and let it appear on the next line
	if (tcount > N-lcount) {
		line[lcount - 1] = '\0';
		printf("%s\n", line);
		lcount = 0;
		for (i = 0; i < tcount; i++) {
			line[lcount++] = temp[i];
		}
		line[lcount++] = ' ';
	}
	else {
		for (i = 0; i < tcount; i++) {
			line[lcount++] = temp[i];
		}
	}
	if (lcount != 0) {
		line[lcount] = '\0';
		printf("%s",line);
	}
	//repeat the same thing but this one only check the last word
}

void center(char *para)
{
    char line[N], print[N];
	char temp[100]; int tcount = 0;
	char c;
	int pcount = 0, i, lcount = 0, printcount = 0;
	//define line as the line of the paragraph
	//print as the things that we print out
	//temp as the words which will be divided by different lines
	//tcount as the number of terms of temp
	//c as the words,pcount as the number of terms of paragraph
	//lcount as the number of terms of line
	//printcount as the number of terms of print

	c=para[pcount++];
	while (c != '\0') {
		if (c == ' ') {
			temp[tcount] = '\0';
			if (tcount > N-lcount) {
				line[lcount - 1] = '\0';
				for (i = 0; i < (N + 1 - lcount) / 2; i++) {
					print[printcount++] = ' ';
				}
				for (i = 0; i < lcount; i++) {
					print[printcount++] = line[i];
				}
				for (i = 0; i < (N + 1 - lcount) / 2; i++) {
					 print[printcount++] = ' ';
				}
				print[printcount] = '\0';
				printcount = 0;
				printf("%s\n", print);
				//to calculate the spaces left
				//so that we can add spaces in front and behind the words

				lcount = 0;
				for (i = 0; i < tcount; i++) {
					line[lcount++] = temp[i];
				}
				line[lcount++]=' ';
			}
			else {
				for (i = 0; i < tcount; i++) {
					line[lcount++] = temp[i];
				}
				line[lcount++] = ' ';
			}
			tcount = 0;
		}
		else {
			temp[tcount++] = c;
		}
		c = para[pcount++];
	}
	//to check whether the words will be divided by different lines
	//if it does,temp will store the word and let it appear on the next line
	if (tcount > N-lcount) {
		line[lcount-1] = '\0';
		for (i = 0; i < (N + 1 - lcount) / 2; i++) {
			print[printcount++]=' ';
		}
		for (i = 0; i < lcount; i++) {
			print[printcount++]=line[i];
		}
		for (i = 0; i < (N + 1 - lcount) / 2; i++) {
			print[printcount++] = ' ';
		}
		print[printcount] = '\0';
		printcount = 0;
		printf("%s\n", print);
		
		lcount = 0;
		for (i = 0; i < tcount; i++) {
			line[lcount++] = temp[i];
		}
		line[lcount++] = ' ';
	}
	else {
		for (i = 0; i < tcount; i++) {
			line[lcount++] = temp[i];
		}
	}
	if (lcount != 0) {
		line[lcount] = '\0';
		for (i = 0; i < (N + 1 - lcount) / 2; i++) {
			print[printcount++] = ' ';
		}
		for (i = 0; i < lcount; i++) {
			print[printcount++] = line[i];
		}
		for (i = 0; i < (N + 1 - lcount) / 2; i++) {
			print[printcount++] = ' ';
		}
		print[printcount] = '\0';
		printcount = 0;
		printf("%s\n", print);
		//repeat the same thing but this one only check the last word
	}
}

void bothAlign(char *para)
{
    char line[N];
	char temp[100]; int tcount = 0;
	char c;
	int i,j;
	int pcount = 0, lcount = 0, spacecount;
	//define line as the line of the paragraph
	//temp as the words which will be divided by different lines
	//tcount as the number of terms of temp
	//c as the words,i and j as the parameter
	//pcount as the number of terms of paragraph
	//lcount as the number of terms of line
	//spacecount as the spaces between words

	c=para[pcount++];
	while (c!='\0') {
		if (c==' ') {
			temp[tcount] = '\0';
			if (tcount > N-lcount) {
				line[lcount-1] = '\0';
				spacecount = N + 1 - lcount;
				while (spacecount > 0) {
					for (i = 0; i < N; i++) {
						if (line[i] == ' ' && spacecount > 0) {
							for (j = N; j > i; j--) {
								line[j] = line[j-1];
							}
							line[i++] = ' ';
							spacecount--;
				//to calculate the spaces left
				//and the spaces will be added between words
				//when a space is given between words
				//it will skip to the next space and add in a new space
						}
					}
				}
				printf("%s\n", line);
				lcount = 0;
				for (i = 0; i < tcount; i++) {
					line[lcount++] = temp[i];
				}
				line[lcount++] = ' ';
			}
			else {
				for (i = 0; i < tcount; i++) {
					line[lcount++] = temp[i];
				}
				line[lcount++] = ' ';
			}
			tcount = 0;
		}
		else {
			temp[tcount++] = c;
		}
		c=para[pcount++];
	}
	//to check whether the words will be divided by different lines
	//if it does,temp will store the word and let it appear on the next line
	if (tcount > N-lcount) {
		line[lcount-1] = '\0';
		printf("%s\n", line);
		lcount = 0;
		for (i = 0; i < tcount; i++) {
			line[lcount++] = temp[i];
		}
		line[lcount++] = ' ';
	}
	else {
		for (i = 0; i < tcount; i++) {
			line[lcount++] = temp[i];
		}
	}
	if (lcount != 0) {
		line[lcount] = '\0';
		printf("%s",line);
	//repeat the same thing but this one only check the last word
	}
}



