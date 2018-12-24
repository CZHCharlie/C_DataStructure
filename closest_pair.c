/*
Description
Given n points in metric space, find a pair of points with the smallest distance between them.

Input
The input consists of several test case. 
For each case, the first line contains the total number of the points n (n >= 2).
Then next n lines follow, each line contains a coordinate (x, y) (-1000 <= x , y <= 1000) of a point.
The end of the input is indicated by 0.

Output
The minimum distance of the closest pair of the points.
The output value should retain 2 digits after the decimal point.

Sample Input
3
1 0
2 1
2 0
4
-2 1
1 0
-3 2
4 4
0

Sample Output
1.00
1.41
*/

#include <stdio.h>
#include <math.h>

#define INF 2001
 
struct point{
    int x;
    int y;
};
typedef struct point POINT;
 
double distance (POINT, POINT);
inline double distance (POINT p1, POINT p2) { return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)); }
void Merge(POINT*, POINT*, int, int, int);
void MergeSort(POINT*, POINT*, int, int);
double MinDistance(POINT*, int, int);
 
int main()
{
    int n = 0;
    scanf("%d", &n);
    while (n != 0) {
        POINT p[n], t[n];
        for (int i = 0; i <= n - 1; i++)
            scanf("%d %d", &p[i].x, &p[i].y);
        MergeSort(p, t, 0, n - 1);
        printf("%.2f\n", MinDistance(p, 0, n - 1));
        scanf("%d", &n);
    }
 
    return 0;
}
 
double MinDistance(POINT* source, int startIndex, int endIndex)
{
    if (startIndex + 1 == endIndex)
        return distance(source[startIndex], source[endIndex]);
    else if (startIndex + 1 > endIndex)
        return INF;
    else {
        int midIndex = startIndex + (endIndex - startIndex) / 2;
        double delt1 = MinDistance(source, startIndex, midIndex);
        double delt2 = MinDistance(source, midIndex + 1, endIndex);
        double delt = 0;
        if (delt1 > delt2)
            delt = delt2;
        else
            delt = delt1;
        int minIndex = midIndex, maxIndex = midIndex + 1;
        while (source[midIndex].x - source[minIndex].x < delt && minIndex >= startIndex)
            minIndex--;
        minIndex++;
        while (source[maxIndex].x - source[midIndex].x < delt && maxIndex <= endIndex)
            maxIndex++;
        maxIndex--;
        for (int i = minIndex; i <= midIndex; i++) {
            int j = midIndex + 1;
            while (j <= maxIndex && fabs(source[j].y - source[i].y) < delt) {
                if (distance(source[i], source[j]) < delt)
                    delt = distance(source[i], source[j]);
                j++;
            }
        }
        return delt;
    }
}
 
void MergeSort(POINT* source, POINT* temp, int startIndex, int endIndex)
{
    if (startIndex < endIndex) {
        int medianIndex = startIndex + (endIndex - startIndex) / 2;
        MergeSort(source, temp, startIndex, medianIndex);
        MergeSort(source, temp, medianIndex + 1, endIndex);
        Merge(source, temp, startIndex, medianIndex, endIndex);
    }
}
 
void Merge(POINT* source, POINT* temp, int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j = midIndex + 1, k = startIndex;
    while (i != midIndex + 1 && j != endIndex + 1) {
        if (source[i].x > source[j].x) {
            temp[k].x = source[j].x;
            temp[k++].y = source[j++].y;
        }
        else {
            temp[k].x = source[i].x;
            temp[k++].y = source[i++].y;
        }
    }
    while (i != midIndex + 1) {
        temp[k].x = source[i].x;
        temp[k++].y = source[i++].y;
    }
    while (j != endIndex + 1) {
        temp[k].x = source[j].x;
        temp[k++].y = source[j++].y;
    }
    for (i = startIndex; i <= endIndex; i++) {
        source[i].x = temp[i].x;
        source[i].y = temp[i].y;
    }
}