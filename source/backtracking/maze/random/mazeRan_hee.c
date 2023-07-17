/*
    program : maze(random)
    name : HuiJun Seo
    last_edit: 23.07.15
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX_COL 10
#define	MAX_ROW 10


/* --------------- typedef ---------------- */

typedef enum {
    N, NE, E, SE, S, SW, W, NW
}direction;

typedef struct {
    short int vert;
    short int horiz;
}offsets;


offsets move[8];

/* -------------- funtion declaration ------------- */
void initOffset();
bool solveMazeUtil(int maze[][MAX_COL], int x, int y, int sol[][MAX_COL]);
bool solveMaze(int maze[][MAX_COL]);
void printSolution(int sol[][MAX_COL]);
bool isSafe(int maze[][MAX_COL], int x, int y);
bool solveMaze(int maze[][MAX_COL]);

/* ------------ main ------------- */
int main()
{
    int maze[MAX_ROW][MAX_COL] =
    {     // 1 2 3 4 5 6 7 8 9 10 
            {1,0,0,1,1,0,0,0,0,0} , // 1
            {1,0,1,1,0,1,1,0,0,0} , // 2
            {0,1,0,0,0,1,0,1,0,0} , // 3
            {0,1,0,0,0,1,1,0,0,0} , // 4
            {0,1,0,1,1,0,0,1,1,1} , // 5
            {1,0,0,0,0,0,0,0,0,0} , // 6
            {1,0,0,1,0,0,0,1,0,0} , // 7
            {1,1,1,0,1,0,1,0,1,0} , // 8
            {0,0,0,0,0,1,0,0,0,1} , // 9
            {0,0,0,1,1,0,0,0,0,1}   // 10 
    };

    printSolution(maze);
    initOffset();
    solveMaze(maze);
    return 0;
}

/* ---------------------- funtion ---------------------- */
void printSolution(int sol[][MAX_COL])
{
    for (int i = 0; i < MAX_ROW; i++, puts(""))
        for (int j = 0; j < MAX_COL; j++)
            printf("%d ", sol[i][j]);
    puts("");
}

void initOffset()
{
    move[N].vert = -1;  move[N].horiz = 0;
    move[NE].vert = -1;	move[NE].horiz = 1;
    move[E].vert = 0;   move[E].horiz = 1;
    move[SE].vert = 1;  move[SE].horiz = 1;
    move[S].vert = 1;   move[S].horiz = 0;
    move[SW].vert = 1;  move[SW].horiz = -1;
    move[W].vert = 0;   move[W].horiz = -1;
    move[NW].vert = -1;	move[NW].horiz = -1;
}

bool solveMaze(int maze[][MAX_COL])
{
    int sol[MAX_ROW][MAX_COL] = { 0 };

    if (!solveMazeUtil(maze, 0, 0, sol))
    {
        printf("Solution doesn't exist");
        return false;
    }
    printSolution(sol);
    return true;
}

// A recursive utility function to solve Maze problem
bool solveMazeUtil(int maze[][MAX_COL], int x, int y, int sol[][MAX_COL])
{
    // if (x, y is goal) return true
    if (x == MAX_COL - 1 && y == MAX_ROW - 1 && maze[y][x] == 1)
    {
        sol[y][x] = 1;
        return true;
    }

    // Check if maze[x][y] is valid
    if (isSafe(maze, x, y) == true)
    {
        if (sol[y][x]) return false;  // Check if it is already part of path or visited
        else sol[y][x] = 1; // mark x, y as part of solution path

        printSolution(sol);
        for (direction D = N; D <= NW; D++)
            if (solveMazeUtil(maze, x + move[D].horiz, y + move[D].vert, sol))
                return true;

        sol[y][x] = 2; // BACKTRACK: unmark x, y from sol, and mark visited.
        return false;
    }
    return false;
}

/*check if x, y is valid index*/
bool isSafe(int maze[][MAX_COL], int x, int y)
{
    // if (x, y outside maze) return false
    if (x >= 0 && x < MAX_COL && y >= 0 && y < MAX_ROW && maze[y][x] == 1)
        return true;
    return false;
}
