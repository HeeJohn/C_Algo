#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_VTXS 256         // 최대 정점 개수
const int TRUE = 1;
const int FALSE = 0;
int size;                       // 정점의 개수
char vertices[MAX_VTXS];       // 정점의 이름
int graph[MAX_VTXS][MAX_VTXS];  // 인접 행렬
void reset()
{/* 그래프 초기화 함수 */
    for (int i = 0;i < MAX_VTXS;i++)
        for (int j = 0;j < MAX_VTXS;j++)
            graph[i][j] = 0;

    size = 0;
}
int isFull()
{
    return size >= MAX_VTXS;
}
void insertVertex(char name)
{/* 정점 삽입 함수 */
    if (isFull())
    {
        printf("Graph vertex full error\n");
        return;
    }

    vertices[size++] = name;
}
void insertEdge(int u, int v, int weight)
{/* 간선 삽입(무방향 그래프) */
    graph[u][v] = weight;     // 가중치 그래프라면 1이 아닌 가중치 삽입
    graph[v][u] = weight;     // 방향그래프에서는 이 부분 삭제(<u, v>만 존재) 
}
int minDistance(int dist[MAX_VTXS], int found[MAX_VTXS])
{ /* 최소 거리 정점 찾는 함수 */
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < size; v++)
    {
        if (!found[v] && min > dist[v])
        {
            min_index = v;
            min = dist[v];
        }
    }

    return min_index;
}

void printSolution(int dist[], int n)
{ /* 최소 거리 출력 함수 */
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < size; i++)
    {

        printf("%d \t\t ", i);
        if (dist[i] == INT_MAX)
            printf("∞\n");
        else
            printf("%d\n", dist[i]);
    }
}

void dijkstra(int start)    // start: 시작 지점
{ /* 다익스트라 함수 */


    int* dist = (int*)malloc(sizeof(int) * size); // 최단 거리를 파악하는 배열
    int* found = (int*)malloc(sizeof(int) * size); // 방문 했는지 체크 하는 배열

    for (int i = 0; i < size; i++)
        dist[i] = INT_MAX, found[i] = FALSE;

    
    dist[start] = 0; // 초기 조건 설정

   
    for (int count = 0; count < size - 1; count++)      // 첫 start 노드를 제외한 모든 노드들에 접근을 해 계산(size-1번 수행)
    {
       
        int u = minDistance(dist, found);   // 최단거리 정보를 알고 있는 노드들 중 가장 거리가 짧은 노드의 인덱스를 가져온다.

      
        for (int v = 0; v < size; v++)  // 그래프 상의 모든 노드들을 탐색하며 u 노드의 주변 정보를 갱신한다.
        {
            // 1. 아직 처리가 되지 않은 노드이어야 하며 (무한루프 방지)
            // 2. u-v 간에 edge가 존재하고
            // 3. start부터 u까지의 경로가 존재하고
            // 4. 기존의 v노드까지의 최단거리 값보다 새로 계산되는 최단거리가 더 짧을 경우
            if (!found[v] && graph[u][v] && dist[u] != INT_MAX && dist[v] > dist[u] + graph[u][v])
            {
                // 최단거리를 갱신해준다.
                dist[v] = dist[u] + graph[u][v];
            }
        }

        
        found[u] = TRUE;  // u 노드의 접근은 끝났다. 그러므로 TRUE로 저장.

        
        printSolution(dist, size); // 현재까지의 최단 거리를 출력해준다.
    }
    free(dist);
    free(found);
}

int main()
{
    reset();

    /* 정점 삽입 */
    insertVertex('A');    // 0
    insertVertex('B');    // 1
    insertVertex('C');    // 2
    insertVertex('D');    // 3
    insertVertex('E');    // 4
    insertVertex('F');    // 5


    /* 간선 삽입 */
    insertEdge(0, 1, 2);   // A->B
    insertEdge(0, 3, 1);   // A->D
    insertEdge(1, 2, 3);   // B->C
    insertEdge(1, 3, 2);   // B->D
    insertEdge(2, 5, 5);   // C->F
    insertEdge(3, 4, 1);   // D->E
    insertEdge(4, 5, 2);   // E->F

    dijkstra(0);    // 시작 지점이 0이다.



    return 0;
}