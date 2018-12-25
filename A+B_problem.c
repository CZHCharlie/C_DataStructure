/*
Description
Calculate A + B (0 <= A , B <= 10^100)

Input
The input consists of n+1 lines.
The first line contains the number of test cases. 
In the following, each line contains two numbers seperated by a space.

Output
Output the sum of two numbers.
An "END" should be found at the n+1 line.

Sample Input
3
123 456
123 1
10 90

Sample Output
579
124
100
END
*/

#include <stdio.h>
#include <stdbool.h>
 
int main()
{
    int n;
 
    scanf("%d", &n);
    getchar();
    for (int i = 1; i <= n; i++) {
        char A[120] = {};
        char B[120] = {};
        char C[120] = {};
        int A_end = 119;
        int B_end = 119;
 
        scanf("%s %s", A, B);
        getchar();
        while (A[A_end] == NULL && A[A_end - 1] == NULL) {
            A_end--;
        }
        while (B[B_end] == NULL && B[B_end - 1] == NULL) {
            B_end--;
        }
        for (int i = A_end - 1; i >= 0; i--) {
            A[i + 120 - A_end] = A[i];
        }
        for (int i = 0; i <= 119 - A_end; i++) {
            A[i] = '0';
        }
        for (int i = B_end - 1; i >= 0; i--) {
            B[i + 120 - B_end] = B[i];
        }
        for (int i = 0; i <= 119 - B_end; i++) {
            B[i] = '0';
        }
 
        int carry = 0;
        for (int i = 119; i >= 0; i--) {
            C[i] = A[i] + B[i] - 48 + carry;
            if (C[i] >= 48 && C[i] <= 57) {
                carry = 0;
            }
            else if (C[i] >= 58 && C[i] <= 67) {
                C[i] -= 10;
                carry = 1;
            }
        }
 
        bool start = false;
        for (int i = 0; i <= 119; i++) {
            if (C[i] != '0' || i == 119) {
                start = true;
            }
            if (start) {
                printf("%c", C[i]);
            }
        }
        printf("\n");
    }
    printf("END");
 
    return 0;
}