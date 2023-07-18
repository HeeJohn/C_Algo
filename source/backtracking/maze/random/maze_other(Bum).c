/*
* program: �̷�ã��(�ٸ� �˰���)
* name: ��â��
* date: 2023.07.18
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MALLOC(p, s) \
if(!((p)=malloc(s)))   {\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

#define MAX_ROW 13
#define MAX_COL 17
#define EXIT_ROW 11
#define EXIT_COL 15

typedef struct {
    short int vert;
    short horiz;
}offsets;
offsets move[8] = { {-1,0},{-1,1},{0,1},{1,1}, {1,0},{1,-1},{0,-1},{-1,-1} };

typedef struct Point {
    short int row;
    short int col;
};

typedef struct Node {
    Point position;
    int distance;
};

int maze[MAX_ROW][MAX_COL];
int visited[MAX_ROW][MAX_COL];

void buildMaze();
void printMaze();
void enqueue(Node* queue, int* rear, Node item);
Node dequeue(Node* queue, int* front);
int bfs(Point start, Point end);

int main() {
    buildMaze();
    printf("�̷�:\n");
    printMaze();

    Point start = { 1, 1 }; // ������ ��ǥ
    Point end = { EXIT_ROW, EXIT_COL }; // ������ ��ǥ

    int distance = bfs(start, end);
    if (distance != -1) {
        printf("�������� ���� �����մϴ�. �ִ� �Ÿ�: %d\n", distance);
    }
    else {
        printf("�������� ������ �� �����ϴ�.\n");
    }

    return 0;
}

void buildMaze() {
    srand(time(NULL));

    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            if (i == 0 || i == MAX_ROW - 1 || j == 0 || j == MAX_COL - 1) {
                maze[i][j] = 1; // �ܰ��� ������ ����
            }
            else if ((i == 1 && j == 1) || (i == EXIT_ROW && j == EXIT_COL)) {
                maze[i][j] = 0; // �������� �������� ��� ����
            }
            else {
                maze[i][j] = rand() % 2; // �������� �����ϰ� �� �Ǵ� ��� ����
            }
        }
    }
}

void printMaze() {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

void enqueue(Node* queue, int* rear, Node item) {
    (*rear)++;
    queue[*rear] = item;
}

Node dequeue(Node* queue, int* front) {
    (*front)++;
    return queue[*front];
}

int bfs(Point start, Point end) {
    visited[1][1] = 1;

    Node* queue = (Node*)malloc(sizeof(Node) * MAX_ROW * MAX_COL);
    int front = -1;
    int rear = -1;

    Node startNode;
    startNode.position = start;
    startNode.distance = 0;
    enqueue(queue, &rear, startNode);

    while (front!=rear) {
        Node current = dequeue(queue, &front);

        Point position = current.position;
        int distance = current.distance;

        if (position.row == end.row && position.col == end.col) {
            free(queue);
            return distance; // �������� ������ ��� �ִ� �Ÿ� ��ȯ
        }

        for (int i = 0; i < 8; i++) {
            int nx = position.row + move[i].vert;
            int ny = position.col + move[i].horiz;

            if (!maze[nx][ny]&& !visited[nx][ny]) {
                Node next;
                next.position.row = nx;
                next.position.col = ny;
                next.distance = distance + 1;
                enqueue(queue, &rear, next);
                visited[nx][ny] = 1;
            }
        }
    }

    free(queue);
    return -1; // �������� ������ �� ���� ���
}