/*
    program : Solving sudoku
    name : HuiJun Seo
    last_edit: 23.07.15
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdbool.h>
#define UNASSIGNED 0
#define N 9

/* -------- declaration of function --------- */
bool FindUnassignedLocation(int grid[N][N], int* row, int* col);
bool isSafe(int grid[N][N], int row, int col, int num);
bool SolveSudoku(int grid[N][N]);
bool UsedInRow(int grid[N][N], int row, int num);
bool UsedInCol(int grid[N][N], int col, int num);
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num);
void printGrid(int grid[N][N]);


/* -------- main--------- */
int main()
{
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0} };


    printf("   < before Solving sudoku >\n");  printGrid(grid);

    if (SolveSudoku(grid))
    {
        printf("\n   < after Solving sudoku >\n");
        printGrid(grid);
    }
    else printf("No solution exists");

    return 0;
}


/* -------- function --------- */

void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++, printf("|\n"))
    {
        if (!(row % 3))  puts("-------------------------------");
        for (int col = 0; col < N; col++)
        {
            if (!(col % 3)) printf("|");
            printf(" %d ", grid[row][col]);
        }
    }
    puts("-------------------------------");
}
bool SolveSudoku(int grid[N][N])
{
    int row, col;

    //solving Sudoku ends when there is no 0 in the grid, which means soloved.
    if (!FindUnassignedLocation(grid, &row, &col))
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num)) //check if it is valid.
        {
            grid[row][col] = num; // mark
            if (SolveSudoku(grid))
                return true;

            grid[row][col] = UNASSIGNED; // unmark
        }
    }
    return false;
}

bool FindUnassignedLocation(int grid[N][N], int* row, int* col)
{
    for (*row = 0; *row < N; (*row)++)
        for (*col = 0; *col < N; (*col)++)
            if (grid[*row][*col] == UNASSIGNED)
                return true;
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) &&
        !UsedInCol(grid, col, num) &&
        !UsedInBox(grid, row - row % 3, col - col % 3, num) &&
        grid[row][col] == UNASSIGNED;
}

bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}



