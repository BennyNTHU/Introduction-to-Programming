/* EE2310 lab06 Finding Sudoku Solutions.
   106061218, Cheng En, Lee.
   2017/10/30
*/
 
/*  Definations:
 *  We had to define some nouns in sudoku games.
 *  Blanks: The 81 squares which form the sudoku game.
 *			If the blank is unfilled initially, we call it is "available".
 *  Blocks: The 3*3 submatrix of sudoku game board.   
 */
 
#include <stdio.h>

/*  Global Variables:
 *  nsudoku[9][9]: The initial sudoku matrix. 
 *  bl_ava[82][2]: The matrix records the indexes of available blanks.
 * 				   Besides, to speak in extreme, 
 *				   if the sudoku matrix given is composed of nothing, 
 *				   the array will record all(81) indexes of the board.
 *				   
 *  count: The amounts of available blanks.
 *  found: The amounts of solutions found of the input sudoku game.
 *  current_answer[81]: Record the current numbers in "each" available blanks.
 *  i & j: Indexs of the nsudoku[i][j].
 *  c: Index of current_answer[82] and bl_ava[81][2]. 
 *     For the latter, c represents 1~82.
 */
int nsudoku[9][9];
int bl_ava[82][2]; 
int count = 0;
int found = 0;
int current_answer[81];  
int i = 0, j = 0, c = 0;

/*  Functions:
 *  initialize(): Initialize all global variables.
 *  readpuzzle(): The functions reads in the sudoku game 
 * 				  and record it in nsudoku[9][9].
 *                In addition,it also record the indexes of blanks available
 *				  in bl_ava[81][2].
 *                The available blanks will be record in 0 in nsudoku[9][9].
 *
 *  printpuzzle(): Show the solution of sudoku game.
 *  try_ans_checker(): Check if the current answer abides the sudoku rules.
 */
void initialize(void);
void readpuzzle(void);
int try_ans_checker(void);
void printpuzzle(void);

int main(void)
{  
  int next_blank = 0;  // Move to the next or previous blanks available.
  
  initialize();        // Initialize the global variables.
  readpuzzle();        // Reads in the sudoku.
  
/*If bl_ava[c][0] becomes -1, then all solutions would have found.
  if not, move to the next blank. */
  for( c = 0 ; bl_ava[c][0] != -1 ; c += next_blank )
  {
    i = bl_ava[c][0];  // Get current position.
    j = bl_ava[c][1];  

/*  The current blanks will try the numbers 1~9 alternatively 
	and check if it's legal. */
    for( current_answer[c] = (nsudoku[i][j]+1) ;  
         try_ans_checker() == 0 ; 
         current_answer[c]++ ) ; 
         
/*  In case that 1~9 are all illegal for a single blank. */ 
    if( current_answer[c] == 10 )
    {
      nsudoku[i][j] = 0;      // Then reset the blank and current answer.
      current_answer[c] = 0;  
      next_blank = -1;        // Move back to previous blank.
    }
    
/*  Cases of legal answers */
    else if( current_answer[c] != 10 )
    {
      nsudoku[i][j] = current_answer[c];  // Record the current answer.
	  next_blank = 1;                     // Move to the next available blank.
    }
    
/*  If the final blank is filled, that is, find 1 solution */    
    if( (i==bl_ava[count-1][0]) && (j==bl_ava[count-1][1]) )
    {
      found++;                       // One solution found.
      printpuzzle();                 // Show the answer.
      current_answer[count-1] = 0;   // Reset the final blank.
      nsudoku[bl_ava[count-1][0]][bl_ava[count-1][1]] = 0; 
      next_blank = -1;               // Move back to previous blank.
    }
    
/*  If the first blank become 10, 
    that means all solutions have found. */
    if( (nsudoku[bl_ava[0][0]][bl_ava[0][1]] > 9) || 
		(nsudoku[bl_ava[0][0]][bl_ava[0][1]] == 0) 	)
    {  
      next_blank = 0;
      bl_ava[c][0] = -1;  // Break out the loop.
    }
  }
  
/*List all solutions */  
  printf("Total number of solutions found: %d.\n\n",found);
  return 0;
}


void initialize(void)  // Initialize the global variables.
{
  for( i = 0 ; i < 9 ; i++ )
    for( j = 0 ; j < 9 ; j++ )
      nsudoku[i][j] = 0;
  
  for( c = 0 ; c < 81 ; c++ )
  {
    bl_ava[c][0] = 0;
    bl_ava[c][1] = 0;
    current_answer[c] = 0;
  }

  i = 0;
  j = 0; 
  c = 0;
}

void readpuzzle(void)
{
  int p = 0;
  char chbuffer = 'A';

  for( i = 0 ; i < 9 ; i++ )
    for( j = 0 ; j < 9 ; j++ )
    {
      scanf("%c ", &chbuffer);	// Read in the sudoku.
      if( chbuffer == '.' )     // Find available blanks.
	    { 
        count++;                // Counting the numbers of available blanks.
        nsudoku[i][j] = 0;      // Assign 0 to available blanks.
        bl_ava[c][0] = i;       // Record the indexes.
        bl_ava[c][1] = j;
        c++;
	    }
      else                      // Record the value.
	      nsudoku[i][j] = chbuffer - '0';  
    }

/*Assign -1 to the remained elements of bl_ava[p][0].*/
  for( p = count ; p <= 82 ; p++ )
  {
    bl_ava[p][0] = -1;
    bl_ava[p][1] = -1;
  }
} 

void printpuzzle(void)  // Show the solution of sudoku game.
{
  printf("solution %d:", found);
	for( i = 0 ; i < 9 ; i++ )
	{	
    printf("\n  ");
    for( j = 0 ; j < 9 ; j++ )
    {
			printf("%d ", nsudoku[i][j]);
      if( j==2 || j==5 ) 
        printf("| ");      
    }
    if( i==2 || i==5 ) 
      printf("\n  ------|-------|------"); 
  }
  printf("\n");
}

/* The function returns 0 if the current answer is illegal and 1 contrary */
int try_ans_checker(void)
{
  int p = 0, q = 0;  
  int block[2] = {0,0};
  
  for( p = 0 ; p <= 8 ; p++ )  // Same number at current Row?
    if( nsudoku[i][p] == current_answer[c] )
      return 0;

  for( q = 0 ; q <= 8 ; q++ )  // Same number at same Column?
    if( nsudoku[q][j] == current_answer[c] )
      return 0;
      
/*Same number at same blocks?*/
  block[0] = (i/3);
  block[1] = (j/3);
  for( p = block[0]*3 ; p <= (block[0]*3 + 2) ; p++ )  
    for( q = block[1]*3 ; q <= (block[1]*3 + 2) ; q++ )
      if( nsudoku[p][q] == current_answer[c] )
        return 0;
       
  return 1;  // The answer is legal.
}



