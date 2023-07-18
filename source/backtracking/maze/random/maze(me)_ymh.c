/*
    program : maze(me)_ymh
    name : minhyuck yun
    last_edit : 23.07.15
*/

#include <stdio.h>
#include <stdlib.h>

#define EXIT_ROW 5 
#define EXIT_COL 6 //Ż�� ��ǥ
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
}; //�̷θ� ��Ÿ���� �迭 1�� �� 0�� ��

typedef struct {
    int vert;
    int horiz;
} offsets;
offsets move[4] = { {-1,0},{0,-1},{0,1},{1,0} }; //�� ���⿡ ���� �̵� �迭(�������θ� �̵� ����)

/*�̰��� ������� �ʽ��ϴ�.*/

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

/*�̰��� ������� �ʽ��ϴ�.*/

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
    maze[row][col] = 2; //�ڽ��� ��ġ�� 2�� ǥ����
    dir = 0;
    while (!found)
    {
        system("cls"); //���� ��µ� ���� ��� �� �����ϴ� �ڵ�
        for (i = 0; i < 7; i++)
        {
            for (j = 0; j < 7; j++)
                printf("%d ", maze[i][j]);
            printf("\n"); //�̷θ� ����ϴ� �ݺ���
        }
        printf("�̵� ������ ��ġ\n");
        while (!found && dir <= 4 || (nextRow == row + 1 || nextRow == row || nextRow == row - 1) && (nextCol == col + 1 || nextCol == col || nextCol == col - 1)) //�̵������� ������ �� ������ 4�� ���Ͽ����� �ݺ�
        {
            nextRow = row + move[dir].vert; //�̵������� ��ġ �� move[dir]�� �ִ� ��ġ�� row�� ���ؼ� ��ǥ�� ��Ÿ��
            nextCol = col + move[dir].horiz;
            if (maze[nextRow][nextCol] == 0)
            {
                printf("(%d, %d)\n", nextRow, nextCol);
                k++; //���� �̵������� ��ġ�� �ִٸ� �� �� �����ߴ� ��, ��� �������� ���
            }
            dir++;
        }
        dir = 0;
        if (k > 1)
        {
            printf("�̵��� �� �ִ� ��ġ�� �� �� �̻��̶� ���� ��ġ�� ����մϴ�.\n");
            position.row = row;
            position.col = col;
            push(position); //���� ��ġ�� push
            z++;//�� �� �����ߴ� �� ����
        }
        printf("�̵��ϰ� ���� ��ǥ�� �Է��ϼ���(�ڽ� : 2).\n(ex)1 1\n����� ��ġ�� �̵��ϰ� �ʹٸ� 9 9�� �Է��ϼ���.(���� ����x)\n->");
        scanf_s("%d %d", &nextRow, &nextCol); //�̵��� ��ǥ�� �Է¹���

        if (nextRow == 9 && nextCol == 9)
        {
            if (z == 0) {
                printf("����� ��ġ�� �����ϴ�.\n�ٽ� �Է����ּ���.\n->");
                scanf_s("%d %d", &nextRow, &nextCol); //���� ����� ��ġ�� ���ٸ� �� z�� �������� �ʾҴٸ� ����
            }
            else {
                printf("����� ��ġ�� �ҷ��ɴϴ�.\n");
                for (i = z; i > 0; i--) {
                    position = pop();
                    printf("%d.(%d, %d)\n", num, position.row, position.col);
                    num++; //��ȣ�� ��Ÿ��
                }
                printf("�̵��ϰ� ���� ��ġ�� ��ȣ�� �Է����ּ���.\n->");
                scanf_s("%d", &num); //��ȣ�� �Է� ����
                z -= num; //z�� �� ž�� ��ȣ��ŭ ����
                top = z;
                position = pop(); //��ȣ ��°�� ���ÿ��� ��ǥ�� pop�ؿ�
                maze[row][col] = 0;
                row = position.row;
                col = position.col; //row, col�� ����
                top++; //�� �� pop�߱� ������ top�� 1 ����������
                path();
            }
        }
        i = 1;
        while (i)
        {
            if (maze[nextRow][nextCol] == 0 && (nextRow == row + 1 || nextRow == row || nextRow == row - 1) && (nextCol == col + 1 || nextCol == col || nextCol == col - 1))
            { //���� �̷ο��� ���� ��ġ�� 0�̶�� ���� �� ���� ��ġ�� �̵������� �� ĭ �Ÿ��� ���� ��ġ��� ����
                maze[row][col] = 0;
                i = 0;
                row = nextRow;
                col = nextCol;
            }
            else
            {
                printf("��ȿ���� ���� ��ġ�Դϴ�.\n");
                i = 0;
            }
        }
        if (row == EXIT_ROW, col == EXIT_COL)
            found = TRUE;
    }

    system("cls"); //����� ���� ��� �����ϴ� �ڵ�
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 7; j++)
            printf("%d ", maze[i][j]);
        printf("\n");
    } //������ �̷θ� ���

    printf("�����մϴ�! Ż���ϼ̽��ϴ�.\n");
}