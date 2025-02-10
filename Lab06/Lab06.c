/* EE231002 Lab06. Finding Sudoku Solutions
   106061218, Cheng En Lee
   Date: 2017/10/30
*/

#include <stdio.h>

// Global Variables
int nsudoku[9][9];       // Sudoku board
int bl_ava[81][2];       // Store indexes of empty cells
int count = 0;           // Number of blanks
int found = 0;           // Number of solutions found
int current_answer[81];  // Current attempted values

// Function declarations
void initialize(void);
void readpuzzle(void);
void printpuzzle(void);
int try_ans_checker(int row, int col, int num);
void solve_sudoku(int index);

int main(void) 
{
    initialize();    // Initialize global variables
    readpuzzle();    // Read input Sudoku puzzle
    solve_sudoku(0); // Solve the Sudoku puzzle
    printf("Total number of solutions found: %d\n", found);
    return 0;
}

// Initialize all global variables
void initialize(void) 
{
    int i, j;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++) 
            nsudoku[i][j] = 0;
    
    for (i = 0; i < 81; i++) 
    {
        bl_ava[i][0] = -1;
        bl_ava[i][1] = -1;
        current_answer[i] = 0;
    }
    count = 0;
    found = 0;
}

// Read the Sudoku puzzle from input
void readpuzzle(void) 
{
    int i, j;
    char ch;
    for (i = 0; i < 9; i++) 
        for (j = 0; j < 9; j++) 
        {
            scanf(" %c", &ch);
            if (ch == '.') 
            {
                nsudoku[i][j] = 0;
                bl_ava[count][0] = i;
                bl_ava[count][1] = j;
                count++;
            } 
            else 
            {
                nsudoku[i][j] = ch - '0';
            }
        }
}

// Print the Sudoku solution
void printpuzzle(void) 
{
    int i, j;
    printf("Solution %d:\n", found);
    for (i = 0; i < 9; i++) 
    {
        if (i % 3 == 0 && i != 0)
            printf("------+-------+------\n");

        for (j = 0; j < 9; j++) 
        {
            if (j % 3 == 0 && j != 0) 
                printf("| ");

            printf("%d ", nsudoku[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if placing 'num' at (row, col) is valid
int try_ans_checker(int row, int col, int num) 
{
    int i, j, startRow, startCol;
    
    // Check row and column
    for (i = 0; i < 9; i++)
        if (nsudoku[row][i] == num || nsudoku[i][col] == num)
            return 0;
    
    // Check 3x3 sub-grid
    startRow = (row / 3) * 3;
    startCol = (col / 3) * 3;
    for (i = startRow; i < startRow + 3; i++) 
        for (j = startCol; j < startCol + 3; j++) 
            if (nsudoku[i][j] == num) 
                return 0;

    return 1;
}

// Solve Sudoku using backtracking
void solve_sudoku(int index) 
{
    if (index == count) 
    {
        found++;
        printpuzzle();
        return;
    }
    
    int row = bl_ava[index][0];
    int col = bl_ava[index][1];
    int num;
    
    for (num = 1; num <= 9; num++)
        if (try_ans_checker(row, col, num)) 
        {
            nsudoku[row][col] = num;
            solve_sudoku(index + 1);
            nsudoku[row][col] = 0; // Backtrack
        }
}
