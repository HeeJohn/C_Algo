/*
    program : closest pair
    name : yeongjin kim
    last edited : 23.07.25
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct
{
    int x;
    int y;
} Point;

int compareX(const void* a, const void* b)
{
    return ((Point*)a)->x - ((Point*)b)->x;
}

int compareY(const void* a, const void* b)
{
    return ((Point*)a)->y - ((Point*)b)->y;
}

float distance(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float mins(float x, float y)
{
    return (x < y) ? x : y;
}

float closestPair(Point points[], int n, Point* closestP)
{
    if (n <= 1)
    {
        return FLT_MAX;
    }

    if (n == 2)
    {
        closestP[0] = points[0];
        closestP[1] = points[1];
        return distance(points[0], points[1]);
    }

    qsort(points, n, sizeof(Point), compareX);
    int mid = n / 2;
    Point midPoint = points[mid];

    Point leftClosest[2], rightClosest[2];
    float leftDist = closestPair(points, mid, leftClosest);
    float rightDist = closestPair(points + mid, n - mid, rightClosest);

    float d = mins(leftDist, rightDist);
    if (d == leftDist)
    {
        closestP[0] = leftClosest[0];
        closestP[1] = leftClosest[1];
    }
    else
    {
        closestP[0] = rightClosest[0];
        closestP[1] = rightClosest[1];
    }

    Point* strip = (Point*)malloc(n * sizeof(Point));
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(points[i].x - midPoint.x) < d)
        {
            strip[j] = points[i];
            j++;
        }
    }

    qsort(strip, j, sizeof(Point), compareY);

    for (int i = 0; i < j; i++)
    {
        for (int k = i + 1; k < j && (strip[k].y - strip[i].y) < d; k++)
        {
            float dist = distance(strip[i], strip[k]);
            if (dist < d)
            {
                d = dist;
                closestP[0] = strip[i];
                closestP[1] = strip[k];
            }
        }
    }

    free(strip);
    return d;
}

int main()
{
    Point points[] = { {1, 2}, {22, 25}, {6, 8}, {7, 9}, {31, 32}, {9, 12}, {3, 5}, {15, 17}, {20, 21}, {27, 30} };
    int numPoints = sizeof(points) / sizeof(points[0]);

    Point closestP[2]; // 최단 거리에 해당하는 두 좌표값을 저장할 배열
    float result = closestPair(points, numPoints, closestP);

    printf("가장 가까운 두 점의 좌표: (%d, %d), (%d, %d)\n", closestP[0].x, closestP[0].y, closestP[1].x, closestP[1].y);
    printf("가장 가까운 두 점의 거리: %.2f\n", result);

    return 0;
}
