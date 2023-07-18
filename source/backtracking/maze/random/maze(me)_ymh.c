/*
    program : maze(me)_ymh
    name : minhyuck yun
    last_edit : 23.07.15
*/

#include <stdio.h>
#include <stdlib.h>

#define EXIT_ROW 5 
#define EXIT_COL 6 //탈출 좌표
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 36
#define MAX_ROW 7
#define MAX_COL 7

int maze[MAX_ROW][MAX_COL] =
{ {1,1,1,1,1,1,1},
   {1,0,0,0,1,0,1},
   {1,0,1,0,0,0,1},
   {1,0,1,1,0,0,1},
   {1,0,0,0,1,1,1},
   {1,1,1,0,0,0,0},
   {1,1,1,1,1,1,1}
}; //미로를 나타내는 배열 1은 벽 0은 길

typedef struct {
    int vert;
    int horiz;
} offsets;
offsets move[4] = { {-1,0},{0,-1},{0,1},{1,0} }; //각 방향에 대한 이동 배열(수직으로만 이동 가능)

/*이곳은 사용하지 않습니다.*/

typedef struct {
    int row;
    int col;
}element;

element stack[MAX_STACK_SIZE];

int top = -1;
int row = 1;
int col = 1;

void path(void);
void push(element item);
element pop();
void stackFull();
int stackEmpty();

/*이곳은 사용하지 않습니다.*/

int main(void)
{
    path();
}

void push(element item)
{
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

void stackFull()
{
    fprintf(stderr, "Stack is full, cannot add element");
    exit(EXIT_FAILURE);
}

element pop()
{
    if (top == -1)
        stackEmpty();
    return stack[top--];
}

int stackEmpty()
{
    fprintf(stderr, "Stack is Empty, cannot pop element");
    exit(EXIT_FAILURE);
}

void path(void)
{
    int num, i, j, k, z, dir, nextRow, nextCol, found = FALSE;
    element position;
    z = 0;
    k = 0;
    num = 1;
    maze[row][col] = 2; //자신의 위치를 2로 표현함
    dir = 0;
    while (!found)
    {
        system("cls"); //현재 출력된 것을 모두 다 삭제하는 코드
        for (i = 0; i < 7; i++)
        {
            for (j = 0; j < 7; j++)
                printf("%d ", maze[i][j]);
            printf("\n"); //미로를 출력하는 반복문
        }
        printf("이동 가능한 위치\n");
        while (!found && dir <= 4 || (nextRow == row + 1 || nextRow == row || nextRow == row - 1) && (nextCol == col + 1 || nextCol == col || nextCol == col - 1)) //이동가능한 방향의 총 개수인 4애 이하에서만 반복
        {
            nextRow = row + move[dir].vert; //이동가능한 위치 중 move[dir]에 있는 위치를 row에 더해서 좌표를 나타냄
            nextCol = col + move[dir].horiz;
            if (maze[nextRow][nextCol] == 0)
            {
                printf("(%d, %d)\n", nextRow, nextCol);
                k++; //만약 이동가능한 위치가 있다면 몇 번 누적했는 지, 어디가 가능한지 출력
            }
            dir++;
        }
        dir = 0;
        if (k > 1)
        {
            printf("이동할 수 있는 위치가 두 개 이상이라 현재 위치를 기억합니다.\n");
            position.row = row;
            position.col = col;
            push(position); //현재 위치를 push
            z++;//몇 번 저장했는 지 저장
        }
        printf("이동하고 싶은 좌표를 입력하세요(자신 : 2).\n(ex)1 1\n저장된 위치로 이동하고 싶다면 9 9를 입력하세요.(현재 구현x)\n->");
        scanf_s("%d %d", &nextRow, &nextCol); //이동할 좌표를 입력받음

        if (nextRow == 9 && nextCol == 9)
        {
            if (z == 0) {
                printf("저장된 위치가 없습니다.\n다시 입력해주세요.\n->");
                scanf_s("%d %d", &nextRow, &nextCol); //만약 저장된 위치가 없다면 즉 z가 누적되지 않았다면 실행
            }
            else {
                printf("저장된 위치를 불러옵니다.\n");
                for (i = z; i > 0; i--) {
                    position = pop();
                    printf("%d.(%d, %d)\n", num, position.row, position.col);
                    num++; //번호를 나타냄
                }
                printf("이동하고 싶은 위치의 번호를 입력해주세요.\n->");
                scanf_s("%d", &num); //번호를 입력 받음
                z -= num; //z를 즉 탑을 번호만큼 빼줌
                top = z;
                position = pop(); //번호 번째에 스택에서 좌표를 pop해옴
                maze[row][col] = 0;
                row = position.row;
                col = position.col; //row, col에 삽입
                top++; //한 번 pop했기 때문에 top을 1 증가시켜줌
                path();
            }
        }
        i = 1;
        while (i)
        {
            if (maze[nextRow][nextCol] == 0 && (nextRow == row + 1 || nextRow == row || nextRow == row - 1) && (nextCol == col + 1 || nextCol == col || nextCol == col - 1))
            { //만약 미로에서 다음 위치가 0이라면 또한 그 다음 위치가 이동가능한 한 칸 거리의 내의 위치라면 실행
                maze[row][col] = 0;
                i = 0;
                row = nextRow;
                col = nextCol;
            }
            else
            {
                printf("유효하지 않은 위치입니다.\n");
                i = 0;
            }
        }
        if (row == EXIT_ROW, col == EXIT_COL)
            found = TRUE;
    }

    system("cls"); //출력한 것을 모두 삭제하는 코드
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 7; j++)
            printf("%d ", maze[i][j]);
        printf("\n");
    } //현재의 미로를 출력

    printf("축하합니다! 탈출하셨습니다.\n");
}