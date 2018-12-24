/*
Description
Given 2 sorted arrays. Find the median of two arrays.

Input
The input consists of 3n+1 lines.
There is one integer n which is the number of test cases in the first line.
In the followings, each case contains 2 lines:
the first line has 2 numbers m and n (0 < n , m <= 500000), which denote the element number in each array,
the second line is the first sorted array and the third line is the second sorted array.
Assume that each array is not empty.

Output
The median of each case.
The output value should retain 1 digits after the decimal point.

Sample Input
2
2 1
1 3
2
2 2
1 2
3 4

Sample Output
2.0
2.5
*/

#include <stdio.h>
#include <stdbool.h>
 
void Merge(int*, int*, int, int, int);
 
int main ()
{
    int N;
    scanf("%d", &N);
    getchar();
 
    for (int i = 1; i<= N; i++) {
        int sourceArray[1000000] = {0};
        int tempArray[1000000] = {0};
        int m, n;
        scanf("%d", &m);
        scanf("%d", &n);
        for (int i = 0; i <= m + n - 1; i++) {
            scanf("%d", sourceArray + i);
        }
        Merge(sourceArray, tempArray, 0, m - 1, m + n - 1);
 
        int medianIndex = (m + n) / 2;
        double median = 0;
        if ((m + n) % 2 == 0)
            median = (sourceArray[medianIndex] + sourceArray[medianIndex - 1]) / 2.0;
        else
            median = sourceArray[medianIndex];
 
        printf("%.1f\n", median);
    }
 
    return 0;
}
 
void Merge(int* sourceArray, int* tempArray, int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j = midIndex + 1, k = startIndex;
    while (i != midIndex + 1 && j != endIndex + 1) {
        if (sourceArray[i] > sourceArray[j])
            tempArray[k++] = sourceArray[j++];
        else
            tempArray[k++] = sourceArray[i++];
    }
    while (i != midIndex + 1)
        tempArray[k++] = sourceArray[i++];
    while (j != endIndex + 1)
        tempArray[k++] = sourceArray[j++];
    for (i = startIndex; i <= endIndex; i++)
        sourceArray[i] = tempArray[i];
}