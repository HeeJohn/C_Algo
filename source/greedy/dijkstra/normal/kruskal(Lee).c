#define _CRT_SECURE_NO_WARNINGS/*항공소프트웨어공학과 202000974 이재혁*/
#include<stdio.h>
#include<stdlib.h>
const int TRUE = 1;
const int FALSE = 0;
#define MAX_VERTICES 100  // 그래프의 정점의 개수
#define INF 1000      // 경로가 존재하지 않음을 뜻함
#define MAX_ELEMENT 100   // 히프의 최대크기

/* union find*/
int parent[MAX_VERTICES]; // 각 정점의 부모 노드
int num[MAX_VERTICES];    // 각 집합의 크기

void set_init(int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        parent[i] = -1;
        num[i] = 1;
    }
}

int set_find(int vertex)
{
    int p, s, i = -1; // p: 부모노드

    for (i = vertex; (p = parent[i]) >= 0; i = p);

    s = i;  // 루트노드 정보를 s에 저장

    for (i = vertex; (p = parent[i]) >= 0; i = p)
        parent[i] = s;

    return s; // 모든 노드의 부모인 루트를 반환한다.
}

void set_union(int s1, int s2)
{
    // 더 큰 쪽을 기준으로 집합을 합친다.
    if (num[s1] < num[s2])
    {
        parent[s1] = s2;  // s1의 부모를 s2로 설정
        num[s2] += num[s1]; // s2의 크기를 s1만큼 더해준다.
    }
    else
    {
        parent[s2] = s1;
        num[s1] += num[s2];
    }
}

typedef struct
{ /* 그래프 구조체 */
    int weight;  // 간선의 가중치
    int u;    // 정점 1
    int v;    // 정점 2
} element;

typedef struct
{ /* 힙 구조체 */
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void init(HeapType* h)
{ /* 힙 초기화 함수 */
    h->heap_size = 0;
}

int is_empty(HeapType* h)
{
    if (h->heap_size == 0)
        return TRUE;
    else
        return FALSE;
}

void insert_min_heap(HeapType* h, element item)
{ /* 최소힙 삽입 함수 */
    int i = ++(h->heap_size);

    while ((i != 1) && (item.weight < h->heap[i / 2].weight))
    {
        h->heap[i] = h->heap[i / 2];

        i /= 2;
    }

    h->heap[i] = item;
}

element delete_min_heap(HeapType* h)
{ /* 최소힙 삭제 함수 */
    int parent, child;
    element item, temp;

    item = h->heap[1];

    temp = h->heap[(h->heap_size)--];

    parent = 1; // 맨 첫 실행의 부모노드를 루트로 둔다.
    child = 2; // 그리고 그 왼쪽 자식을 자식노드로 둔다.

    while (child <= h->heap_size)
    {
        if (
            (child < h->heap_size) &&
            (h->heap[child].weight) > h->heap[child + 1].weight
            )
            child++;

        if (temp.weight <= h->heap[child].weight)
            break;

        h->heap[parent] = h->heap[child]; // 자녀의 값이 새로운 비교 기준점이 된다.
        parent = child; // 자녀가 부모로 된다. (다음 비교를 위해)
        child *= 2; // 2를 곱하여 다음 자녀로 된다.
    }
    h->heap[parent] = temp;
    return item;
}

void insert_heap_edge(HeapType* h, int u, int v, int weight)
{ /* 간선 삽입 함수 */
    element e;
    e.u = u;
    e.v = v;
    e.weight = weight;
    insert_min_heap(h, e);
}

void insert_all_edges(HeapType* h) 
{

    // 최소힙이므로 가장 작은 노드가 루트노드로 위치하게 된다.
    insert_heap_edge(h, 0, 1, 28);
    insert_heap_edge(h, 1, 2, 16);
    insert_heap_edge(h, 2, 3, 12);
    insert_heap_edge(h, 3, 4, 22);
    insert_heap_edge(h, 4, 5, 25);
    insert_heap_edge(h, 5, 0, 10);
    insert_heap_edge(h, 6, 1, 14);
    insert_heap_edge(h, 6, 3, 18);
    insert_heap_edge(h, 6, 4, 24);
}


void kruskal(int n)
{ /* kruskal의 최소 비용 신장 트리 알고리즘 */

    int edge_accepted = 0;  // 현재까지 선택된 간선의 수
    HeapType h;       // 최소 힙
    int uset, vset;     // 정점 u와 정점 v의 집합 번호
    element e;        // 힙 요소

    init(&h);       // 힙 초기화
    insert_all_edges(&h); // 힙에 간선들을 삽입
    set_init(n);      // 집합 초기화

    while (edge_accepted < (n - 1)) // 간선의 수 < (n - 1)
    {
        e = delete_min_heap(&h);  // 가장 작은 가중치의 간선 획득
        // 획득됨과 동시에 해당 간선은 히프에서 제거된다.
        uset = set_find(e.u);   // 정점 u의 집합 번호
        vset = set_find(e.v);   // 정점 v의 집합 번호

        // 두 집합이 서로 다른 집합에 속한다면
        if (uset != vset)
        {
            printf("(%d, %d) %d \n", e.u, e.v, e.weight);
            edge_accepted++;
            set_union(uset, vset);  // 두 개의 집합을 합친다.
        }
    }
}
int main()
{
    printf("(u, v)  weight\n");
    printf("--------------\n");
    kruskal(7);
}
