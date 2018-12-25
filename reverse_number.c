/*
Description
Given a signed number which can be very long (which means the input number can be out of the long long int range).
Reverse digits of the number and print it.
Assuming the output number should be an integer, which is in the range of [-2^31, 2^31-1].
If the reversed number is out of range (called overflow), print 0.

Input
The input consists of n+1 lines.
There is one integer n which is the number of test cases in the first line.
In the followings, each line contains a number. ('\n' will be added at the end of each line)

Output
The reversed number of each line or 0 for the overflow.
The sign should be retained.

Sample Input
3
123
-321
210

Sample Output
321
-123
12
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
int main()
{
    int n, count;
    scanf("%d", &n);
    getchar();
    for (count = 1; count <= n; count++) {
        int x, sign;
        long long int S = 0, i = 1;
        bool flag = true; /**表示正负号， 负号为false*/
        bool legal = true; /**表示是否超过范围，超过为false*/
        bool legal_i = true;
        bool start = false; /**用来排除上来一堆0的情况，比如00000123*/
        if ((sign = getchar()) == '-' && legal) {
            flag = false;
            while ((x = getchar()) != '\n') {
                if (x == 48 && !start) {
                    continue;
                }
                else {
                    start = true;
                }
 
                if (i >= 100000000000 && legal_i) {
                    legal_i = false;
                }
                if (!legal_i && (x - 48)) {
                    legal = false;
                }
                if (legal) {
                    S += (x - 48) * i;
                    i *= 10;
                    if (S > 2147483648) {
                        legal = false;
                    }
                }
            }
        }
        else if (legal) {
            flag = true;
            if (sign != 48) {
                S = (sign - 48);
                i *= 10;
                start = true;
            }
            while ((x = getchar()) != '\n') {
                if (x == 48 && !start) {
                    continue;
                }
                else {
                    start = true;
                }
 
                if (i >= 100000000000 && legal_i) {
                    legal_i = false;
                }
                if (!legal_i && (x - 48)) {
                    legal = false;
                }
                if (legal) {
                    S += (x - 48) * i;
                    i *= 10;
                    if (S > 2147483647) {
                        legal = false;
                    }
                }
            }
        }
        if (legal) {
            if (!flag) {
                printf("-");
            }
            printf("%lld\n", S);
        }
        else {
            printf("0\n");
        }
    }
 
    return 0;
}